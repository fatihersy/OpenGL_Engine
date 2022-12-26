#pragma once

#ifndef SDL2_H
#define SDL2_H

b8 SDL_Initialize();
b8 SDL_Shutdown();

b8 SDL_initialize_window(const char* title, int width, int height);
b8 SDL_initialize_renderer();

b8 SDL_platform_pump_message();

void SDL_renderer_begin_frame();
void SDL_renderer_end_frame();

void SDL_destroy_window();
void SDL_destroy_renderer();

#endif // 

