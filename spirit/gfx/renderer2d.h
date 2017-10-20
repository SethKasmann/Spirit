#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <array>
#include <vector>
#include <algorithm>
#include <iostream>
#include "glm.hpp"
#include "GL/glew.h"
#include "vertex.h"
#include "dynamicbuffer.h"
#include "object2d.h"

namespace spirit {

#define MAX_BUFFER_SIZE 12000

class Renderer2d {
public:
  Renderer2d();
  void push(const Object2d *obj);
  void bind();
  void unbind();
  void render();

private:
  GLuint _vao;
  GLuint _vbo;
  IndexBuffer _ibo;
  Vertex *_vertex_ptr;
};
}

#endif