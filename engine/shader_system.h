#pragma once

#ifndef SHADER_SYSTEM_H
#define SHADER_SYSTEM_H

#include "defines.h"
#include "ftool.h"
#include "fstring.h"

typedef struct shader_enums 
{
	const char* LAYOUT = "//layouts";
	const char* VARIABLE = "//variables";

}shader_enums;

typedef struct fshader 
{
private:
	std::string content = 
		"#version 330 core\n"
		"//layouts\n"
		"//variables\n";

	std::vector<std::string> layouts;
	std::vector<std::string> variables;

public:
	void add_layout(const char* location, const char* vector, const char* name)
	{
		//layout (location = 0) in vec3 aPos;
		shader_enums shader_enums;

		std::string text;
		text = "layout (location = " + std::string(location) + ") in " + vector + " " + name + "\n";

		layouts.push_back(text);

		content = add_line(content, text.c_str(), shader_enums.LAYOUT);
	}

	void add_variable(const char* io, const char* vector, const char* name)
	{
		//out vec3 ourColor;
		shader_enums shader_enums;

		std::string text;
		text = io + std::string(" ") + vector + std::string(" ") + name + "\n";

		variables.push_back(text);

		content = add_line(content, text.c_str(), shader_enums.VARIABLE);
	}

	void delete_layout(const char* location)
	{
		//layout (location = 0) in vec3 aPos;
		auto text = std::string("(location = ") + location + ")";

		string_vector_match_index(layouts, text);

		if (!layouts.empty()) 
		{
			//layouts.erase();

			content = delete_line(content, text.c_str());
		}
	}

	void delete_variable(const char* name)
	{

	}

	void print_content()
	{
		std::cout << content << std::endl;
	}

} fshader;

#endif // !SHADER_SYSTEM_H
