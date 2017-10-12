#ifndef OBJECT2D_H
#define OBJECT2D_H

#include "buffer.h"
#include "vertexarray.h"
#include "glm.hpp"
#include "texture.h"
#include "texturearray.h"
#include <array>

namespace spirit {

	class Object2d
	{
	public:
		Object2d(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);
		Object2d(const glm::vec3& pos, const glm::vec2& size, Texture* texture);
		Object2d(const glm::vec3& pos, const glm::vec2& size, float level);
		void draw();
		const glm::vec4& get_color() const;
		const glm::vec3& get_pos() const;
		const glm::vec2& get_size() const;
		const std::array<glm::vec3, 4>& get_tex_coords() const;
		uint32_t get_ui_color() const;
		GLuint get_tex_id() const;
		float _level;
	private:
		Texture* _texture;
		glm::vec4 _color;
		glm::vec3 _pos;
		glm::vec2 _size;
		std::array<glm::vec3, 4> _tex_coords;
	};

}

#endif