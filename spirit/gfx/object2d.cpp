#include "object2d.h"

namespace spirit {

	Object2d::Object2d(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
	: _pos(pos), _size(size), _color(color), _texture(nullptr), _level(-1.0)
	{
		_tex_coords[0] = glm::vec3(0.0f, 1.0f, 0.0f);
		_tex_coords[1] = glm::vec3(1.0f, 1.0f, 0.0f);
		_tex_coords[2] = glm::vec3(0.0f, 0.0f, 0.0f);
		_tex_coords[3] = glm::vec3(1.0f, 0.0f, 0.0f);
	}

	Object2d::Object2d(const glm::vec3& pos, const glm::vec2& size, Texture* texture)
	: _pos(pos), _size(size), _texture(texture), _level(-1.0)
	{
		_tex_coords[0] = glm::vec3(0.0f, 1.0f, 0.0f);
		_tex_coords[1] = glm::vec3(1.0f, 1.0f, 0.0f);
		_tex_coords[2] = glm::vec3(0.0f, 0.0f, 0.0f);
		_tex_coords[3] = glm::vec3(1.0f, 0.0f, 0.0f);
	}

	Object2d::Object2d(const glm::vec3& pos, const glm::vec2& size, float level)
	: _pos(pos), _size(size), _level(level)
	{
		_tex_coords[0] = glm::vec3(0.0f, 1.0f, _level);
		_tex_coords[1] = glm::vec3(1.0f, 1.0f, _level);
		_tex_coords[2] = glm::vec3(0.0f, 0.0f, _level);
		_tex_coords[3] = glm::vec3(1.0f, 0.0f, _level);
	}

	const glm::vec4& Object2d::get_color() const
	{
		return _color;
	}

	const glm::vec3& Object2d::get_pos() const
	{
		return _pos;
	}

	const glm::vec2& Object2d::get_size() const
	{
		return _size;
	}

	const std::array<glm::vec3, 4>& Object2d::get_tex_coords() const
	{
		return _tex_coords;
	}

	uint32_t Object2d::get_ui_color() const
	{
		return (((static_cast<int>(_color.w * 255)) << 24)
			  | ((static_cast<int>(_color.z * 255)) << 16)
			  | ((static_cast<int>(_color.y * 255)) <<  8)
			  |  (static_cast<int>(_color.x * 255)));
	}

	GLuint Object2d::get_tex_id() const
	{
		return _texture == nullptr ? 0 : _texture->get_id();
	}
}