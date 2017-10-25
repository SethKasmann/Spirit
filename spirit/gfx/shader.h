#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <vector>
#include <iostream>
#include "misc.h"
#include "glm.hpp"

namespace spirit {

class Shader {
public:
  Shader(const char *vec_src, const char *frag_src);
  ~Shader();
  bool init_shader(GLenum shader_type, const char *source);
  void enable();
  void disable();
  GLenum get_id() const;
  void set_vec2(const char *name, glm::vec2 &&vec);
  void set_mat4_fv(const char *name, glm::mat4 &mat);
  void set_uniform_1i(const char *name, GLint id);
  void set_uniform_1iv(const char *name, GLint *value, GLuint count);

private:
  GLenum _program;
};
}

#endif