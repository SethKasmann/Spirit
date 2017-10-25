#include "inputhandler.h"
#include <SDL2/SDL.h>

namespace spirit {
InputHandler *InputHandler::_self = nullptr;

InputHandler::InputHandler() {
  // Add the SDL even watch. Since the function pointer has to be
  // a static member, _self will act as a way to refer to the input
  // handler object.
  _self = this;
  // SDL_AddEventWatch(process_event, nullptr);

  // Set the keyboard state.
  _keyboard = SDL_GetKeyboardState(nullptr);

  // Add the event filter.
  SDL_SetEventFilter(filter_events, nullptr);
}

InputHandler::~InputHandler() {
  SDL_DelEventWatch(process_events, nullptr);
  _self = nullptr;
}

int InputHandler::process_events(void *userdata, SDL_Event *event) {
  /*
  switch (event->type)
  {

  }
  */
}

int InputHandler::filter_events(void *userdata, SDL_Event *event) {
  int ret;
  switch (event->type) {
  case SDL_QUIT:
    ret = 1;
    break;
  default:
    ret = 0;
    break;
  }
  return ret;
}

bool InputHandler::keydown(int scancode) { return _keyboard[scancode]; }
}