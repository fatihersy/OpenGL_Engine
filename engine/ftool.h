#pragma once

#ifndef FTOOL_H
#define FTOOL_H

#include "defines.h"
#include <string>
#include <vector>

template<class T> size_t vector_element_index(std::vector<T> vec, T key);

std::vector<std::string>::iterator string_vector_match_index(std::vector<std::string> vec, std::string key);

std::string read_file(const char* path);

#endif // !FTOOL_H




