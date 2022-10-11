#include "pch.h"
#include "application.h"

#include "application_manager.h"

Application_manager app_manager;

b8 application_create() 
{
	if (!app_manager.create_application()) return false;

	return true;
}

b8 application_run() 
{
	while (app_manager.is_running())
	{
		app_manager.renderer_loop();

		app_manager.update_systems();
	}



	return true;
}
