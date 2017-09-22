#include "object2d.h"

namespace spirit {

	Object2d::Object2d(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
	: _pos(pos), _size(size), _color(color)
	{
		std::array<GLfloat, 12> verticies = 
		{
			_pos.x,           _pos.y,           0,
			_pos.x + _size.x, _pos.y,           0,
			_pos.x,           _pos.y + _size.y, 0,
			_pos.x + _size.x, _pos.y + _size.y, 0
		};

		std::array<GLfloat, 16> colors =
		{
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w
		};

		std::array<GLushort, 6> indicies =
		{
			0, 1, 2, 1, 2, 3
		};

		_vao.init();

		VertexBuffer v(&verticies[0], 12, 4);
		VertexBuffer c(&colors[0], 16, 4);

		_ibo.init(&indicies[0], 6);
		_vao.add_buffer(v, 0, 0, 0);
		_vao.add_buffer(c, 1, 0, 0);
	}

	void Object2d::draw()
	{
		_vao.bind();
		_ibo.bind();
		glDrawElements(GL_TRIANGLES, _ibo.get_size(), GL_UNSIGNED_SHORT, 0);
		_ibo.unbind();
		_vao.unbind();
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

}