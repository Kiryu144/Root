#version 330

layout(location = 0) in vec3 _vertex;
layout(location = 1) in vec3 _normal;
layout(location = 2) in vec4 _vertexColor;

out vec3 normal;
out vec3 fragPos;
out vec4 vertexColor;
out vec3 worldSpacePosition;
  
uniform mat4 projection;
uniform mat4 view;
uniform mat4 transformation;
  
void main(){
  gl_Position = (projection * view * transformation * vec4(_vertex, 1));
  
  vec3 position = transformation[3].xyz;

  normal = _normal;
  fragPos = vec3(gl_Position);
  vertexColor = _vertexColor;
  worldSpacePosition = worldSpacePosition;
 }