#version 330 core
layout(location = 0) out vec4 color;
uniform float u_time;
uniform sampler2D u_texture;
in vec2 UV;
void main() {
	vec4 texCol = texture(u_texture, UV);
	color = texCol;// vec4(abs(sin(time * 1.5)), abs(sin(time * 9)), abs(sin(time * 0.8)), 1.0);
}
