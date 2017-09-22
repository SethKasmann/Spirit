#ifndef BUFFER_H
#define BUFFER_H

#include <GL/glew.h>

namespace spirit {

	class VertexBuffer
	{
	public:
		VertexBuffer();
		VertexBuffer(GLfloat* verticies, size_t size, GLuint count);
		~VertexBuffer();
		void init(GLfloat* verticies, size_t size, GLuint count);
		void bind() const;
		void unbind() const;
		GLuint get_count() const;
		size_t get_size() const;
	private:
		GLuint _vbo;
		GLuint _count;
		size_t _size;
	};

	class IndexBuffer
	{
	public:
		IndexBuffer();
		IndexBuffer(GLushort* indices, size_t size);
		~IndexBuffer();
		void init(GLushort* indices, size_t size);
		void bind() const;
		void unbind() const;
		size_t get_size() const;
	private:
		GLuint _ibo;
		size_t _size;
	};
}

#endif