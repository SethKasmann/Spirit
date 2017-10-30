#include <SDL2/SDL.h>
#include "spirit.h"

namespace spirit {
SpiritEngine *SpiritEngine::_self = nullptr;

// Default constructor. Call ctor with defaults.
SpiritEngine::SpiritEngine()
    : SpiritEngine("Spirit Engine", default_width, default_height) {}

// Constructor that handles initialization.
SpiritEngine::SpiritEngine(std::string name, int w, int h)
    : _window(name, w, h), _camera(w, h), _camera3d(w, h), _renderer() {
  // Initialize the shader.
  _shader.init("spirit/shader/basic.vert", "spirit/shader/basic.frag");
  // Link the SDL event watch to the static input handler function.
  SDL_AddEventWatch(process_events, nullptr);
  _self = this;
  glDisable(GL_DEPTH_TEST);
}

// Destructor.
SpiritEngine::~SpiritEngine() {
  SDL_DelEventWatch(process_events, nullptr);
  _self = nullptr;
}

Camera2d &SpiritEngine::get_camera() { return _camera; }

Camera3d &SpiritEngine::get_camera3d() { return _camera3d; }


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
      _self->_camera3d.set_w(_self->_window.get_w());
      _self->_camera3d.set_h(_self->_window.get_h());
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

void SpiritEngine::render(Batch& batch, Texture& texture)
{
	_shader.enable();
	texture.bind();
	texture.link_to_shader(_shader);
	batch.link_to_shader(_shader);
	_renderer.begin();
	_renderer.submit(batch, _camera);
	_renderer.end();
	_renderer.render();
	texture.unbind();
	_shader.disable();
	batch.clear();
}
}