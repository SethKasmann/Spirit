#ifndef OBJECT2D_H
#define OBJECT2D_H

#include "buffer.h"
#include "vertexarray.h"
#include "glm.hpp"
#include <array>

namespace spirit {

	class Object2d
	{
	public:
		Object2d(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);
		void draw();
		const glm::vec4& get_color() const;
		const glm::vec3& get_pos() const;
		const glm::vec2& get_size() const;
	private:
		IndexBuffer  _ibo;
		VertexArray  _vao;
		glm::vec4 _color;
		glm::vec3 _pos;
		glm::vec2 _size;
	};

}

#endif