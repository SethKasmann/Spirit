#ifndef BATCH_H
#define BATCH_H

#include <vector>
#include <memory>
#include "shader.h"
#include "glm.hpp"
#include "object2d.h"
#include "renderer2d.h"

namespace spirit {

	class Batch
	{
	public:
		Batch(Shader* shader, const glm::mat4& pr_mat);
		void push_back(Object2d* element);
		void render();
	private:
		Shader* _shader;
		Renderer2d _renderer;
		std::vector<Object2d*> _elements;
		glm::mat4 _pr_mat;
	};

}

#endif