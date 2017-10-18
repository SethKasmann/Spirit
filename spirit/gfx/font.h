#ifndef FONT_H
#define FONT_H

#include "layer.h"

namespace spirit {

	class Font : public Layer
	{
	public:
		Font(std::string file, std::string text, size_t size, int r, int g,
			int b, int a);
		~Font();
		void load();
		void free();
		void generate(int w, int h, int z);
		const std::array<glm::vec3, 4>& operator[](int i) const;
	private:
		std::string _text;
		std::array<glm::vec3, 4> _coordinates;
        SDL_Surface* _surface;
        SDL_Color _color;
        size_t _size;
	};

}

#endif