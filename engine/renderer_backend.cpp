#include "pch.h"
#include "renderer_backend.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "window.h"
#include "input.h"

#include "renderer_types.inl"

static b8 is_initialized = false;

b8 renderer_backend_create(frenderer_backend* backend) 
{
	if (is_initialized) return false;

	if (!glfwInit()) return false;

	if (!initialize_window(backend->window.title, 
						 backend->window.width, 
						 backend->window.height)) 
	return false;

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to Load GLAD!" << std::endl;
		renderer_backend_destroy();
		return false;
	}

	set_framebuffer_callback();

	backend->renderer_input_initialize = initialize_input;
	backend->define_key_event = define_key_event;
	backend->update_input_system = update_input_system;
	backend->get_window_instance = get_window_instance;
	backend->renderer_begin_frame = glfw_begin_frame;
	backend->renderer_end_frame = glfw_end_frame;
	backend->window_should_close = window_should_close;

	backend->window.handle = (GLFWwindow*) get_window_instance();

	is_initialized = true;

	return true;
}

void renderer_backend_destroy() 
{
	destroy_window();

	glfwTerminate();
}



/*

void draw_shape(glshape shape)
{
	glUseProgram(shape.program_handle);

	if (shape.texture_handle) glBindTexture(GL_TEXTURE_2D, shape.texture_handle);

	glBindVertexArray(shape.VAO);
	glDrawElements(GL_TRIANGLES, shape.indice_count, GL_UNSIGNED_INT, 0);
}



b8 renderer_begin_loop()
{
	return window_should_close();
}

b8 terminate_renderer()
{

	return true;
}

*/