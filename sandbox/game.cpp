#include "game.h"

Game::Game()
    : SpiritEngine("Test Game", 960, 540) {

  std::vector<glm::vec4> sprite_sheet;
  for (int i = 0; i < 2; ++i)
  {
    for (int j = 0; j < 8; ++j)
    {
      sprite_sheet.push_back(glm::vec4(108.0f*j, 140.0f*i, 108.0f, 140.0f));
    }
  }
  texture.insert_sheet("spirit/image/testsheet.png", "running", &sprite_sheet[0], 16);
  texture.insert_image("spirit/image/bomb1.png", "bomb1");
  texture.insert_font("spirit/font/OpenSans.ttf", "sans_test", 30);
  texture.generate();

  for (float i = 0; i < 960.0f; i += 108.0f) {
    for (float j = 0; j < 540.0f; j += 140.0f) {
      sprites.push_back(
          spirit::Object2d(glm::vec3(i, j, rand() % 1000), 108.0f, 140.0f, texture, "running", rand() % 16));
    }
  }

  main_loop();
}

void Game::main_loop() {
  while (!closed()) {
    begin_loop();
    for (auto &s : sprites)
      batch.push(&s);

    batch.set_projection(get_camera3d().get_projection());
    batch.set_modelview(get_camera3d().get_view());
    render(batch, texture);
    end_loop();
  }
}

void Game::keyboard_event(int key, bool state, bool repeat) {
  switch (key) {
  case SDL_SCANCODE_W:
    if (state)
    {
      get_camera().move(0.0f, 5.0f);
      get_camera3d().move(glm::vec3(0.0f, 5.0f, 0.0f));
    }
    break;
  case SDL_SCANCODE_S:
    if (state)
    {
      get_camera().move(0.0f, -5.0f);
      get_camera3d().move(glm::vec3(0.0f, -5.0f, 0.0f));
    }
    break;
  case SDL_SCANCODE_D:
    if (state)
    {
      get_camera().move(5.0f, 0.0f);
      get_camera3d().move(glm::vec3(5.0f, 0.0f, 0.0f));
    }
    break;
  case SDL_SCANCODE_A:
    if (state)
    {
      get_camera().move(-5.0f, 0.0f);
      get_camera3d().move(glm::vec3(-5.0f, 0.0f, 0.0f));
    }
    break;
  case SDL_SCANCODE_EQUALS:
    if (state)
    {
      get_camera().zoom(0.5f);
      get_camera3d().move(glm::vec3(0.0f, 0.0f, 5.0f));
    }
    break;
  case SDL_SCANCODE_MINUS:
    if (state)
    {
      get_camera().zoom(-0.5f);
      get_camera3d().move(glm::vec3(0.0f, 0.0f, -5.0f));
    }
    break;
  case SDL_SCANCODE_R:
    if (state)
    {
      get_camera3d().rotate(0.1f, glm::vec3(0, 1, 0));
    }
  }
}