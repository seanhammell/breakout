#include "src/entity/ball.h"

#include <cstdlib>

#include "SDL2/SDL.h"

#include "src/entity/brick.h"
#include "src/entity/paddle.h"
#include "src/graphic/renderer.h"
#include "src/graphic/texture.h"

Ball::Ball(Texture *texture, SDL_Rect clip)
    : texture_{ texture }, clip_{ clip } {}

void Ball::HandleInput(SDL_Event input) {
  if (!is_live_ && input.type == SDL_KEYDOWN) {
    if (input.key.keysym.sym == SDLK_SPACE) {
      is_live_ = true;
    }
  }
}

void Ball::Update(const Paddle& paddle, std::vector<Brick> *bricks) {
  if (is_live_) {
    Move();

    if (y_ > Renderer::kVirtualHeight) {
      x_ = (Renderer::kVirtualWidth - kBallWidth) / 2;
      y_ = Renderer::kVirtualHeight - 23;
      x_velocity_ = (std::rand() % 7) - 3;
      y_velocity_ = -1;
      is_live_ = false;
    }

    if (x_ < 0 || x_ + kBallWidth > Renderer::kVirtualWidth) {
      Unmove();
      x_velocity_ = -x_velocity_;
    }

    if (y_ < 0) {
      Unmove();
      y_velocity_ = -y_velocity_;
    }

    PaddleCollision(paddle);
    BrickCollision(bricks);
  }
}

void Ball::Render() {
  texture_->Render(x_, y_, &clip_);
}

void Ball::Move() {
  x_ += x_velocity_;
  y_ += y_velocity_;
}

void Ball::Unmove() {
  x_ -= x_velocity_;
  y_ -= y_velocity_;
}

void Ball::PaddleCollision(const Paddle& paddle) {
  int paddle_x{ paddle.get_x() };

  if (x_ + kBallWidth < paddle_x ||
      x_ > paddle_x + Paddle::kPaddleWidth ||
      y_ + kBallHeight < Paddle::kPaddleY ||
      y_ > Paddle::kPaddleY + Paddle::kPaddleHeight) {
    return;
  }

  Unmove();
  int ball_center{ x_ + (kBallWidth / 2) };
  int paddle_center{ paddle_x + (Paddle::kPaddleWidth / 2) };

  x_velocity_ = (ball_center - paddle_center) / 4;
  y_velocity_ *= -1;
  Move();
}

void Ball::BrickCollision(std::vector<Brick> *bricks) {
  for (size_t i{ 0 }; i < bricks->size(); ++i) {
    int brick_x{ (*bricks)[i].get_x() };
    int brick_y{ (*bricks)[i].get_y() };

    if (x_ + kBallWidth < brick_x ||
        x_ > brick_x + Brick::kBrickWidth ||
        y_ + kBallHeight < brick_y ||
        y_ > brick_y + Brick::kBrickHeight) {
      continue;
    }

    bricks->erase(bricks->begin() + i);

    Unmove();
    x_velocity_ *= -1;
    y_velocity_ *= -1;
    Move();
  }
}
