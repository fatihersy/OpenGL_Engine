#pragma once

#ifndef RENDERER_BACKEND_H
#define RENDERER_BACKEND_H

#include "renderer_types.inl"

b8 renderer_backend_create(frenderer_backend* backend);

void renderer_backend_destroy(frenderer_backend* backend);

#endif // !RENDERER_BACKEND_H

