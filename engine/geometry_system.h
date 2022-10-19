#pragma once

#ifndef GEOMETRY_SYSTEM_H
#define GEOMETRY_SYSTEM_H

#include "renderer_types.inl"

std::vector<f32> get_vertices(geometry_type type);

std::vector<u32> get_indices(geometry_type type);

u32 get_vertice_count(geometry_type type);

u32 get_indice_count(geometry_type type);

#endif // !GEOMETRY_SYSTEM_H


