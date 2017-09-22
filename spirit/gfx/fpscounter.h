#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include <SDL2/SDL.h>
#include <cstdint>
#include <iostream>

namespace spirit {

	static const uint32_t interval = 1000;

	class FPSCounter
	{
	public:
		FPSCounter();
		bool update();
		void clear();
		friend std::ostream& operator<<(std::ostream& o, const FPSCounter& f);
	private:
		uint32_t _fps, _count, _time;
	};

}

#endif