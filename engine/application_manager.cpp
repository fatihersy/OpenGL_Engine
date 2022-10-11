#include "pch.h"
#include "application_manager.h"

#include "renderer_init.h"
#include "transformations.h"
#include "input.h"

#include <vector>

Application_manager::Application_manager() 
{
	this->_is_running = false;
	this->_is_suspended = false;
	this->shapes = {};
}

Application_manager::~Application_manager() 
{
	terminate_renderer();
}

void Application_manager::create_shape()
{
	fshape shape = {};

	shape.ID = (u32) shapes.size();

	shape.x = 0;
	shape.y = 0;
	shape.z = 0;

	shape.height = 1;
	shape.width = 1;
	shape.scale = 1;



	shapes.push_back(shape);
}

b8 Application_manager::create_application()
{
	if (!initialize_renderer("Hello OpenGL", 800, 640)) return false;

	if (!initialize_input()) return false;

	define_key_event(GLFW_KEY_ESCAPE, APPLICATION_KEY_EVENT_QUIT);
	define_key_event(GLFW_KEY_W, APPLICATION_PING_INPUT);
	define_key_event(GLFW_KEY_SPACE, APPLICATION_CLEAR_CONSOLE);
	define_key_event(GLFW_KEY_P, APPLICATION_SWITCH_POLY_MOD);

	_is_running = true;

	return true;
}

void Application_manager::renderer_loop() 
{
	renderer_begin_render();

	if (!renderer_update()) this->_is_suspended = true;

	renderer_end_render();
}

b8 Application_manager::is_running() 
{
	return 
	(
		renderer_begin_loop() 
		& this->_is_running 
		& this->_is_suspended
	);
}

b8 Application_manager::update_systems() 
{
	return update_input();
}