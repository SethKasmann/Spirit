#include <GL/glew.h>
#include <vector>
#include <iostream>
#include "misc.h"

namespace spirit {

    class Shader
    {
    public:
        Shader(const char* vec_src, const char* frag_src);
        ~Shader();
        bool init_shader(GLenum shader_type, const char* source);
        void enable();
        void disable();
        GLenum get_id() const;
    private:
        GLenum _program;
    };

}