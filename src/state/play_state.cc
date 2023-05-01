#include "src/state/play_state.h"

#include "SDL2/SDL.h"

#include "src/entity/paddle.h"
#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/graphic/ui_element.h"

PlayState::PlayState()
    : score_display_{ &score_texture_, 0, 5 }, ball_{ &blocks_texture_ },
      paddle_{ &blocks_texture_ } {
  score_display_.AlignRightHorizontal();
}

bool PlayState::Load() {
  if (!font_.LoadFromFile("./font/cs50.ttf", 8)) { return false; }
  if (!score_texture_.LoadFromText(font_, "SCORE: 0")) { return false; }
  if (!blocks_texture_.LoadFromFile("./img/blocks.png")) { return false; }
  return true;
}

StateMachine *PlayState::HandleInput(SDL_Event input) {
  paddle_.HandleInput(input);
  return NULL;
}

void PlayState::Update() {
  score_display_.Render();
  ball_.Update();
  paddle_.Update();
}
