#version 330

layout(location = 0) in vec3 _vertex;
layout(location = 1) in vec2 _uv;

out vec2 UV;
  
void main(){
	//gl_Position = (vec4(_vertex, 1) + vec4(-1, -1, 0, 0));
	//gl_Position = vec4(_vertex, 1);
	gl_Position = vec4(_vertex * 2, 1) + vec4(-1, -1, 0, 0);

	UV = _uv;
 }