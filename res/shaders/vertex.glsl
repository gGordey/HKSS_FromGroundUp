#version 330 core
layout(location = 0) in vec4 pos;
layout(location = 1) in vec2 texCoord;

out vec2 UV;

uniform sampler2D u_texture;
uniform float u_time;
uniform int u_res_x;
uniform int u_res_y;

void main() {
	float final_x = pos.x / u_res_x;
	float final_y = pos.y / u_res_y;
	gl_Position = vec4(final_x, final_y, 1.0, 1.0);

	UV = texCoord;
} 
