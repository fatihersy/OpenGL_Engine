#include "pch.h"
#include "primitives.h"

f32 triangle_vertices[] =
{
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};

f32 quad_vertices[] =
{
    0.5f,  0.5f, 0.0f, 0.6f, 0.2f, 0.4f,
    0.5f, -0.5f, 0.0f, 0.3f, 0.5f, 0.7f,
    -0.5f, -0.5f, 0.0f, 0.6f, 0.2f, 0.6f,
    -0.5f,  0.5f, 0.0f, 0.5f, 0.3f, 0.3f
};

u32 triangle_indices[] =
{
    0, 1, 2
};

u32 quad_indices[] =
{
    0, 1, 3,
    1, 2, 3
};

std::vector<f32> get_vertices(primitive_types type)
{
    if (type == TRIANGLE)
        return std::vector<f32>(std::begin(triangle_vertices), std::end(triangle_vertices));

    if (type == QUAD)
        return std::vector<f32>(std::begin(quad_vertices), std::end(quad_vertices));

    return std::vector<f32>();
}

std::vector<u32> get_indices(primitive_types type)
{
    if (type == TRIANGLE)
        return std::vector<u32>(std::begin(triangle_indices), std::end(triangle_indices));

    if (type == QUAD)
        return std::vector<u32>(std::begin(quad_indices), std::end(quad_indices));

    return std::vector<u32>();
}


u32 get_vertice_count(primitive_types type)
{
    if (type == TRIANGLE)
        return std::size(triangle_vertices);

    if (type == QUAD)
        return std::size(quad_vertices);

    return 0;
}

u32 get_indice_count(primitive_types type)
{
    if (type == TRIANGLE)
        return std::size(triangle_indices);

    if (type == QUAD)
        return std::size(quad_indices);

    return 0;
}