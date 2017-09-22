#include "vertexarray.h"

namespace spirit {

	VertexArray::VertexArray()
	{
		init();
	}

	VertexArray::~VertexArray()
	{
		//glDeleteVertexArrays(1, &_vao);
	}

	void VertexArray::init()
	{
		glGenVertexArrays(1, &_vao);
	}

	void VertexArray::add_buffer(const DynamicBuffer& buffer, int location, int count, int stride, int offset)
	{
		bind();
		buffer.bind();
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, 
			                  count, 
			                  GL_FLOAT, 
			                  GL_FALSE, 
			                  stride * sizeof(GLfloat),
			                  reinterpret_cast<void*>(offset * sizeof(GLfloat)));
		buffer.unbind();
		unbind();
	}

	void VertexArray::add_buffer(const VertexBuffer& buffer, int location, int stride, int offset)
	{
		bind();
		buffer.bind();
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, 
			                  3, 
			                  GL_FLOAT, 
			                  GL_FALSE, 
			                  stride * sizeof(GLfloat),
			                  reinterpret_cast<void*>(offset * sizeof(GLfloat)));
		buffer.unbind();
		unbind();
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(_vao);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

}