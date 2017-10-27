#include "renderer2d.h"

namespace spirit {

Renderer2d::Renderer2d() : _vertex_ptr(nullptr), _size(0) {
  // Generate the VAO and VBO
  glGenVertexArrays(1, &_vao);
  glGenBuffers(1, &_vbo);

  // Bind the VAO and VBO
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBindVertexArray(_vao);

  // Set the VBO data
  glBufferData(GL_ARRAY_BUFFER, MAX_BUFFER_SIZE * sizeof(Vertex) * 4, nullptr,
               GL_DYNAMIC_DRAW);

  // Enable locations for shaders.
  glEnableVertexAttribArray(position_location);
  glEnableVertexAttribArray(color_location);
  glEnableVertexAttribArray(texture_location);
  glEnableVertexAttribArray(texture_id_location);

  // Attribute pointer for the position
  glVertexAttribPointer(position_location, position_count, GL_FLOAT, GL_FALSE,
                        vertex_stride,
                        reinterpret_cast<void *>(position_offset));

  // Attribute pointer for the color
  glVertexAttribPointer(color_location, color_count, GL_UNSIGNED_BYTE, GL_TRUE,
                        vertex_stride, reinterpret_cast<void *>(color_offset));

  // Attribute pointer for the texture coordinates
  glVertexAttribPointer(texture_location, texture_count, GL_FLOAT, GL_FALSE,
                        vertex_stride,
                        reinterpret_cast<void *>(texture_offset));

  // Attribute pointer for the texture id
  glVertexAttribPointer(texture_id_location, texture_id_count, GL_UNSIGNED_INT,
                        GL_FALSE, vertex_stride,
                        reinterpret_cast<void *>(texture_id_offset));

  // Unbind the VAO and VBO
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Create and bind the IBO.
  glGenBuffers(1, &_ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

  // Generate the indicies array.
  int offset = 0;
  std::array<GLushort, MAX_IBO_SIZE> indicies;

  for (int i = 0; i < MAX_IBO_SIZE; i += 6) {
    indicies[i] = offset;
    indicies[i + 1] = offset + 1;
    indicies[i + 2] = offset + 2;
    indicies[i + 3] = offset + 2;
    indicies[i + 4] = offset + 3;
    indicies[i + 5] = offset + 0;
    offset += 4;
  }

  // Copy the index data into the IBO object.
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_BUFFER_SIZE * 6 * sizeof(GLushort),
               &indicies[0], GL_STATIC_DRAW);
  // Unbind the IBO object
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer2d::submit(const Batch &batch, const Camera2d& camera) {
  // Get scaled camera dimensions.
  glm::vec2 camera_dim = glm::vec2(camera.get_w(), camera.get_h());

  const std::vector<const Object2d *>& vec = batch.get_vector();
  for (std::vector<const Object2d *>::const_iterator it = vec.begin();
       it != vec.end(); ++it)
  {
      object_to_vertices(*it);
  }
}

void Renderer2d::begin() {
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  _vertex_ptr =
      static_cast<Vertex *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
}

void Renderer2d::end() {
  glUnmapBuffer(GL_ARRAY_BUFFER);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  _vertex_ptr = nullptr;
}

void Renderer2d::object_to_vertices(const Object2d *obj) {

  uint32_t color = obj->get_color();
  float tex_id = obj->get_type();

  if (_size >= MAX_VBO_SIZE) {
    end();
    render();
    begin();
  }

  _vertex_ptr->position.x = obj->get_pos().x;
  _vertex_ptr->position.y = obj->get_pos().y;
  _vertex_ptr->position.z = obj->get_pos().z;
  _vertex_ptr->color = color;
  _vertex_ptr->tex = obj->get_tex_coords()[0];
  _vertex_ptr->tex_id = tex_id;
  _vertex_ptr++;

  _vertex_ptr->position.x = obj->get_pos().x + obj->get_w();
  _vertex_ptr->position.y = obj->get_pos().y;
  _vertex_ptr->position.z = obj->get_pos().z;
  _vertex_ptr->color = color;
  _vertex_ptr->tex = obj->get_tex_coords()[1];
  _vertex_ptr->tex_id = tex_id;
  _vertex_ptr++;

  _vertex_ptr->position.x = obj->get_pos().x + obj->get_w();
  _vertex_ptr->position.y = obj->get_pos().y + obj->get_h();
  _vertex_ptr->position.z = obj->get_pos().z;
  _vertex_ptr->color = color;
  _vertex_ptr->tex = obj->get_tex_coords()[2];
  _vertex_ptr->tex_id = tex_id;
  _vertex_ptr++;

  _vertex_ptr->position.x = obj->get_pos().x;
  _vertex_ptr->position.y = obj->get_pos().y + obj->get_h();
  _vertex_ptr->position.z = obj->get_pos().z;
  _vertex_ptr->color = color;
  _vertex_ptr->tex = obj->get_tex_coords()[3];
  _vertex_ptr->tex_id = tex_id;
  _vertex_ptr++;

  _size += 4;
}

void Renderer2d::render() {
  glBindVertexArray(_vao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
  glDrawElements(GL_TRIANGLES, MAX_IBO_SIZE, GL_UNSIGNED_SHORT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  _size = 0;
}
}