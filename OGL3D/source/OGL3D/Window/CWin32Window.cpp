#include <OGL3D/Window/OWindow.h>
#include <Windows.h>
#include <glad/glad_wgl.h>
#include <glad/glad.h>
#include <assert.h>

LRESULT CALLBACK WndPRoc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lPARAM) {

	switch (msg) {

	case WM_DESTROY:
	{
		OWindow* window = (OWindow*) GetWindowLongPtr(hwnd,GWLP_USERDATA);
		break;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		break;
	}

	default:
		return DefWindowProc(hwnd, msg, wParam,lPARAM);
	}

	return NULL;
}

OWindow::OWindow()
{
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = L"OGL3DWindow";//wchar_t is a prefix for wchar_t or wide character so is cast
	wc.lpfnWndProc = &WndPRoc;
	//wc.lpfnWndProc = DefWindowProcA; //close is the window in a weird way
	wc.style = CS_OWNDC;

	auto classId = RegisterClassEx(&wc);
	assert(classId);

	RECT rc = {0,0,1024,768}; //area where the window display an image or play area
	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

	m_handle = CreateWindowEx(
		NULL,MAKEINTATOM(classId), L"ParseCode | OpenGL 3D", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT,CW_USEDEFAULT,rc.right-rc.left,rc.bottom-rc.top, // as I use rc that means that size now will have border+game area
		NULL,NULL,NULL,NULL
	); 


	assert(m_handle);

	SetWindowLongPtr((HWND)m_handle,GWLP_USERDATA,(LONG_PTR)this);

	ShowWindow((HWND)m_handle,SW_SHOW);
	UpdateWindow((HWND)m_handle);

	//Creating OPENGL render context

	auto hDC = GetDC(HWND(m_handle));

	int pixelFormatAttributes[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
	    WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB,  WGL_FULL_ACCELERATION_ARB,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB,8,
		0
	};

	int pixelFormat = 0;
	UINT numFormats = 0;

	wglChoosePixelFormatARB(hDC, pixelFormatAttributes,nullptr,1,&pixelFormat, &numFormats);
	assert(numFormats);

	PIXELFORMATDESCRIPTOR pixelFormatDesc={};
	DescribePixelFormat(hDC,pixelFormat,sizeof(PIXELFORMATDESCRIPTOR),&pixelFormatDesc);
	SetPixelFormat(hDC,pixelFormat,&pixelFormatDesc);

	int openGLAttributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 6,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	m_context = glad_wglCreateContextAttribsARB(hDC,0, openGLAttributes);
	assert(m_context);

}

OWindow::~OWindow()
{
	wglDeleteContext(HGLRC(m_context));
	DestroyWindow((HWND)m_handle);
}

ORect OWindow::getInnerSize()
{
	RECT rc = {};
	GetClientRect((HWND)m_handle,&rc);
	return ORect(rc.right-rc.left,rc.bottom-rc.top);
}


void OWindow::makeCurrentContext()
{
	wglMakeCurrent(GetDC(HWND(m_handle)),HGLRC(m_context));
}
void OWindow::present(bool vsync)
{
	wglSwapIntervalEXT(vsync);//basically set vsync on or off
	wglSwapLayerBuffers(GetDC(HWND(m_handle)),WGL_SWAP_MAIN_PLANE);

}

