/* Sandbox game class to test the engine. */

#include <vector>
#include "spirit.h"

class Game : public spirit::SpiritEngine {
public:
  Game();
  void main_loop();
  void keyboard_event(int key, bool state, bool repeat) override;

private:
  spirit::Shader shader;
  spirit::Texture texture;
  std::vector<spirit::Object2d> sprites;
  spirit::Batch batch;
};