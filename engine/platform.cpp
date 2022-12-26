#include "pch.h"
#include "platform.h"

#include "sdl2.h"

static b8 is_initialize = false;

b8 initialize_core_systems() 
{
	if(is_initialize) return false;

	SDL_Initialize();

	is_initialize = true;

	return true;
}

b8 shutdown_core_systems() 
{
	if (!is_initialize) return false;

	return SDL_Shutdown();
}

b8 platform_pump_message() 
{
	return SDL_platform_pump_message();
}
