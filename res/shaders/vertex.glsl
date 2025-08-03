#version 330 core
layout(location = 0) in vec4 pos;
layout(location = 1) in vec2 texCoord;

out vec2 UV;

uniform sampler2D u_texture;
uniform float time;
uniform int res_x;
uniform int res_y;
void main() {
	float final_x = pos.x / res_x;
	float final_y = pos.y / res_y;
	if (final_y < 0.2) {
		gl_Position = vec4(final_x, final_y, 1.0, 1.0);
	}
	else {
		gl_Position = vec4((pos.x / res_x) + sin(time * 3) * 0.4, pos.y / res_y, 1.0, 1.0);
	}

	UV = texCoord;
} 
