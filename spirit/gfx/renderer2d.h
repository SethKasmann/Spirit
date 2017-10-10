#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <array>
#include <iostream>
#include "glm.hpp"
#include "GL/glew.h"
#include "vertexarray.h"
#include "dynamicbuffer.h"
#include "object2d.h"

namespace spirit {

	static const int max_buffer_size = 10000;

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