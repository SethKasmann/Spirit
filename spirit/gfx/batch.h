#ifndef BATCH_H
#define BATCH_H

#include <vector>
#include <memory>
#include "shader.h"
#include "glm.hpp"
#include "object2d.h"

namespace spirit {

class Batch {
public:
  Batch();
  void push(const Object2d *element);
  void push(const Text *text);
  void clear();
  void set_projection(const glm::mat4 &projection);
  void set_modelview(const glm::mat4 &modelview);
  void link_to_shader(const Shader& shader);
  const std::vector<const Object2d *>& get_vector() const;
private:
  std::vector<const Object2d *> _elements;
  glm::mat4 _projection;
  glm::mat4 _modelview;
};
}

#endif