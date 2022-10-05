#pragma once

#ifndef GL_TYPES_H
#define GL_TYPES_H

#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <defines.h>

template<typename T> u64 VECTOR_SIZE(std::vector<T> vector)
{
	return vector.size() * sizeof(T);
}

template<typename T> u32 ARRAY_COUNT(T array[])
{
	return sizeof(array) * sizeof(T);
}

typedef enum primitive_types
{
	TRIANGLE,
	QUAD
} primitive_types;

typedef struct glshape
{
	GLuint program_handle;

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
