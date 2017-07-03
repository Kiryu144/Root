#version 330

layout(location = 0) in vec3 _vertex;
layout(location = 1) in vec2 _uv;

out vec2 UV;
  
uniform mat4 projection;
uniform mat4 view;
uniform mat4 transformation;

uniform vec2 normalizedWindowSize;
  
void main(){
	vec3 vertexWorldPos = transformation[3].xyz + _vertex;

	gl_Position = (projection * view) * vec4(vertexWorldPos, 1);
	gl_Position /= gl_Position.w;
	gl_Position.xy += _vertex.xy * vec2(length(transformation[1].xyz) * normalizedWindowSize.y, length(transformation[2].xyz) * normalizedWindowSize.x);
	UV = _uv * -1;
}