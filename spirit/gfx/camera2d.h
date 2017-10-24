#ifndef CAMERA2D_H
#define CAMERA2D_H

#include "glm.hpp"
#include "matrix_transform.hpp"

namespace spirit
{
    // Class to represent a 2D camera. Handles the orthographic matrix
    // based on the screen size, and the translation/scaling based on
    // camera movements.
    class Camera2d
    {
    public:
        Camera2d();
        Camera2d(float x, float y);
        void set_position(float x, float y);
        void set_ortho(int w, int h);
        void set_scale(float scale);
        void zoom(float scale);
        void move(float dx, float dy);
        const glm::mat4& get_projection() const;
        const glm::mat4& get_modelview();
    private:
        bool _update;
        float _scale;
        glm::vec2 _position;
        glm::mat4 _projection;
        glm::mat4 _modelview;
    };
}

#endif