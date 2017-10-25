#ifndef BATCH_H
#define BATCH_H

#include <vector>
#include <memory>
#include "shader.h"
#include "glm.hpp"
#include "object2d.h"
#include "renderer2d.h"
#include "texture.h"
#include "window.h"

namespace spirit {

class Batch {
public:
  Batch(Shader *shader, Texture *texture);
  void push(const Object2d *element);
  void push(const Text *text);
  void render();
  void clear();
  void set_projection(const glm::mat4 &projection);
  void set_modelview(const glm::mat4 &modelview);

private:
  Shader *_shader;
  Texture *_texture;
  Renderer2d _renderer;
  std::vector<const Object2d *> _elements;
  glm::mat4 _projection;
  glm::mat4 _modelview;
};
}

#endif