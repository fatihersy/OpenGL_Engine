#pragma once

#ifndef INPUT_H
#define INPUT_H

typedef enum APP_KEY_EVENT {
	APPLICATION_KEY_EVENT_UNDEFINED = 0,
	APPLICATION_KEY_EVENT_QUIT,
	APPLICATION_PING_INPUT,
	APPLICATION_CLEAR_CONSOLE,
	APPLICATION_SWITCH_POLY_MOD
} APP_KEY_EVENT;

b8 initialize_input();

b8 define_key_event(i32 code, APP_KEY_EVENT event);

b8 update_input();

#endif // !INPUT_H


