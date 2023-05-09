#include "src/state/play_state.h"

#include "SDL2/SDL.h"

#include "src/entity/ball.h"
#include "src/entity/brick.h"
#include "src/entity/paddle.h"
#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/graphic/ui_element.h"

PlayState::PlayState()
    : score_display_{ &score_texture_, 0, 5 }, ball_{ &blocks_texture_ },
      paddle_{ &blocks_texture_ } {
  score_display_.AlignRightHorizontal();
  LoadLevel();
}

bool PlayState::Load() {
  if (!font_.LoadFromFile("./font/cs50.ttf", 8)) { return false; }
  if (!score_texture_.LoadFromText(font_, "SCORE: 0")) { return false; }
  if (!blocks_texture_.LoadFromFile("./img/blocks.png")) { return false; }
  return true;
}

StateMachine *PlayState::HandleInput(SDL_Event input) {
  ball_.HandleInput(input);
  paddle_.HandleInput(input);
  return NULL;
}

void PlayState::Update() {
  paddle_.Update();
  ball_.Update(paddle_, &bricks_);
}

void PlayState::Render() {
  score_display_.Render();
  paddle_.Render();
  ball_.Render();
  for (auto brick : bricks_) {
    if (!brick.is_hit()) {
      brick.Render();
    }
  }
}

void PlayState::LoadLevel() {
  for (int row{ 0 }; row < 8; ++row) {
    int y{ row * Brick::kBrickHeight + 20 };
    auto type{ static_cast<Brick::BrickType>(Brick::kRed - row / 2) };
    for (int col{ 0 }; col < 24; ++col) {
      bricks_.push_back(Brick(col * Brick::kBrickWidth + 1, y, type, &blocks_texture_));
    }
  }
}
