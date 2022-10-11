#pragma once

#ifndef WINDOW_H
#define WINDOW_H

b8 initialize_window(const char* title, i32 _width, i32 _height);

b8 window_should_close();

void set_framebuffer_callback();

void destroy_window();

void glfw_begin_frame();

void glfw_end_frame();

void* get_window_instance();

#endif // !WINDOW_H

