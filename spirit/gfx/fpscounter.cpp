#include "fpscounter.h"

namespace spirit {

	FPSCounter::FPSCounter()
	: _fps(0), _count(0), _time(SDL_GetTicks())
	{}

	bool FPSCounter::update()
	{
		_count++;
		if (_time + interval < SDL_GetTicks())
		{
			_time  = SDL_GetTicks();
			_fps   = _count;
			_count = 0;
			return true;
		}
		return false;
	}

	void FPSCounter::clear()
	{
		_fps   = 0;
		_count = 0;
		_time  = SDL_GetTicks();
	}

	std::string FPSCounter::to_string()
	{
		return std::string("fps ") + std::to_string(_fps);
	}

	std::ostream& operator<<(std::ostream& o, const FPSCounter& f)
	{
		o << "FPS: " << f._fps;
	}

}