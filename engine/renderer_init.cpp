#include "pch.h"
#include "renderer_init.h"

#include "window.h"
#include "gl_types.h"

#include "GLFW/glfw3.h"

static b8 is_initialized = false;

void draw_shape(glshape shape);

b8 initialize_renderer(const char* title, i32 width, i32 height) 
{
	if (is_initialized) return false;

	if (!glfwInit()) return false;

	if(!initialize_window(title, width, height)) return false;

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to Load GLAD!" << std::endl;
		terminate_renderer();
		return false;
	}

	set_framebuffer_callback();

	// TODO: ...  shape = initialize_shape(primitive_types::TRIANGLE, "wall.jpg");

	is_initialized = true;

	return true;
}

b8 renderer_update() 
{
	//draw_shape(shape);

	return true;
}

void draw_shape(glshape shape) 
{
	glUseProgram(shape.program_handle);

	if (shape.texture_handle) glBindTexture(GL_TEXTURE_2D, shape.texture_handle);

	glBindVertexArray(shape.VAO);
	glDrawElements(GL_TRIANGLES, shape.indice_count, GL_UNSIGNED_INT, 0);
}

void renderer_begin_render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(0.5f, 0.1f, 0.2f, 1.0f);
}

void renderer_end_render()
{
	glfwSwapBuffers((GLFWwindow*)get_window_instance());

	glfwPollEvents();
}

b8 renderer_begin_loop()
{
	return window_should_close();
}

b8 terminate_renderer()
{
	destroy_window();

	glfwTerminate();

	return true;
}
