#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "texture.h"
#include "shader.h"
#include "vertex.h"
#include "object.h"
#include "renderable.h"
#include "gl_wrapper.h"

const int res_x = 640 * 2;
const int res_y = 360 * 2;
static float time = 0.0f;

static void pass_uniforms(shader_program shader);
static void proc_input(GLFWwindow *window, object *obj);

static const float SPEED 		= 25.0f;
static const float JUMP_POWER 	= 25.0f;
static const float GRAVITY 		= 1.2f;
static const float GRAVITY_CAP 	= 25.0f;

int main(int argc, char **argv) {
	printf("Hello, 'Silksong Form Grounnd Up'!\n");

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow *window = start_gl_glfw(res_x, res_y);
	get_gl_errors();

	shader_program default_shader = create_shader_from_files("res/shaders/fragment.glsl","res/shaders/vertex.glsl");
	
	object o  = create_object_from_texture(1.0f, "res/img/hornet.png", default_shader);
	object o1 = create_object_from_texture(1.0f, "res/img/lace.png", default_shader);
	object_position(&o1, -500.0f, 0.0f);

	get_gl_errors();


	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
		time += 0.01f;
		proc_input(window, &o);
		glClearColor(0.2, 0.6, 0.4, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
	
		draw_object(&o);
		draw_object(&o1);
		object_update(&o);

		pass_uniforms(default_shader);

		glfwSwapBuffers(window);
		glfwPollEvents();

		get_gl_errors();
	}
	
	glfwTerminate();
}

void pass_uniforms(shader_program shader) {
	GET_FN_GL_ERRORS(shader_uniform_i, (shader, "u_res_x", res_x));
	GET_FN_GL_ERRORS(shader_uniform_i, (shader, "u_res_y", res_y));
	GET_FN_GL_ERRORS(shader_uniform_f, (shader, "u_time", time));
	GET_FN_GL_ERRORS(shader_uniform_i, (shader, "u_texture", 0));
}

void proc_input(GLFWwindow *window, object *obj) {
	int input_pressed = 0;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		obj->velx = SPEED;
		input_pressed = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		obj->velx = -SPEED;
		input_pressed = 1;
	}
	if (!input_pressed) {
		obj->velx = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		obj->vely = JUMP_POWER;
	}
	else {
		obj->vely -= GRAVITY;
		if (obj->vely < -GRAVITY_CAP) {
			obj->vely = -GRAVITY_CAP;
		}
	}
}
