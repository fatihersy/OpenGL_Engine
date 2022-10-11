#include "pch.h"
#include "renderer_frontend.h"

#include "renderer_backend.h"

frenderer_backend* backend;

static b8 is_initialized = false;

b8 renderer_system_initialize(const char* title, i32 width, i32 height)
{
	backend = new frenderer_backend;

	backend->window.title = title;
	backend->window.width = width;
	backend->window.height = height;

	if(!renderer_backend_create(backend)) return false;

	is_initialized = true;

	return true;
}

frenderer_backend* get_backend_instance()
{
	if (!is_initialized) return nullptr;

	return backend;
}

b8 renderer_system_shutdown() 
{
	backend = nullptr;

	renderer_backend_destroy();

	return true;
}

b8 renderer_draw_frame() 
{


	return true;
}