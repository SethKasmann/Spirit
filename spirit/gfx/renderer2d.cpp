#include "renderer2d.h"

namespace spirit {

	Renderer2d::Renderer2d()
	: _vao(), _vertex_ptr(nullptr)
	{
		int offset;

		_vbo.init(max_buffer_size * sizeof(Vertex));
		_vao.add_vertex_buffer(_vbo);
		_vao.add_color_buffer(_vbo);
		_vao.add_tex_buffer(_vbo);

		std::array<GLushort, max_buffer_size> indicies;

		offset = 0;
		for (int i = 0; i < max_buffer_size; i += 6) // is this loop bad ?
		{
			indicies[i    ] = offset;
			indicies[i + 1] = offset + 1;
			indicies[i + 2] = offset + 2;
			indicies[i + 3] = offset + 1;
			indicies[i + 4] = offset + 2;
			indicies[i + 5] = offset + 3;
			offset += 4;
		}

		_ibo.init(&indicies[0], max_buffer_size);
	}

	void Renderer2d::bind()
	{
		_vbo.bind();
		_vertex_ptr = static_cast<Vertex*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	}

	void Renderer2d::push(const Object2d& obj)
	{
		uint32_t c = obj.get_ui_color();

		_vertex_ptr->position.x = obj.get_pos().x;
		_vertex_ptr->position.y = obj.get_pos().y;
		_vertex_ptr->position.z = obj.get_pos().z;
		_vertex_ptr->color = c;
		_vertex_ptr->tex.x = obj.get_tex_coords()[0].x;
		_vertex_ptr->tex.y = obj.get_tex_coords()[0].y;
		_vertex_ptr++;

		_vertex_ptr->position.x = obj.get_pos().x + obj.get_size().x;
		_vertex_ptr->position.y = obj.get_pos().y;
		_vertex_ptr->position.z = obj.get_pos().z;
		_vertex_ptr->color = c;
		_vertex_ptr->tex.x = obj.get_tex_coords()[1].x;
		_vertex_ptr->tex.y = obj.get_tex_coords()[1].y;
		_vertex_ptr++;

		_vertex_ptr->position.x = obj.get_pos().x;
		_vertex_ptr->position.y = obj.get_pos().y + obj.get_size().y;
		_vertex_ptr->position.z = obj.get_pos().z;
		_vertex_ptr->color = c;
		_vertex_ptr->tex.x = obj.get_tex_coords()[2].x;
		_vertex_ptr->tex.y = obj.get_tex_coords()[2].y;
		_vertex_ptr++;

		_vertex_ptr->position.x = obj.get_pos().x + obj.get_size().x;
		_vertex_ptr->position.y = obj.get_pos().y + obj.get_size().y;
		_vertex_ptr->position.z = obj.get_pos().z;
		_vertex_ptr->color = c;
		_vertex_ptr->tex.x = obj.get_tex_coords()[3].x;
		_vertex_ptr->tex.y = obj.get_tex_coords()[3].y;
		_vertex_ptr++;
	}

	void Renderer2d::unbind()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		_vbo.unbind();
		_vertex_ptr = nullptr;
	}

	void Renderer2d::render()
	{
		_vao.bind();
		_ibo.bind();
		glDrawElements(GL_TRIANGLES, _ibo.get_size(), GL_UNSIGNED_SHORT, 0);
		_ibo.unbind();
		_vao.unbind();
	}

}