#pragma once

#include <iostream>

#include <defines.h>

#include "application.h"

extern b8 create_client();

int main(void) 
{
	if(!application_create()) std::cout << "App Cannot Create!\n";
	
	if(!create_client()) return -1;

	if(!application_run()) std::cout << "App Closed\n";

	return 0;
}