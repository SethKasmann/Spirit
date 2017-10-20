#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <iostream>
#include <array>

union SDL_Event;

namespace spirit
{
	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();
		static int process_events(void* userdata, SDL_Event* event);
		static int filter_events(void* userdata, SDL_Event* event);
		bool keydown(int scancode);
	private:
		static InputHandler* _self;
		const uint8_t* _keyboard;
	};

}
#endif