#include "renderer2d.h"

namespace spirit {

	Renderer2d::Renderer2d()
	: _vertex_ptr(nullptr)
	{
		// Generate the VAO and VBO
		glGenVertexArrays(1, &_vao);
		glGenBuffers(1, &_vbo);

		// Bind the VAO and VBO
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBindVertexArray(_vao);

		// Set the VBO data
		glBufferData(GL_ARRAY_BUFFER, MAX_BUFFER_SIZE * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		// Enable locations for shaders.
		glEnableVertexAttribArray(position_location);
		glEnableVertexAttribArray(color_location);
		glEnableVertexAttribArray(texture_location);
		glEnableVertexAttribArray(texture_id_location);

		// Generate attribute pointers for shaders.
		glVertexAttribPointer(position_location,
							  position_count,
							  GL_FLOAT,
							  GL_FALSE,
							  vertex_stride,
							  reinterpret_cast<void*>(position_offset));

		glVertexAttribPointer(color_location,
							  color_count,
							  GL_UNSIGNED_BYTE,
							  GL_TRUE,
							  vertex_stride,
							  reinterpret_cast<void*>(color_offset));

		glVertexAttribPointer(texture_location,
							  texture_count,
							  GL_FLOAT,
							  GL_FALSE,
							  vertex_stride,
							  reinterpret_cast<void*>(texture_offset));

		glVertexAttribPointer(texture_id_location,
							  texture_id_count,
							  GL_UNSIGNED_INT,
							  GL_FALSE,
							  vertex_stride,
							  reinterpret_cast<void*>(texture_id_offset));

		// Unbind the VAO and VBO
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Generate the indicies array.
		int offset = 0;
		std::array<GLushort, MAX_BUFFER_SIZE> indicies;

		for (int i = 0; i < MAX_BUFFER_SIZE; i += 6)
		{
			indicies[i    ] = offset;
			indicies[i + 1] = offset + 1;
			indicies[i + 2] = offset + 2;
			indicies[i + 3] = offset + 1;
			indicies[i + 4] = offset + 2;
			indicies[i + 5] = offset + 3;
			offset += 4;
		}

		_ibo.init(&indicies[0], MAX_BUFFER_SIZE);
	}

	void Renderer2d::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		_vertex_ptr = static_cast<Vertex*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	}

	void Renderer2d::unbind()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		_vertex_ptr = nullptr;
	}

	void Renderer2d::push(const Object2d& obj)
	{
		uint32_t color = 0;
		GLfloat tex_id = 0.0;

		if (obj._level == -1.0)
			color = obj.get_ui_color();
		else
			tex_id = 1.0;

		_vertex_ptr->position.x = obj.get_pos().x;
		_vertex_ptr->position.y = obj.get_pos().y;
		_vertex_ptr->position.z = obj.get_pos().z;
		_vertex_ptr->color = color;
		_vertex_ptr->tex.x = obj.get_tex_coords()[0].x;
		_vertex_ptr->tex.y = obj.get_tex_coords()[0].y;
		_vertex_ptr->tex.z = obj.get_tex_coords()[0].z;
		_vertex_ptr->tex_id = tex_id;
		_vertex_ptr++;

		_vertex_ptr->position.x = obj.get_pos().x + obj.get_size().x;
		_vertex_ptr->position.y = obj.get_pos().y;
		_vertex_ptr->position.z = obj.get_pos().z;
		_vertex_ptr->color = color;
		_vertex_ptr->tex.x = obj.get_tex_coords()[1].x;
		_vertex_ptr->tex.y = obj.get_tex_coords()[1].y;
		_vertex_ptr->tex.z = obj.get_tex_coords()[1].z;
		_vertex_ptr->tex_id = tex_id;
		_vertex_ptr++;

		_vertex_ptr->position.x = obj.get_pos().x;
		_vertex_ptr->position.y = obj.get_pos().y + obj.get_size().y;
		_vertex_ptr->position.z = obj.get_pos().z;
		_vertex_ptr->color = color;
		_vertex_ptr->tex.x = obj.get_tex_coords()[2].x;
		_vertex_ptr->tex.y = obj.get_tex_coords()[2].y;
		_vertex_ptr->tex.z = obj.get_tex_coords()[2].z;
		_vertex_ptr->tex_id = tex_id;
		_vertex_ptr++;

		_vertex_ptr->position.x = obj.get_pos().x + obj.get_size().x;
		_vertex_ptr->position.y = obj.get_pos().y + obj.get_size().y;
		_vertex_ptr->position.z = obj.get_pos().z;
		_vertex_ptr->color = color;
		_vertex_ptr->tex.x = obj.get_tex_coords()[3].x;
		_vertex_ptr->tex.y = obj.get_tex_coords()[3].y;
		_vertex_ptr->tex.z = obj.get_tex_coords()[3].z;
		_vertex_ptr->tex_id = tex_id;
		_vertex_ptr++;
	}

	void Renderer2d::render()
	{
		glBindVertexArray(_vao);
		_ibo.bind();
		glDrawElements(GL_TRIANGLES, _ibo.get_size(), GL_UNSIGNED_SHORT, 0);
		_ibo.unbind();
		glBindVertexArray(0);
	}

}