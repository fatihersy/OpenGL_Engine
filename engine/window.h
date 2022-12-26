#pragma once

#ifndef WINDOW_H
#define WINDOW_H

b8 initialize_window_system(const char* title, i32 _width, i32 _height);

b8 shutdown_window_system();

void destroy_window();

#endif // !WINDOW_H

