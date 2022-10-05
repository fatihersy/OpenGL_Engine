#pragma once

#ifndef RENDERER_INIT_H
#define RENDERER_INIT_H

#include <defines.h>

b8 initialize_renderer(const char* title, i32 width, i32 height);

b8 terminate_renderer();

b8 renderer_begin_loop();

b8 renderer_update();

void renderer_begin_render();

void renderer_end_render();

void initialize_shape();

#endif // !RENDERER_INIT_H
