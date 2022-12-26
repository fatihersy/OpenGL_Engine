#include "pch.h"
#include "opengl_backend.h"

#include "gl_types.inl"

#include "sdl2.h"
#include "shader.h"
#include "geometry_system.h"

static b8 is_initialized = false;

std::vector<glshape> glshapes = {};

b8 opengl_renderer_backend_initialize(frenderer_backend* backend)
{
	if (is_initialized) return false;

	SDL_initialize_renderer();

	is_initialized = true;

	return true;
}

void opengl_renderer_backend_shutdown() {  }

b8 opengl_renderer_create_geometry(fshape _shape, geometry_type _type) 
{
	glshape shape = {};

	shape.ID = _shape.ID;
	shape.type = _type;

	if(!create_program("vertex.vert", "fragment.frag")) return false;
	shape.program_handle = get_last_program_id();
	
	if(!generate_texture("wall.jpg", GL_TEXTURE_2D)) return false;
	shape.texture_handle = get_last_texture_id();
	
	std::vector<vertex_attribs> attribs = {POSITION, COLOR, TEXTURE};
	shape.VAO = bind_vertex_data(shape.type, attribs);

	shape.indice_count = get_indice_count(shape.type);

	glshapes.push_back(shape);

	return true;
}

void  opengl_renderer_begin_frame() 
{
	SDL_renderer_begin_frame();
}
void  opengl_renderer_end_frame()	 
{ 
	SDL_renderer_end_frame();
}

void opengl_renderer_draw_frame(std::vector<fshape> out_shapes) 
{
	for (const glshape shape : glshapes)
	{
		//glUseProgram(shape.program_handle);

		//if (shape.texture_handle) glBindTexture(GL_TEXTURE_2D, shape.texture_handle);

		//glBindVertexArray(shape.VAO);
		//glDrawElements(GL_TRIANGLES, shape.indice_count, GL_UNSIGNED_INT, 0);
	}
}
