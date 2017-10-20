#include "camera2d.h"

namespace spirit
{
    Camera2d::Camera2d()
    : Camera2d(0.0f, 0.0f)
    {}

    Camera2d::Camera2d(float x, float y)
    : _changed(false), _scale(1.0f), _position(glm::vec2(x, y)), _ortho(glm::mat4(1.0f))
    {}

    void Camera2d::set_position(float x, float y)
    {
        _position = glm::vec2(x, y);
        _changed = true;
    }

    void Camera2d::update_position(float x, float y)
    {
        _position += glm::vec2(x, y);
        _changed = true;
    }

    void Camera2d::set_scale(float scale)
    {
        _scale = scale;
        _changed = true;
    }

    void Camera2d::update_scale(float dscale)
    {
        _scale += dscale;
        _changed = true;
    }

    void Camera2d::set_ortho(int w, int h)
    {
        _ortho = glm::ortho(0.0f, static_cast<float>(w), 0.0f, static_cast<float>(h));
        _changed = true;
    }

    void Camera2d::update()
    {
        if(_changed)
        {
            _camera_mat = glm::scale(_ortho, glm::vec3(_scale, _scale, 1.0f));
            _camera_mat = glm::translate(_camera_mat, glm::vec3(_position.x, _position.y, 0.0f));
            _changed = false;
        }
    }

    const glm::mat4& Camera2d::get_mat() const
    {
        return _camera_mat;
    }
}