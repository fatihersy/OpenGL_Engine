#include "pch.h"
#include "application.h"

#include "renderer_init.h"
#include "input.h"

static b8 is_running = false;

b8 application_create() 
{
	if (!initialize_renderer("Hello OpenGL", 800, 640)) return false;

	initialize_input();

	define_key_event(GLFW_KEY_ESCAPE,  APPLICATION_KEY_EVENT_QUIT);
	define_key_event(GLFW_KEY_W,		APPLICATION_PING_INPUT);
	define_key_event(GLFW_KEY_SPACE,   APPLICATION_CLEAR_CONSOLE);
	define_key_event(GLFW_KEY_P, APPLICATION_SWITCH_POLY_MOD);

	is_running = true;

	return true;
}

b8 application_run() 
{
	while (renderer_begin_loop() && is_running)
	{
		renderer_begin_render();

		renderer_update();

		renderer_end_render();

		update_input();
	}

	terminate_renderer();

	return true;
}
