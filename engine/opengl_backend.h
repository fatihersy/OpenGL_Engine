#pragma once

#ifndef OPENGL_BACKEND_H
#define OPENGL_BACKEND_H

#include "defines.h"

#include "renderer_types.inl"

b8 opengl_renderer_backend_initialize(frenderer_backend* backend);
void opengl_renderer_backend_shutdown();

b8 opengl_renderer_create_geometry(fshape _shape, geometry_type _type);

void opengl_renderer_begin_frame();
void opengl_renderer_draw_frame(std::vector<fshape> out_shapes);
void opengl_renderer_end_frame();

#endif // !OPENGL_BACKEND_H
