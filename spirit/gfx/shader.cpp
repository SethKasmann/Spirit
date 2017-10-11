#include "shader.h"

namespace spirit {

    Shader::Shader(const char* vert_src, const char* frag_src)
    {
        // Place the file contents into a string.
        std::string vert_str = file_to_string(vert_src);
        std::string frag_str = file_to_string(frag_src);

        // Copy the file contents to a char*
        const char* vert_prog = vert_str.c_str();
        const char* frag_prog = frag_str.c_str();

        // Create program and shader objects.
        _program = glCreateProgramObjectARB();

        // Return if a shader doesn't initialize properly.
        if (   !init_shader(GL_VERTEX_SHADER_ARB,   vert_prog)
            || !init_shader(GL_FRAGMENT_SHADER_ARB, frag_prog))
            return;

        // Link the program object.
        glLinkProgramARB(_program);
    }

    // Destructor - delete the program object.
    Shader::~Shader()
    {
        glDeleteObjectARB(_program);
    }

    // Initialize a shader based on it's type (vert or frag)
    bool Shader::init_shader(GLenum shader_type, const char* source)
    {
        GLint error, size;
        GLenum shader;
        bool ret = true;
        // Create the shader object
        shader = glCreateShaderObjectARB(shader_type);
        // Connect the sournce code with the shader object.
        glShaderSourceARB(shader, 1, &source, nullptr);
        // Compile the shader source in open gl.
        glCompileShader(shader);

        // Error checking.
        glGetShaderiv(shader, GL_COMPILE_STATUS, &error);
        if (error == false)
        {
            // Print the error.
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
            std::vector<char> error_message(size);
            glGetShaderInfoLog(shader, size, &size, &error_message[0]);
            std::cout << "Shader failed to initialize:\n";
            for (auto&& e : error_message)
                std::cout << e;
            ret = false;
        }
        // No error - attached the compiloed shader to the program.
        glAttachObjectARB(_program, shader);
        // The shader is no longer needed.
        glDeleteObjectARB(shader);
        return ret;
    }

    void Shader::enable()
    {
        glUseProgram(_program);
    }

    void Shader::disable()
    {
        glUseProgram(0);
    }

    GLenum Shader::get_id() const
    {
        return _program;
    }

    void Shader::set_vec2(const char* name, glm::vec2&& vec)
    {
        glUniform2f(glGetUniformLocation(_program, name), vec.x, vec.y);
    }

    void Shader::set_mat4_fv(const char* name, glm::mat4& mat)
    {
        glUniformMatrix4fv(glGetUniformLocation(_program, name), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::set_uniform_1i(const char* name, GLint id)
    {
        glUniform1i(glGetUniformLocation(_program, name), id);
    }

    void Shader::set_uniform_1iv(const char* name, GLint* value, GLuint count)
    {
        glUniform1iv(glGetUniformLocation(_program, name), count, value);
    }

}