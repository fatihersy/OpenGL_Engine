#include "pch.h"
#include "ftool.h"

#include <fstream>
#include "fstring.h"

struct compare
{
	std::string key;
	compare(std::string const& i) : key(i) {}

	bool operator()(std::string const& i) {
		return (i.find(key));
	}
};


template<typename T> size_t vector_element_index(std::vector<T> vec, T key) 
{
	size_t i = 0;

	for (auto& itr : vec)
	{
		if (itr == key) break;

		i++;
	}

	return i;
}

std::vector<std::string>::iterator string_vector_match_index(std::vector<std::string> vec, std::string key)
{
	std::vector<std::string>::iterator i = vec.begin();

	for (std::string& itr : vec)
	{
		if (string_match(itr, key)) break;

		i++;
	}

	return vec.begin();
}

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