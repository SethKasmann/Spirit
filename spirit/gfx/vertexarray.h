#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "buffer.h"
#include "dynamicbuffer.h"
#include "glm.hpp"
#include <cstddef>

namespace spirit {
/*
	struct Vertex
	{
		glm::vec3 position;
		uint32_t color;
		glm::vec2 tex;
	};	

	static const int vertex_location = 0;
	static const int color_location = 1;
	static const int tex_location = 2;
	static const int vertex_count = 3;
	static const int color_count = 4;
	static const int tex_count = 2;
	static const int stride = sizeof(Vertex);
	static const int vertex_offset = 0;
	static const int color_offset = vertex_count * sizeof(GL_FLOAT);
	static const int tex_offset = color_offset + color_count * sizeof(GL_UNSIGNED_BYTE);

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		void init();
		void add_vertex_buffer(const DynamicBuffer& buffer);
		void add_color_buffer(const DynamicBuffer& buffer);
		void add_tex_buffer(const DynamicBuffer& buffer);
		void add_buffer(const VertexBuffer& buffer, int location, int stride, int offset);
		void bind() const;
		void unbind() const;
	private:
		GLuint _vao;
	};*/

}

#endif