#pragma once

#ifndef OPENGL_BACKEND_H
#define OPENGL_BACKEND_H

#include "defines.h"

#include "renderer_types.inl"

b8 opengl_renderer_backend_initialize(frenderer_backend* backend);
void opengl_renderer_backend_shutdown();

b8 opengl_renderer_input_initialize();
void opengl_renderer_input_shutdown();

b8 opengl_renderer_define_key_event(i32 code, APP_KEY_EVENT code_event);
b8 opengl_renderer_update_input(void* window);

b8 opengl_renderer_create_geometry(fshape _shape, geometry_type _type);

b8 opengl_renderer_window_should_close();
void* opengl_renderer_get_window();

void opengl_renderer_begin_frame();
void opengl_renderer_draw_frame(std::vector<fshape> out_shapes);
void opengl_renderer_end_frame();

#endif // !OPENGL_BACKEND_H
