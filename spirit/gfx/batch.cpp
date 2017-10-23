#include "batch.h"

namespace spirit {

	Batch::Batch(Shader* shader, Texture* texture, const glm::mat4& pr_mat)
	: _shader(shader)
	, _texture(texture)
	, _pr_mat(pr_mat)
	{
		_texture->bind();
		_shader->enable();
		_shader->set_mat4_fv("pr_matrix", _pr_mat);
		_shader->set_uniform_1i("tex_array", _texture->get_id());
		_shader->disable();
		_texture->unbind();
	}

	Batch::Batch(Shader* shader, Texture* texture, Window& window)
	: _shader(shader)
	, _texture(texture)
	{
		_pr_mat = window.get_camera().get_mat();
		_texture->bind();
		_shader->enable();
		_shader->set_mat4_fv("pr_matrix", _pr_mat);
		_shader->set_uniform_1i("tex_array", _texture->get_id());
		_shader->disable();
		_texture->unbind();
	}

	void Batch::push(const Object2d* element)
	{
		_elements.push_back(element);
	}

	void Batch::push(const Text* text)
	{
		const Object2d* ptr = text->get_ptr();
		for (int i = 0; i < text->get_size(); ++i)
		{
			_elements.push_back(ptr);
			ptr++;
		}
	}

	void Batch::clear()
	{
		_elements.clear();
	}

	void Batch::render()
	{
		_shader->enable();
		_shader->set_mat4_fv("pr_matrix", _pr_mat);
		_texture->bind();
		_renderer.bind();
		for (int i = 0; i < _elements.size(); ++i)
		{
			_renderer.push(_elements[i]);
		}
		_renderer.unbind();
		_renderer.render();
		_texture->unbind();
		_shader->disable();
		clear();

	}

	void Batch::set_projection(const glm::mat4& projection)
	{
		_pr_mat = projection;
	}
}