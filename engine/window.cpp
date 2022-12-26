#include "pch.h"
#include "window.h"

#include "sdl2.h"

typedef struct fwindow
{
	void* handle;

	const char* title;
	i32 width;
	i32 height;

} fwindow;

static fwindow* window = { 0 };

static b8 is_initialized = false;

b8 initialize_window_system(const char* title, i32 _width, i32 _height)
{
	if (is_initialized) return false;

	window = new fwindow;

	window->width = _width;
	window->height = _height;
	window->title = title;

	if(!SDL_initialize_window(
		window->title, 
		window->width, 
		window->height)) return false;

	is_initialized = true;

	return true;
}

b8 shutdown_window_system() 
{
	if (!is_initialized) return false;

	destroy_window();

	return true;
}

void destroy_window() 
{
	SDL_destroy_window();
}

