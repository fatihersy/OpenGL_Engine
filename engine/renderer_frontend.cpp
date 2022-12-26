#include "pch.h"
#include "renderer_frontend.h"

#include "renderer_backend.h"

frenderer_backend* backend = 0;

static b8 is_initialized = false;

// TODO: Temporary
static std::vector<fshape> shapes;

b8 renderer_system_initialize()
{
	if (is_initialized) return false;

	backend = new frenderer_backend;

	if(!renderer_backend_create(backend)) return false;

	is_initialized = true;

	return true;
}

b8 renderer_create_shape(u32 _ID, geometry_type type) 
{
	fshape shape = {};

	shape.ID = _ID;

	shape.x = 0;
	shape.y = 0;
	shape.z = 0;

	shape.height = 1;
	shape.width = 1;
	shape.scale = 1;

	shapes.push_back(shape);

	backend->renderer_create_default_geometry(shape, type);

	return true;
}

frenderer_backend* get_backend_instance()
{
	if (!is_initialized) return nullptr;

	return backend;
}

b8 renderer_system_shutdown() 
{
	renderer_backend_destroy(backend);

	return true;
}

b8 renderer_draw_frame() 
{
	backend->renderer_draw_frame(shapes);

	return true;
}