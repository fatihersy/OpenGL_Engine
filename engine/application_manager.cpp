#include "pch.h"

#include "application_manager.h"

#include "renderer_frontend.h"
#include "transformations.h"

#include "shader_system.h"

static frenderer_backend backend;


Application_manager::Application_manager() 
{
	this->_is_running = false;
	this->_is_suspended = false;
}

Application_manager::~Application_manager() 
{
	backend = { 0 };
}

b8 Application_manager::create_application()
{
	if (!renderer_system_initialize("Hello OpenGL", 800, 640)) return false;

	backend = *get_backend_instance();

	if (!backend.renderer_input_initialize()) return false;

	backend.define_key_event(GLFW_KEY_ESCAPE, APPLICATION_KEY_EVENT_QUIT);
	backend.define_key_event(GLFW_KEY_W, APPLICATION_PING_INPUT);
	backend.define_key_event(GLFW_KEY_SPACE, APPLICATION_CLEAR_CONSOLE);
	backend.define_key_event(GLFW_KEY_P, APPLICATION_SWITCH_POLY_MOD);

	renderer_create_shape(1, QUAD);

	fshader shader;

	shader.add_layout("0", "vec3", "aPos");
	shader.add_layout("1", "vec3", "aColor");
	shader.add_layout("2", "vec2", "aTexCoord");

	shader.add_variable("out", "vec3", "ourColor");
	shader.add_variable("out", "vec2", "TexCoord");

	shader.delete_layout("0");

	shader.print_content();

	_is_running = true;

	return true;
}


b8 Application_manager::is_running() 
{
	if(this->_is_suspended) 
	{
		std::cout << "Application is suspended. Shutting Down!" << std::endl;
		return false;
	}

	if (!this->_is_running)
	{
		std::cout << "Application is stopped working. Shutting Down." << std::endl;
		return false;
	}

	return backend.window_should_close();
}

void Application_manager::update_renderer()
{
	backend.renderer_begin_frame();

	if (!renderer_draw_frame()) this->_is_suspended = true;

	backend.renderer_end_frame();
}

void Application_manager::update_systems() 
{
	backend.update_input_system
	(
		backend.window.handle
	);


}