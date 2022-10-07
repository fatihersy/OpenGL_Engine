#include "pch.h"
#include "shape.h"

#include <defines.h>

#include "shader.h"
#include "primitives.h"

glshape initialize_shape(primitive_types _type)
{
	glshape shape;

	shape.type = _type;

	if (!create_program("vertex.vert", "fragment.frag")) return shape;

	shape.program_handle = get_last_program_id();

	shape.indice_count = get_indice_count(shape.type);

	shape.VAO = bind_vertex_data(shape.type);

	return shape;
}