#version 330

in vec3 out_fragPos;
in vec2 out_uv;
in vec3 out_normal;

out vec4 color;

uniform mat4 transformation;
uniform vec3 pointLight;

void main(){
	mat3 normalMatrix = transpose(inverse(mat3(transformation)));
	vec3 translatedNormal = normalize(normalMatrix * out_normal);
	vec3 translatedFragPosition = vec3(transformation * vec4(out_fragPos, 1));

//AMBIENT
	float ambientStrenght = 0.3;

//POINT
	vec3 surfaceToLight = pointLight - translatedFragPosition;
	float brightness = dot(translatedNormal, surfaceToLight) / (length(surfaceToLight) * length(translatedNormal));
	float distanceToLight = length(pointLight - translatedFragPosition);
	float attenuation = 10.0 / (1.0 + 0.5 * pow(distanceToLight, 2));
	brightness = clamp(brightness, 0, 1);
	attenuation = clamp(attenuation, 0, 0.85);


	color = vec4(0.25, 0.5, 0.25, 1) * (brightness + ambientStrenght) * attenuation;
}
