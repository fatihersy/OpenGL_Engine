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
	const char* MAIN_CONTENT = "//content";

}shader_enums;

typedef struct fshader 
{
private:
	string definitions = 
		"#version 330 core\n"
		"//layouts\n"
		"//variables\n";

	string main_func_base = 
		"void main()\n" 
		"{\n"
			"//content\n"
		"}\n";

	string  main_func_str;
	vec_str layouts;
	vec_str variables;

public:
	void add_layout(const char* location, const char* vector, const char* name)
	{
		//layout (location = 0) in vec3 aPos;
		shader_enums shader_enums;

		std::string text;
		text = "layout (location = " + std::string(location) + ") in " + vector + " " + name + ";";

		layouts.push_back(text);

		text += "\n";

		definitions = add_line(definitions, text.c_str(), shader_enums.LAYOUT);
	}

	void add_variable(const char* io, const char* vector, const char* name)
	{
		//out vec3 ourColor;
		shader_enums shader_enums;

		std::string text;
		text = io + std::string(" ") + vector + std::string(" ") + name + std::string(";");

		text += "\n";

		variables.push_back(text);

		definitions = add_line(definitions, text.c_str(), shader_enums.VARIABLE);
	}

	void delete_layout(const char* location)
	{
		//layout (location = 0) in vec3 aPos;
		auto location_str = std::string("(location = ") + location + ")";

		int index = string_vector_match_index(layouts, location_str);

		string layout_full_str = *(layouts.begin() + index);

		if (!layouts.empty()) 
		{
			layouts.erase(layouts.begin()+index);

			definitions = delete_line(definitions, layout_full_str.c_str());
		}
	}

	void delete_variable(const char* name)
	{		
		//out vec3 ourColor;

		int index = string_vector_match_index(variables, name);

		string var_full_str = *(variables.begin() + index);

		if (!variables.empty())
		{
			variables.erase(variables.begin() + index);
			// TODO:
			definitions = delete_line(definitions, var_full_str.c_str());
		}
	}

	void set_main_func(const char* text)
	{
		//"void main()\n"
		//	"{\n"
		//		"//content\n"
		//	"}";

		main_func_str = text;
	}

	void print_content()
	{
		shader_enums shader_enums;

		string _main = set_line(main_func_base, main_func_str.c_str(), shader_enums.MAIN_CONTENT);

		std::cout << definitions << _main << std::endl;
	}

	string get_content()
	{
		shader_enums shader_enums;

		string _main = set_line(main_func_base, main_func_str.c_str(), shader_enums.MAIN_CONTENT);

		return definitions + _main;
	}

} fshader;

#endif // !SHADER_SYSTEM_H
