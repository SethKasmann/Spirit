#include "game.h"

Game::Game()
    : SpiritEngine("Test Game", 960, 540),
      shader("spirit/shader/basic.vert", "spirit/shader/basic.frag") {
  texture.insert_image("spirit/image/bomb1.png", "bomb1");
  texture.insert_font("spirit/font/OpenSans.ttf", "sans_test", 30);
  texture.generate();

  for (int i = 0; i < 960; i += 10) {
    for (int j = 0; j < 540; j += 10) {
      sprites.push_back(
          spirit::Object2d(glm::vec3(i, j, 0), 10, 10, texture, "bomb1"));
    }
  }

  batch.set_shader(&shader);
  batch.set_texture(&texture);

  main_loop();
}

void Game::main_loop() {
  while (!closed()) {
    begin_loop();
    for (auto &s : sprites)
      batch.push(&s);

    batch.set_projection(get_camera().get_projection());
    batch.set_modelview(get_camera().get_modelview());
    batch.render();
    end_loop();
  }
}

void Game::keyboard_event(int key, bool state, bool repeat) {
  switch (key) {
  case SDL_SCANCODE_W:
    if (state & !repeat)
      get_camera().move(0.0f, -5.0f);
    break;
  case SDL_SCANCODE_S:
    if (state & !repeat)
      get_camera().move(0.0f, 5.0f);
    break;
  case SDL_SCANCODE_D:
    if (state & !repeat)
      get_camera().move(-5.0f, 0.0f);
    break;
  case SDL_SCANCODE_A:
    if (state & !repeat)
      get_camera().move(5.0f, 0.0f);
    break;
  case SDL_SCANCODE_EQUALS:
    if (state & !repeat)
      get_camera().zoom(0.1f);
    break;
  case SDL_SCANCODE_MINUS:
    if (state & !repeat)
      get_camera().zoom(-0.1f);
    break;
  }
}