#pragma once
#include <OGL3D/OPrerequisites.h>
#include <memory>
//#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <chrono>
using namespace std;

class OGraphicsEngine;
class OEntitySystem;
class OWindow;
class OGame
{
public:
	OGame();
	virtual ~OGame();

	void run();
	void quit();

	OEntitySystem* getEntitySystem();

protected:
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onQuit();

protected:
	bool m_isRunning = true;
	unique_ptr<OGraphicsEngine> m_graphicsEngine;
	unique_ptr<OWindow> m_display;
	unique_ptr<OEntitySystem> m_entitySystem;

	OVertexArrayObjectPtr m_polygonVAO;
	OUniformBufferPtr m_uniform;
	OShaderProgramPtr m_shader;

	chrono::system_clock::time_point m_previousTime;
	f32 m_scale = 0;
};

