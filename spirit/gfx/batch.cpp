#include "batch.h"

namespace spirit {

	Batch::Batch(Shader* shader, TextureArray* tex_array, const glm::mat4& pr_mat)
	: _shader(shader)
	, _tex_array(tex_array)
	, _pr_mat(pr_mat)
	{
		_tex_array->bind();
		_shader->enable();
		_shader->set_mat4_fv("pr_matrix", _pr_mat);
		_shader->set_uniform_1i("tex_array", _tex_array->get_id());
		_shader->disable();
		_tex_array->unbind();
	}

	void Batch::push(const Object2d* element)
	{
		_elements.push_back(element);
	}

	void Batch::render()
	{
		_shader->enable();
		_tex_array->bind();
		_renderer.bind();
		for (int i = 0; i < _elements.size(); ++i)
		{
			_renderer.push(_elements[i]);
		}
		_renderer.unbind();
		_renderer.render();
		_tex_array->unbind();
		_shader->disable();

	}

}