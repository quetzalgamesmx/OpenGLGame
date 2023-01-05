#version 410 core //the last version compatible with Mac OS is 4.10

layout (row_major) uniform UniformData
{
	mat4 world;
	mat4 projection;
};

layout(location= 0) in vec3 position;
layout(location= 1) in vec2 texcoord;

layout(location= 0) out vec3 vertoutColor;

void main()
{
   vec4 pos = vec4(position,1) * world;
   pos = pos* projection;

   gl_Position = pos;

   vertoutColor = vec3(texcoord.x,texcoord.y,0);
}