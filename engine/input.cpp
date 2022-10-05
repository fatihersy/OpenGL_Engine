#include "pch.h"
#include "input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "window.h"

static b8 is_initialized = false;

static std::vector<i32> previous_pressed = {};
static std::vector<i32> pressed = {};

std::vector<std::pair<i32, APP_KEY_EVENT>> key_events = {};

b8 initialize_input() 
{
	if (is_initialized) return false;

	is_initialized = true;

	return true;
}

b8 define_key_event(i32 code, APP_KEY_EVENT code_event) 
{
	if (!is_initialized) return false;

	key_events.push_back(std::pair(code, code_event));
}

b8 update_input() 
{
	if (!is_initialized) return false;

	std::vector<APP_KEY_EVENT> event_queue = {};

	for(auto var : key_events)
	{
		if(glfwGetKey((GLFWwindow*)get_window_instance(), var.first)) 
		{
			pressed.push_back(var.first);

			event_queue.push_back(var.second);
		}
	}

	for (auto var : event_queue)
	{
		switch (var)
		{
		case APPLICATION_KEY_EVENT_UNDEFINED: return false; 
		break;

		case APPLICATION_KEY_EVENT_QUIT:
			glfwSetWindowShouldClose((GLFWwindow*)get_window_instance(), GL_TRUE);
		break;

		case APPLICATION_PING_INPUT:
			std::cout << "IT'S INPUT LAYER" << std::endl;
		break;

		case APPLICATION_CLEAR_CONSOLE:
			system("cls");
		break;

		case APPLICATION_SWITCH_POLY_MOD:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;

		default: return false;
		}
	}

	previous_pressed = pressed;

	pressed.clear();

	return true;
}
