#include "batch.h"

namespace spirit {

	Batch::Batch(Shader* shader, const glm::mat4& pr_mat)
	: _shader(shader)
	, _pr_mat(pr_mat)
	{
		_shader->enable();
		_shader->set_mat4_fv("pr_matrix", _pr_mat);
		_shader->disable();
	}

	void Batch::push_back(Object2d* element)
	{
		_elements.push_back(element);
	}

	void Batch::render()
	{
		_shader->enable();
		_renderer.bind();
		for (auto e : _elements)
			_renderer.push(*e);
		_renderer.unbind();
		_renderer.render();
		_shader->disable();

	}

}