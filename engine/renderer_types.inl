#pragma once

#include <vector>

#include <defines.h>

template<typename T> u64 VECTOR_SIZE(std::vector<T> vector)
{
	return vector.size() * sizeof(T);
}

typedef enum primitive_types
{
	TRIANGLE,
	QUAD
} primitive_types;

typedef struct fshape
{
	u32 ID;

	i32 width;
	i32 height;
	i32 scale;

	i32 x;
	i32 y;
	i32 z;
} fshape;

typedef enum APP_KEY_EVENT {
	APPLICATION_KEY_EVENT_UNDEFINED = 0,
	APPLICATION_KEY_EVENT_QUIT,
	APPLICATION_PING_INPUT,
	APPLICATION_CLEAR_CONSOLE,
	APPLICATION_SWITCH_POLY_MOD
} APP_KEY_EVENT;

typedef struct fwindow
{
	void* handle;

	const char* title;
	i32 width;
	i32 height;

} fwindow;

typedef struct render_packet 
{
	f32 delta_time;

	const std::vector<fshape> views;
};

typedef struct frenderer_backend 
{
	fwindow window;

	b8 (*renderer_input_initialize) ();

	b8 (*define_key_event) (i32 code, APP_KEY_EVENT event);

	b8 (*update_input_system) (void* window);

	b8 (*window_should_close) ();

	void (*renderer_begin_frame) ();

	void (*renderer_end_frame) ();

	void* (*get_window_instance) ();

} frenderer_backend;

