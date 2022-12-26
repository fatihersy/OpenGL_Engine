#pragma once

#include <vector>

#include <defines.h>

template<typename T> u64 VECTOR_SIZE(std::vector<T> vector)
{
	return vector.size() * sizeof(T);
}

typedef enum geometry_type
{
	TRIANGLE,
	QUAD
} geometry_type;

typedef struct fshape
{
	u32 ID;

	i32 width;
	i32 height;
	i32 scale;

	i32 x;
	i32 y;
	i32 z;
} fshape;

typedef struct frenderer_backend 
{
	void (*renderer_begin_frame) ();

	void (*renderer_end_frame) ();

	void (*renderer_draw_frame) (std::vector<fshape> out_shapes);

	b8 (*renderer_create_default_geometry) (fshape _shape, geometry_type _type);

} frenderer_backend;

