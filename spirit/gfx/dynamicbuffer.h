#ifndef DYNAMICBUFFER_H
#define DYNAMICBUFFER_H

namespace spirit {

	class DynamicBuffer
	{
	public:
		DynamicBuffer()
		{}
		void init(size_t size)
		{
			glGenBuffers(1, &_dynamic_vbo);
			bind();
			glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
			unbind();
		}
		~DynamicBuffer()
		{
			glDeleteBuffers(1, &_dynamic_vbo);
		}
		void bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, _dynamic_vbo);
		}
		void unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		size_t get_size() const
		{
			return _size;
		}
	private:
		GLuint _dynamic_vbo;
		size_t _size;
	};
	
}

#endif