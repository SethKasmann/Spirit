#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "buffer.h"
#include "dynamicbuffer.h"

namespace spirit {

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		void init();
		void add_buffer(const DynamicBuffer& buffer, int location, int count, int stride, int offset);
		void add_buffer(const VertexBuffer& buffer, int location, int stride, int offset);
		void bind() const;
		void unbind() const;
	private:
		GLuint _vao;
	};

}

#endif