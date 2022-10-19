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

	geometry_type type;
	u32 indice_count;
} glshape;

typedef struct glprogram
{
	GLuint handle;
	GLuint vertex, fragment;
} glprogram;

typedef enum vertex_attribs 
{
	POSITION = 0,
	COLOR,
	TEXTURE
};