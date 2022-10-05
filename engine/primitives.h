#pragma once

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <defines.h>
#include <vector>

namespace primitives 
{
    enum types {
        TRIANGLE,
        QUAD
    };

    std::vector<f32> get_vertices(types type)
    {
        f32 triangle_vertices[] =
        {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
        };
        
        f32 quad_vertices[] =
        {
            0.5f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };
        
        if (type == TRIANGLE)
            return std::vector<f32>(std::begin(triangle_vertices), std::end(triangle_vertices));

        if (type == QUAD)
            return std::vector<f32>(std::begin(quad_vertices), std::end(quad_vertices));

        return std::vector<f32>();
    }

    std::vector<u32> get_indices(types type)
    {
        u32 triangle_indices[] =
        {
            0, 1, 2
        };

        u32 quad_indices[] =
        {
            0, 1, 3,
            1, 2, 3
        };

        if (type == TRIANGLE)
            return std::vector<u32>(std::begin(triangle_indices), std::end(triangle_indices));

        if (type == QUAD)
            return std::vector<u32>(std::begin(quad_indices), std::end(quad_indices));

        return std::vector<u32>();
    }
}

#endif // !PRIMITIVES_H
