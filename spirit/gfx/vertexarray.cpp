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

	void VertexArray::add_vertex_buffer(const DynamicBuffer& buffer)
	{
		bind();
		buffer.bind();
		glEnableVertexAttribArray(vertex_location);
		glVertexAttribPointer(vertex_location,
							  vertex_count,
							  GL_FLOAT,
							  GL_FALSE,
							  stride,
							  reinterpret_cast<void*>(offsetof(Vertex, position)));
		buffer.unbind();
		unbind();
	}

	void VertexArray::add_color_buffer(const DynamicBuffer& buffer)
	{
		bind();
		buffer.bind();
		glEnableVertexAttribArray(color_location);
		glVertexAttribPointer(color_location,
							  color_count,
							  GL_UNSIGNED_BYTE,
							  GL_TRUE,
							  stride,
							  reinterpret_cast<void*>(offsetof(Vertex, color)));
		buffer.unbind();
		unbind();
	}

	void VertexArray::add_tex_buffer(const DynamicBuffer& buffer)
	{
		bind();
		buffer.bind();
		glEnableVertexAttribArray(tex_location);
		glVertexAttribPointer(tex_location,
							  tex_count,
							  GL_FLOAT,
							  GL_FALSE,
							  stride,
							  reinterpret_cast<void*>(offsetof(Vertex, tex)));
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