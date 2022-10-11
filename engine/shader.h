#pragma once

#ifndef SHADER_H
#define SHADER_H

#include "gl_types.inl"

int create_program(const char* vertex_path, const char* fragment_path);

GLuint compile_shader(const char* path, GLint shader_type);

GLuint generate_texture(const char* path, GLenum type);

GLuint bind_vertex_data(primitive_types type);

GLuint get_last_program_id();

#endif // !SHADER_H


