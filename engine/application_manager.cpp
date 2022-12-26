#include "pch.h"

#include "application_manager.h"

#include "renderer_frontend.h"
#include "transformations.h"

#include "shader_system.h"
#include "event.h"
#include "window.h"
#include "platform.h"
#include "input.h"

typedef struct application_state
{
	b8 _is_running;
	b8 _is_suspended;

} application_state;

static application_state* app_state;

static frenderer_backend* backend;

b8 application_on_event(u16 code, void* sender, void* listener_inst, event_context context);

Application_manager::Application_manager() 
{
	app_state = new application_state;
	backend = new frenderer_backend;

	app_state->_is_running = false;
	app_state->_is_suspended = false;
}

Application_manager::~Application_manager() 
{
	delete backend;
	delete app_state;
}

b8 Application_manager::create_application()
{
	if(!initialize_core_systems()) return false;

	if(!initialize_window_system("MY ENGINE", 800, 600)) return false;

	if(!renderer_system_initialize()) return false;

	initialize_event_system();

	if(!initialize_input_system()) return false;

	backend = get_backend_instance();

	// TODO: INIT INPUT

	//renderer_create_shape(1, QUAD);

	fshader shader;

	shader.add_layout("0", "vec3", "aPos");
	shader.add_layout("1", "vec3", "aColor");
	shader.add_layout("2", "vec2", "aTexCoord");

	shader.add_variable("out", "vec3", "ourColor");
	shader.add_variable("out", "vec2", "TexCoord");

	shader.set_main_func
	(
		"	gl_Position = vec4(aPos, 1.0);\n"
		"	ourColor = aColor;\n"
		"	TexCoord = aTexCoord;\n"
	);

	std::cout << shader.get_content();

	event_register(KEY_ESCAPE, 0, application_on_event);
	//event_register(APPLICATION_KEY_UP, 0, application_on_event, event_context {});

	app_state->_is_running = true;

	return true;
}


b8 Application_manager::is_running() 
{
	if (!platform_pump_message())
	{
		std::cout << "Application is stopped working. Shutting Down." << std::endl;
		return false;
	}

	if (!app_state->_is_running) 
	{
		std::cout << "Application is stopped working. Shutting Down." << std::endl;
		return false;
	}

	if(app_state->_is_suspended)
	{
		std::cout << "Application is suspended. Shutting Down!" << std::endl;
		return false;
	}

	return true;
}

void Application_manager::update_renderer()
{
	backend->renderer_begin_frame();

	if (!renderer_draw_frame()) app_state->_is_suspended = true;

	backend->renderer_end_frame();
}

void Application_manager::update_systems() 
{

}

b8 application_on_event(u16 code, void* sender, void* listener_inst, event_context context)
{
	switch (code)
	{
	case KEY_ESCAPE:
		app_state->_is_running = false;
		break;

	default:
		break;
	}

	return true;
}

