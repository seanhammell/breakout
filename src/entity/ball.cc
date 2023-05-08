#include "src/entity/ball.h"

#include <cmath>
#include <cstdlib>

#include "SDL2/SDL.h"

#include "src/entity/physics.h"
#include "src/entity/brick.h"
#include "src/entity/paddle.h"
#include "src/graphic/renderer.h"
#include "src/graphic/texture.h"

Ball::Ball(Texture *texture, SDL_Rect clip)
    : texture_{ texture }, clip_{ clip } {}

void Ball::HandleInput(SDL_Event input) {
  if (input.key.keysym.sym == SDLK_SPACE && x_vel_ == 0 && y_vel_ == 0) {
    x_vel_ = 1;
    y_vel_ = -3;
  }
}

void Ball::Update() {
  ApplyVelocity(x_vel_, y_vel_);
}

void Ball::Render() {
  texture_->Render(x_pos_, y_pos_, &clip_);
}

void Ball::ApplyVelocity(int x_vel, int y_vel) {
  using namespace physics;

  // Moving down and to the left causes this to trigger immediately
  if (x_vel == 0 && y_vel == 0) {
    return;
  }

  Point origin{ x_vel < 0 ? x_pos_ : x_pos_ + kBallWidth,
                y_vel < 0 ? y_pos_ : y_pos_ + kBallHeight };
  Point dest{ origin.x + x_vel, origin.y + y_vel };
  Line path{ origin.x, origin.y, dest.x, dest.y };
  Collision axis{ kNone };

  axis = WallCollision(path, &dest);

  int delta_x{ dest.x - origin.x };
  int delta_y{ dest.y - origin.y };

  x_pos_ += delta_x;
  y_pos_ += delta_y;

  x_vel = abs(delta_x) > abs(x_vel) ? 0 : x_vel - delta_x;
  y_vel = abs(delta_y) > abs(y_vel) ? 0 : y_vel - delta_y;

  if (axis != kNone) {
    if (axis == kHorizontal) {
      y_vel_ = -y_vel_;
      y_vel = -y_vel;
    } else if (axis == kVertical) {
      x_vel_ = -x_vel_;
      x_vel = -x_vel;
    }
  }

  ApplyVelocity(x_vel, y_vel);

  // use the x_vel and y_vel to decide which corner of the ball to use as the
  // starting point of the line. For example, x_vel > 0 and y_vel < 0 means the
  // ball is moving up and right, so use the top-right corner of the ball.
  // Likewise, if x_vel < 0 and y_vel > 0, the ball is moving down and left,
  // so use the bottom-left corner of the ball.

  // for each collision line
  //   if there is an intercept
  //     check if it is the closest point to the ball so far

  // move to the intercept
  // subtract the movement from x_vel and y_vel
  // recursively apply veloctiy until it runs out
}
