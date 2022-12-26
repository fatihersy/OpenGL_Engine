#include "pch.h"
#include "renderer_backend.h"

#include "opengl_backend.h"

static b8 is_initialized = false;

b8 renderer_backend_create(frenderer_backend* backend) 
{
	if (is_initialized) return false;

	if (!opengl_renderer_backend_initialize(backend)) return false;

	backend->renderer_begin_frame = opengl_renderer_begin_frame;
	backend->renderer_end_frame = opengl_renderer_end_frame;
	backend->renderer_draw_frame = opengl_renderer_draw_frame;
	backend->renderer_create_default_geometry = opengl_renderer_create_geometry;

	is_initialized = true;

	return true;
}

void renderer_backend_destroy(frenderer_backend* backend)
{
	backend->renderer_begin_frame			  = 0;
	backend->renderer_end_frame			  = 0;
	backend->renderer_create_default_geometry = 0;
	backend->renderer_draw_frame			  = 0;
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