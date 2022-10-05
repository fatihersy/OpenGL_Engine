#include "pch.h"
#include "file_stream.h"

#include <fstream>

std::string read_file(const char* file_name) 
{

	std::string path = "../engine/";
	path += file_name;

	std::ifstream file(path, std::ios::in);

	std::string line;
	std::string content;

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			content.append(line + "\n");
		}
		file.close();
	}
	else std::cout << "File cannot be found!" << std::endl;
	
	return content;
}
