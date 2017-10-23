#include "camera2d.h"

namespace spirit
{
    Camera2d::Camera2d()
    : Camera2d(0.0f, 0.0f)
    {}

    Camera2d::Camera2d(float x, float y)
    : _changed(false), _scale(1.0f), _position(glm::vec2(x, y)), _ortho(glm::mat4(1.0f)), _camera(glm::mat4(1.0f))
    {}

    void Camera2d::set_position(float x, float y)
    {
        _position = glm::vec2(x, y);
        _changed = true;
    }

    void Camera2d::set_ortho(int w, int h)
    {
        _ortho = glm::ortho(0.0f, static_cast<float>(w), 0.0f, static_cast<float>(h));
        _changed = true;
    }

    void Camera2d::set_scale(float scale)
    {
        _scale = scale;
        _changed = true;
    }

    void Camera2d::zoom(float scale)
    {
        _scale += scale;
        _changed = true;
    }

    void Camera2d::move(float dx, float dy)
    {
        _position += glm::vec2(dx, dy);
        _changed = true;
    }

    const glm::mat4& Camera2d::get_mat()
    {
        if(_changed)
        {
            _camera = glm::scale(_ortho, glm::vec3(_scale, _scale, 1.0f));
            _camera = glm::translate(_camera, glm::vec3(_position.x, _position.y, 0.0f));
            _changed = false;
        }
        return _camera;
    }

}