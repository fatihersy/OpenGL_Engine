#include "pch.h"
#include "fstring.h"

#include "defines.h"

std::string add_line(std::string original, const char* text, const char* splitter)
{
	std::string token		 = original.substr(0, original.find(splitter));
	std::string token_left = original.substr(original.find(splitter), original.length());

	token.append(text);
	token.append(token_left);

	return token;
}

std::string delete_line(std::string original, const char* text)
{
	std::istringstream iss(original);
	std::string line;
	std::string temp;

	while (std::getline(iss, line))
	{
		if (line.find(text) == std::string::npos)
		{
			temp += line + "\n";
		}
	}

	return temp;
}

b8 string_match(std::string first, std::string secord)
{
	return first.find(secord) != std::string::npos;
}