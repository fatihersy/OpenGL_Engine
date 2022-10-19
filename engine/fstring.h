#pragma once

#ifndef FSTRING_H
#define FSTRING_H

#include <string>
#include <cstring>
#include <sstream>
#include "defines.h"

typedef std::string string;

std::string add_line(std::string original, const char* text, const char* splitter);

std::string delete_line(std::string original, const char* text);

std::string delete_matched_lines(std::string original, const char* text);

b8 string_match(std::string first, std::string secord);



#endif // !FSTRING_H


