#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "window.h"

namespace spirit {

Window::Window(std::string name, int w, int h)
    : _closed(false), _window(nullptr), _context(nullptr) {

  // Initialize SDL.
  // ----- TODO: move this into a static obj ----- //
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL failed to initialize video.\n";
  }

  // Create SDL window.
  _window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, w, h,
                             SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

  // Check the window was created propertly.
  if (_window == nullptr) {
    std::cout << "Failed to create window.\n";
  }

  // Set GL version.
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  // Set GL double buffering.
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  // Create OpenGL rendering contect to connect to the window.
  _context = SDL_GL_CreateContext(_window);

  // Make context current required before initializing GLEW.
  if (SDL_GL_MakeCurrent(_window, _context)) {
    std::cout << "Failed to set up context for window.\n";
  }

  // Initialize GLEW.
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();

  if (err != GLEW_OK) {
    std::cout << "GLEW failed to initialize.\n";
  }
}

Window::~Window() {
  // Destroy context.
  if (_context) {
    SDL_GL_DeleteContext(_context);
  }

  // Destroy window.
  if (_window) {
    SDL_DestroyWindow(_window);
  }

  SDL_Quit();
}

bool Window::closed() const { return _closed; }

// Set the private closed variable. This function is necessary
// since closed may be changed from the event_watch, which is
// a static function (since it's a callback).
void Window::set_closed(int closed) { _closed = closed; }

// Resize the window and maintain the aspect ratio.
void Window::resize() {
  int w, h;
  SDL_GetWindowSize(_window, &w, &h);
  glViewport(0, 0, w, h);
}

// Clear the window. Should be called at the beginning of the
// game loop.
void Window::clear() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::mouse_position(int *x, int *y) const { SDL_GetMouseState(x, y); }

int Window::get_w() const {
  int ret;
  SDL_GetWindowSize(_window, &ret, nullptr);
  return ret;
}

int Window::get_h() const {
  int ret;
  SDL_GetWindowSize(_window, nullptr, &ret);
  return ret;
}

void Window::swap_window() const { SDL_GL_SwapWindow(_window); }
}