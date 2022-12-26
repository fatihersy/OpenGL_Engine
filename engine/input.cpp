#include "pch.h"
#include "input.h"

#include <vector>

#include "sdl2.h"
#include "event.h"

static b8 is_initialized = false;

b8 initialize_input_system()
{
	if (is_initialized) return false;

	is_initialized = true;

	return true;
}

b8 shutdown_input_system()
{
	if (!is_initialized) return false;

	is_initialized = false;

	return true;
}

void process_key_input(keys key)
{
	event_fire(key, 0, event_context {0});
}