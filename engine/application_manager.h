#pragma once

#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include <vector>

class Application_manager
{
public:

	 Application_manager();
	~Application_manager();

	b8 create_application();
	b8 is_running();

	void update_renderer();
	void update_systems();

private:

};








#endif // !APPLICATIONS_MANAGER_H


