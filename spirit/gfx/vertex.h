#ifndef VERTEX_H
#define VERTEX_H

#include "glm.hpp"
#include <cstddef>
#include <iostream>

namespace spirit {

struct Vertex {
  glm::vec3 position;
  uint32_t color;
  glm::vec3 tex;
  uint32_t tex_id;
};

static const int position_location = 0;
static const int color_location = 1;
static const int texture_location = 2;
static const int texture_id_location = 3;

static const int position_count = 3;
static const int color_count = 4;
static const int texture_count = 3;
static const int texture_id_count = 1;

static const int vertex_stride = sizeof(Vertex);

static const int position_offset = offsetof(Vertex, position);
static const int color_offset = offsetof(Vertex, color);
static const int texture_offset = offsetof(Vertex, tex);
static const int texture_id_offset = offsetof(Vertex, tex_id);
}

#endif