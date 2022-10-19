#pragma once

#ifndef RENDERER_FRONTEND_H
#define RENDERER_FRONTEND_H

#include "renderer_types.inl"

b8 renderer_system_initialize(const char* title, i32 width, i32 height);
b8 renderer_system_shutdown();

frenderer_backend* get_backend_instance();

b8 renderer_draw_frame();

b8 renderer_create_shape(u32 ID, geometry_type type);

// ON RESIZE WINDOW

// DRAW FRAME

// CREATE & DESTROY & RESIZE TEXTURE

// CREATE & DESTROY & DRAW GEOMETRY



// SHADER STUFF

// RENDERBUFFER & RENDERPASS STUFF
 
#endif // !RENDERER_BACKEND_H
