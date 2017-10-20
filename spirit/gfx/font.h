#ifndef FONT_H
#define FONT_H

#include "subtexture.h"

namespace spirit {

	class Font : public SubTexture
	{
	public:
		Font(std::string file, std::string text, size_t size, int r, int g,
			int b, int a);
		~Font();
		void load();
		void free();
		void generate(int w, int h);
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