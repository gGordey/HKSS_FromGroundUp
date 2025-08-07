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

int main(int argc, char **argv) {
	printf("Hello, 'Silksong Form Grounnd Up'!\n");

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow *window = start_gl_glfw(res_x, res_y);
	get_gl_errors();
	
	object o = create_object(200.0f, 200.0f);
	
	object o1 = create_object(1000.0f, 1000.0f);
	object_position(&o1, 100.0f, 100.0f);

	shader_program shader = create_shader_from_files("res/shaders/fragment.glsl","res/shaders/vertex.glsl");
	get_gl_errors();
	o.rend.shader = shader;
	o1.rend.shader = shader;

	texture hornet = load_texture("res/img/hornet.png");
	get_gl_errors();

	texture lace = load_texture("res/img/lace.png");
	get_gl_errors();

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
		time += 0.01f;
		proc_input(window, &o);
		glClearColor(0.2, 0.6, 0.4, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
	
		GET_FN_GL_ERRORS(glBindTexture, (GL_TEXTURE_2D, hornet.id));
		draw_object(&o);
		GET_FN_GL_ERRORS(glBindTexture, (GL_TEXTURE_2D, lace.id));
		draw_object(&o1);

		pass_uniforms(shader);

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

static const float step = 25.0f;
void proc_input(GLFWwindow *window, object *obj) {
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		obj->posx += step;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		obj->posx -= step;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		obj->posy += step;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		obj->posy -= step;
	}
}
