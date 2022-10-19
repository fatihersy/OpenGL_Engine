#include "pch.h"
#include "renderer_backend.h"

#include "opengl_backend.h"

static b8 is_initialized = false;

b8 renderer_backend_create(frenderer_backend* backend) 
{
	if (is_initialized) return false;

	if (!opengl_renderer_backend_initialize(backend)) return false;

	backend->renderer_input_initialize = opengl_renderer_input_initialize;
	backend->define_key_event = opengl_renderer_define_key_event;
	backend->update_input_system = opengl_renderer_update_input;
	backend->get_window_instance = opengl_renderer_get_window;
	backend->renderer_begin_frame = opengl_renderer_begin_frame;
	backend->renderer_end_frame = opengl_renderer_end_frame;
	backend->window_should_close = opengl_renderer_window_should_close;
	backend->renderer_create_default_geometry = opengl_renderer_create_geometry;
	backend->renderer_draw_frame = opengl_renderer_draw_frame;

	backend->window.handle = opengl_renderer_get_window();

	is_initialized = true;

	return true;
}

void renderer_backend_destroy(frenderer_backend* backend)
{
	backend->renderer_input_initialize = 0;
	backend->define_key_event		    = 0;
	backend->update_input_system		= 0;
	backend->get_window_instance		= 0;
	backend->renderer_begin_frame		= 0;
	backend->renderer_end_frame		= 0;
	backend->window_should_close		= 0;
	backend->window.handle			= 0;
}



/*

void draw_shape(glshape shape)
{
	glUseProgram(shape.program_handle);

	if (shape.texture_handle) glBindTexture(GL_TEXTURE_2D, shape.texture_handle);

	glBindVertexArray(shape.VAO);
	glDrawElements(GL_TRIANGLES, shape.indice_count, GL_UNSIGNED_INT, 0);
}

*/