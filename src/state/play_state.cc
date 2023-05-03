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
  for (int i{ 0 }; i < 4; ++i) {
    for (int j{ 1 }; j < 192; j += 8) {
      bricks_.push_back(Brick(j, 24 + i * 4,
                              static_cast<Brick::BrickType>(i),
                              &blocks_texture_));
    }
  }
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
  ball_.Update();
  paddle_.Update();
  ResolveCollisions();
}

void PlayState::Render() {
  score_display_.Render();
  ball_.Render();
  paddle_.Render();
  for (Brick brick : bricks_) {
    brick.Render();
  }
}

void PlayState::ResolveCollisions() {
  int ball_x{ ball_.get_x() };
  int ball_y{ ball_.get_y() };
  int paddle_x{ paddle_.get_x() };

  if (ball_x + Ball::kBallWidth < paddle_x ||
      ball_x > paddle_x + Paddle::kPaddleWidth ||
      ball_y + Ball::kBallHeight < Paddle::kPaddleY ||
      ball_y > Paddle::kPaddleY + Paddle::kPaddleHeight) {
    return;
  }

  int ball_center{ ball_x + (Ball::kBallWidth / 2) };
  int paddle_center{ paddle_x + (Paddle::kPaddleWidth / 2) };

  ball_.set_x_velocity((ball_center - paddle_center) / 6);
  ball_.set_y_velocity(-ball_.get_y_velocity());
}
