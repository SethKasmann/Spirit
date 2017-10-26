#include <iostream>
#include <string>
#include <GL/glew.h>
#include "inputhandler.h"
#include "window.h"
#include "camera2d.h"
#include "texture.h"
#include "fpscounter.h"
#include "shader.h"
#include "object2d.h"
#include "glm.hpp"
#include "batch.h"
union SDL_Event;
namespace spirit {

static const int default_width = 640;
static const int default_height = 480;

class Window;

class SpiritEngine {
protected:
  SpiritEngine();
  SpiritEngine(std::string name, int w, int h);
  ~SpiritEngine();
  virtual void keyboard_event(int key, bool state, bool repeat){};
  Camera2d &get_camera();
  // Need to change this name.
  void begin_loop();
  void end_loop();
  bool closed() const;

private:
  static int process_events(void *userdata, SDL_Event *event);
  Window _window;
  Camera2d _camera;
  FPSCounter _fps;
  static SpiritEngine *_self;
};
}