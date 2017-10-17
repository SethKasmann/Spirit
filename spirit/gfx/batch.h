#ifndef BATCH_H
#define BATCH_H

#include <vector>
#include <memory>
#include "shader.h"
#include "glm.hpp"
#include "object2d.h"
#include "renderer2d.h"
#include "texture.h"

namespace spirit {

	class Batch
	{
	public:
		Batch(Shader* shader, Texture* texture, const glm::mat4& pr_mat);
		void push(const Object2d* element);
		void render();
	private:
		Shader* _shader;
		TextureArray* _tex_array;
		Texture* _texture;
		Renderer2d _renderer;
		std::vector<const Object2d*> _elements;
		glm::mat4 _pr_mat;
	};

}

#endif