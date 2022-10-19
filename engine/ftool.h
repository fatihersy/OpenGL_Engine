#pragma once

#ifndef FTOOL_H
#define FTOOL_H

#include "defines.h"
#include <string>
#include <vector>
#include "fstring.h"

typedef std::vector<std::string> vec_str;

template<typename T> size_t vector_element_index(std::vector<T> vec, T key);

u32 string_vector_match_index(vec_str vec, string key);

std::string read_file(const char* path);

#endif // !FTOOL_H




