#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <array>
#include <vector>
#include <algorithm>
#include <iostream>
#include "glm.hpp"
#include "GL/glew.h"
#include "vertex.h"
#include "object2d.h"

namespace spirit {

#define MAX_BUFFER_SIZE 10000

static const int MAX_VBO_SIZE = 10000 * 4;
static const int MAX_IBO_SIZE = 10000 * 6;

class Renderer2d {
public:
  Renderer2d();
  void push(const Object2d *obj);
  void begin();
  void end();
  void render();

private:
  GLuint _vbo;
  GLuint _vao;
  GLuint _ibo;
  Vertex *_vertex_ptr;
  size_t _size;
};
}

#endif