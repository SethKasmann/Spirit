#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "camera2d.h"
#include "glm.hpp"

struct SDL_Window;
union SDL_Event;
typedef void *SDL_GLContext;

namespace spirit {

class Window {

public:
  Window(std::string name, int w, int h);
  ~Window();
  bool closed() const;
  void set_closed(int closed);
  void resize();
  void clear();
  void mouse_position(int *x, int *y) const;
  int get_w() const;
  int get_h() const;
  void swap_window() const;

private:
  bool _closed;
  SDL_Window *_window;
  SDL_GLContext _context;
};
}

#endif