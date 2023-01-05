#pragma once
#include <memory>
#include <sstream>
#include <iostream>
#include <stdexcept>
using namespace std;

class OVertexArrayObject;
class OUniformBuffer;
class OShaderProgram;

typedef std::shared_ptr<OVertexArrayObject> OVertexArrayObjectPtr;
typedef std::shared_ptr<OUniformBuffer> OUniformBufferPtr;
typedef std::shared_ptr<OShaderProgram> OShaderProgramPtr;

typedef float f32;
typedef int i32;
typedef unsigned int ui32;

struct OVertexAttribute
{
	ui32 numElements = 0;
};

struct OVertexBufferDesc
{
	void* verticesList = nullptr;
	ui32 vertexSize = 0;
	ui32 listSize = 0;

	OVertexAttribute* attributesList = nullptr;
	ui32 attributesListSize = 0;
};


struct OIndexBufferDesc
{
	void* indicesList = nullptr;
	ui32 listSize = 0;
};

struct OShaderProgramDesc
{
	const wchar_t* vertexShaderFilePath;
	const wchar_t* fragmentShaderFilePath;
};

struct OUniformBufferDesc
{
	ui32 size = 0;
};

enum class OTriangleType
{
	TriangleList = 0, //in this way you will have all the vertice T1-1,T1-2,T1-3 and T2-1,T2-2,T2-3
	TriangleStrip   //in this way you will have all the vertice without repeat post T!,T2,T3,T4
};

enum class OCullType
{
	BackFace = 0,
	FrontFace,
	Both
};

enum class OWindingOrder
{
	ClockWise = 0,
	CounterClockWise
};

enum class OShaderType
{
	VertexShader = 0,
	FragmentShader
};

#define OGL3D_ERROR(message)\
{\
stringstream m;\
m<<"OGL3D Error: "<<message<<endl;\
throw runtime_error(m.str());\
}

#define OGL3D_WARNING(message)\
wclog<<"OGL3D Warning: "<<message<<endl;

#define OGL3D_INFO(message)\
wclog << "OGL3D Info: " << message << endl; 

