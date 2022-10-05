#pragma once

#ifndef SHADER_H
#define SHADER_H

#include "gl_types.h"

GLuint compile_shader(const char* path, GLint shader_type);

int create_program(const char* vertex_path, const char* fragment_path);

GLuint bind_vertices(primitive_types type);

GLuint get_last_program_id();

#endif // !SHADER_H


