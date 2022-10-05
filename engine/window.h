#pragma once

#ifndef WINDOW_H
#define WINDOW_H

b8 initialize_window(const char* title, i32 _width, i32 _height);

b8 window_should_close();

b8 window_should_close();

void set_framebuffer_callback();

void destroy_window();

void* get_window_instance();

#endif // !WINDOW_H

