#pragma once

#ifndef INPUT_H
#define INPUT_H

#include "renderer_types.inl"

b8 input_initialize();

b8 input_shutdown();

b8 define_key_event(i32 code, APP_KEY_EVENT event);

b8 update_input_system(void* window);

#endif // !INPUT_H


