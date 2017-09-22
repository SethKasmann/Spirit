#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <array>
#include "glm.hpp"
#include "GL/glew.h"
#include "vertexarray.h"
#include "dynamicbuffer.h"
#include "object2d.h"

namespace spirit {

	static const int max_buffer_size = 10000 * sizeof(GLfloat);
	static const int vertex_location = 0;
	static const int color_location = 1;
	static const int vertex_count = 3;
	static const int color_count = 4;
	static const int stride = vertex_count + color_count;
	static const int vertex_offset = 0;
	static const int color_offset = vertex_count;

	struct Vertex
	{
		glm::vec3 position;
		glm::vec4 color;
	};	

	class Renderer2d
	{
	public:
		Renderer2d();
		void push(const Object2d& obj);
		void bind();
		void unbind();
		void render();
	private:
		DynamicBuffer _vbo;
		IndexBuffer _ibo;
		VertexArray _vao;
		Vertex* _vertex_ptr;
	};

}

#endif