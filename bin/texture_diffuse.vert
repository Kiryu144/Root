#version 330

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;

out vec3 out_fragPos;
out vec2 out_uv;
out vec3 out_normal;
  
uniform mat4 projection;
uniform mat4 view;
uniform mat4 transformation;
  
void main(){
	gl_Position = (projection * view * transformation * vec4(vertex, 1));

	out_fragPos = vertex;
	out_uv = uv;
	out_normal = normal;
 }