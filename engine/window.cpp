#include "pch.h"
#include "window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static GLFWwindow* window = 0;
static i32 width = 0;
static i32 height = 0;
static b8 is_initialized = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void* get_window_instance() 
{
	return window;
}

b8 initialize_window(const char* title, i32 _width, i32 _height) 
{
	if (is_initialized) return false;

	width = _width;
	height = _height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (!window)
	{
		std::cout << "Window Cannot Be Initialize!\n";
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	is_initialized = true;

	return true;
}

b8 window_should_close()
{
	return !glfwWindowShouldClose(window);
}

void set_framebuffer_callback()
{
	glViewport(0, 0, width, height);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void destroy_window() 
{
	glfwDestroyWindow(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
