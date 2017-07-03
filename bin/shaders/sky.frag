#version 330

out vec4 color;

uniform sampler2D colorMap;
uniform float time;

varying vec3 vertex;

void main(){
	vec3 V = normalize(vertex);	
	color = texture2D(colorMap, vec2(1 - time, 0.5 + (V.y/-2)));
	//color *= vec4(0.0001);
	//color += vec4(1, 0, 0, 1);
}
