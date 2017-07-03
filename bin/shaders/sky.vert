#version 330

layout(location = 0) in vec3 _vertex;
  

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transformation;

varying vec3 vertex;
  
void main(){
	vertex = _vertex.xyz;
	gl_Position = (projection * view * transformation * vec4(_vertex, 1));
}