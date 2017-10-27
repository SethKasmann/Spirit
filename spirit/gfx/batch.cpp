#include "batch.h"

namespace spirit {

Batch::Batch() {}

void Batch::push(const Object2d *element) { _elements.push_back(element); }

void Batch::push(const Text *text) {
  const Object2d *ptr = text->get_ptr();
  for (int i = 0; i < text->get_size(); ++i) {
    _elements.push_back(ptr);
    ptr++;
  }
}

void Batch::clear() { _elements.clear(); }

void Batch::set_projection(const glm::mat4 &projection) {
  _projection = projection;
}

void Batch::set_modelview(const glm::mat4 &modelview) {
  _modelview = modelview;
}

void Batch::link_to_shader(const Shader& shader)
{
  shader.set_mat4_fv("pr_matrix", _projection);
  shader.set_mat4_fv("ml_matrix", _modelview);
}

const std::vector<const Object2d *>& Batch::get_vector() const
{
  return _elements;
}
}