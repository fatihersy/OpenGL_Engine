#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "renderer_types.inl"

typedef struct glshape
{
	u32 ID;

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