#pragma once

#ifndef GL_TYPES_H
#define GL_TYPES_H

#include <vector>
#include <cmath>

#include "glad/glad.h"

#include <defines.h>

template<typename T> u64 VECTOR_SIZE(std::vector<T> vector)
{
	return vector.size() * sizeof(T);
}

typedef enum primitive_types
{
	TRIANGLE,
	QUAD
} primitive_types;

typedef struct glshape
{
	GLuint program_handle;
	GLuint texture_handle;
	GLuint VAO;

	primitive_types type;
	u32 indice_count;
} glshape;

typedef struct glprogram
{
	GLuint handle;
	GLuint vertex, fragment;
} glprogram;




#endif // !GL_TYPES_H
