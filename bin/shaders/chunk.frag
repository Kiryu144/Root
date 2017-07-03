#version 330

in vec3 normal;
in vec3 fragPos;
in vec4 vertexColor;
in vec3 worldSpacePosition;

out vec4 color;

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform float ambientStrenght;

void main(){

//AMBIENT
	vec3 ambient = ambientStrenght * lightColor;

//DIFFUSE
	vec3 norm = normalize(normal);
	float diff = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = clamp(diff * lightColor, 0, 1);

	color = vec4((ambient + diffuse), 1) * vertexColor;
}
