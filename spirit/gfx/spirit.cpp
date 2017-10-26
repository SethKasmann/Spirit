#include <SDL2/SDL.h>
#include "spirit.h"

namespace spirit {
SpiritEngine *SpiritEngine::_self = nullptr;

// Default constructor. Call ctor with defaults.
SpiritEngine::SpiritEngine()
    : SpiritEngine("Spirit Engine", default_width, default_height) {}

// Constructor that handles initialization.
SpiritEngine::SpiritEngine(std::string name, int w, int h)
    : _window(name, w, h), _camera(w, h) {
  SDL_AddEventWatch(process_events, nullptr);
  _self = this;
}

// Destructor.
SpiritEngine::~SpiritEngine() {
  SDL_DelEventWatch(process_events, nullptr);
  _self = nullptr;
}

Camera2d &SpiritEngine::get_camera() { return _camera; }

// Static function to process events.
int SpiritEngine::process_events(void *userdata, SDL_Event *event) {
  switch (event->type) {
  case SDL_QUIT:
    _self->_window.set_closed(true);
    break;
  case SDL_KEYDOWN:
  case SDL_KEYUP:
    // Keyboard event callback function.
    _self->keyboard_event(event->key.keysym.scancode, event->key.state,
                          event->key.repeat);
    break;
  case SDL_WINDOWEVENT:
    if (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
      _self->_camera.set_projection(static_cast<float>(_self->_window.get_w()),
                                    static_cast<float>(_self->_window.get_h()));
      // Do I even need this function.. ?
      _self->_window.resize();
    } else if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
      _self->_window.set_closed(true);
    }
    break;
  }
  return 1;
}

// Function to be called at the beginning of the game loop.
void SpiritEngine::begin_loop() { _window.clear(); }

// Function to be called at the end of the game loop.
void SpiritEngine::end_loop() {
  SDL_PumpEvents();
  _window.swap_window();
  if (_fps.update())
    std::cout << _fps.to_string() << '\n';
  int error = glGetError();
  if (error)
    std::cout << "GL ERROR: " << error << '\n';
}

bool SpiritEngine::closed() const { return _window.closed(); }
}