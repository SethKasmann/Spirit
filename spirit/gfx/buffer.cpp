#include "buffer.h"

namespace spirit {

	VertexBuffer::VertexBuffer()
	: _size(0), _count(0), _vbo(0)
	{}

	VertexBuffer::VertexBuffer(GLfloat* verticies, size_t size, GLuint count)
	: _size(size), _count(count)
	{
		init(verticies, size, count);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &_vbo);
	}

	void VertexBuffer::init(GLfloat* verticies, size_t size, GLuint count)
	{
		// Create the vertex buffer object.
		glGenBuffers(1, &_vbo);
		// Bind the local buffer.
		bind();
		// Copy vertex data into the buffer object.
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), verticies, GL_STATIC_DRAW);
		// Unbind the buffer after data has been passed in.
		unbind();
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	}

	void VertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	GLuint VertexBuffer::get_count() const
	{
		return _count;
	}

	size_t VertexBuffer::get_size() const
	{
		return _size;
	}

	IndexBuffer::IndexBuffer()
	: _size(0), _ibo(0)
	{}

	IndexBuffer::IndexBuffer(GLushort* indices, size_t size)
	{
		init(indices, size);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &_ibo);
	}

	void IndexBuffer::init(GLushort* indices, size_t size)
	{
		_size = size;
		// Create the vertex buffer object.
		glGenBuffers(1, &_ibo);
		// Bind the local buffer.
		bind();
		// Copy vertex data into the buffer object.
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLushort), indices, GL_STATIC_DRAW);
		// Unbind the buffer after data has been passed in.
		unbind();
	}

	void IndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	}

	void IndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	size_t IndexBuffer::get_size() const
	{
		return _size;
	}

}