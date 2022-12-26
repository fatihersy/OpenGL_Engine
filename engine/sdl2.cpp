#include "pch.h"
#include "sdl2.h"

#include "SDL2/SDL.h"
#include "glad/glad.h"

#include "event.h"
#include "input.h"

static b8 is_initialized = false;
static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;
static SDL_Event e = { 0 };
static SDL_GLContext gl_context;

b8 SDL_Initialize() 
{
	if (is_initialized) return false;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
	
	SDL_GL_LoadLibrary(NULL); // Default OpenGL is fine.

	// Request an OpenGL 4.5 context (should be core)
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	// Also request a depth buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// Request a debug context.
	SDL_GL_SetAttribute(
		SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG
	);

	is_initialized = true;

	return true;
}

b8 SDL_Shutdown() 
{
	SDL_Quit();
	return true;
}

b8 SDL_initialize_window(const char* title, int width, int height) 
{
	if (!is_initialized) return false;

	window = SDL_CreateWindow(
		title, 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );
	if (!window)
	{
		fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
		return false;
	}

	gl_context = SDL_GL_CreateContext(window);
	if (gl_context == NULL) 
	{
		fprintf(stderr, "SDL_GL_CreateContext error: %s\n", SDL_GetError());
		return false;
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cout << "Failed to Load GLAD!" << std::endl;
		return false;
	}

	SDL_GetWindowSize(window, &width, &height);
	glViewport(0, 0, width, height);

	return true;
}

b8 SDL_platform_pump_message() 
{
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
			/* Look for a keypress */
		case SDL_KEYDOWN:
			/* Check the SDLKey values and move change the coords */
			switch (e.key.keysym.sym) {
			case SDLK_ESCAPE:
				event_fire(KEY_ESCAPE, 0, event_context {0});
				break;
			case SDLK_w:

				break;
			case SDLK_s:

				break;
			case SDLK_a:

				break;
			case SDLK_d:

				break;
			default:
				break;
			}
		}
	}

	return true;
}

b8 SDL_initialize_renderer() 
{
	if (!is_initialized) return false;

	if (!window) return false;

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer) return false;

	return true;
}

void SDL_renderer_begin_frame() 
{
	glClearColor(0.0f, 0.5f, 1.0f, 0.0f);

	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 200, 50, 100, 255);
}

void SDL_renderer_end_frame() 
{
	SDL_RenderPresent(renderer);
}

void SDL_destroy_window() 
{
	SDL_DestroyWindow(window);
}

void SDL_destroy_renderer() 
{
	SDL_DestroyRenderer(renderer);
}
