#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include <SDL2/SDL.h>
#include <cstdint>
#include <iostream>
#include <string>

namespace spirit {

	static const uint32_t interval = 1000;

	class FPSCounter
	{
	public:
		FPSCounter();
		bool update();
		void clear();
		std::string to_string();
		friend std::ostream& operator<<(std::ostream& o, const FPSCounter& f);
	private:
		uint32_t _fps, _count, _time;
	};

}

#endif