#pragma once

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "renderer_types.inl"

std::vector<f32> get_vertices(primitive_types type);

std::vector<u32> get_indices(primitive_types type);

u32 get_indice_count(primitive_types type);


#endif // !PRIMITIVES_H
