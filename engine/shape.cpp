#include "pch.h"
#include "shape.h"

#include <defines.h>

#include "shader.h"
#include "primitives.h"

glshape initialize_shape(primitive_types _type, const char* texture_path)
{
	glshape shape;

	shape.type = _type;

	if (!create_program("vertex.vert", "fragment.frag")) return shape;

	shape.program_handle = get_last_program_id();
	shape.indice_count = get_indice_count(shape.type);
	shape.VAO = bind_vertex_data(shape.type);
	if(texture_path != "") shape.texture_handle = generate_texture(texture_path, GL_TEXTURE_2D);

	return shape;
}