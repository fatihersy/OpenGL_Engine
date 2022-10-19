#pragma once

#ifndef SHADER_H
#define SHADER_H

#include "gl_types.inl"

int create_program(const char* vertex_path, const char* fragment_path);

b8 generate_texture(const char* path, GLenum type);

GLuint bind_vertex_data(geometry_type type, std::vector<vertex_attribs> attribs);

GLuint get_last_program_id();

GLuint get_last_texture_id();

#endif // !SHADER_H


