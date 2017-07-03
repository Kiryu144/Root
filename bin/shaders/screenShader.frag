#version 330

in vec2 UV;

out vec4 color;

uniform sampler2D textureSampler;
uniform float time;

void main() {
	color = texture(textureSampler, UV) * vec4(abs(sin(time)), 0, abs(cos(time)), 1);
}

