#include "src/entity/physics.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>

#include "src/entity/ball.h"
#include "src/entity/paddle.h"
#include "src/graphic/renderer.h"
#include "src/media/chunk.h"
#include "src/media/media.h"

static const Physics::Line kScreenTop{0, 0, Renderer::kVirtualWidth, 0};
static const Physics::Line kScreenLeft{0, 0, 0, Renderer::kVirtualHeight};
static const Physics::Line kScreenRight{Renderer::kVirtualWidth, 0,
                                        Renderer::kVirtualWidth,
                                        Renderer::kVirtualHeight};

void Physics::Update(Ball* ball, const Paddle& paddle,
                     std::array<Brick, Brick::kMaxBricks>* bricks) {
  static constexpr int kTopThird = Renderer::kVirtualHeight / 3;
  int y_before = ball->y_pos_;
  ApplyVelocity(ball, ball->x_vel_, ball->y_vel_, paddle, bricks);
  if (y_before >= kTopThird && ball->y_pos_ < kTopThird) {
    ball->x_vel_ *= 2;
    ball->y_vel_ *= 2;
  } else if (y_before < kTopThird && ball->y_pos_ >= kTopThird) {
    ball->x_vel_ /= 2;
    ball->y_vel_ /= 2;
  }
}

double Physics::Distance(const Point& a, const Point& b) {
  return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

bool Physics::Intersection(const Line& a, const Line& b) {
  double denom{(b.y2 - b.y1) * (a.x2 - a.x1) - (b.x2 - b.x1) * (a.y2 - a.y1)};
  double num_a{(b.x2 - b.x1) * (a.y1 - b.y1) - (b.y2 - b.y1) * (a.x1 - b.x1)};
  double num_b{(a.x2 - a.x1) * (a.y1 - b.y1) - (a.y2 - a.y1) * (a.x1 - b.x1)};

  if (std::abs(denom) < kEpsilon) {
    if (std::abs(num_a) < kEpsilon && std::abs(num_b) < kEpsilon) {
      vertex_.x = (a.x1 + a.x2) / 2;
      vertex_.y = (a.y1 + a.y2) / 2;
      return true;
    }

    return false;
  }

  double ua{num_a / denom};
  double ub{num_b / denom};

  if (ua < 0 || ua > 1 || ub < 0 || ub > 1) {
    return false;
  }

  vertex_.x = a.x1 + ua * (a.x2 - a.x1);
  vertex_.y = a.y1 + ua * (a.y2 - a.y1);
  return true;
}

bool Physics::CheckCollision(const Line& bound, Collision type) {
  if (Intersection(path_, bound)) {
    if (Distance(origin_, vertex_) < nearest_vertex_) {
      path_.x2 = vertex_.x;
      path_.y2 = vertex_.y;
      nearest_vertex_ = Distance(origin_, vertex_);
      surface_ = type;
      return true;
    }
  }

  return false;
}

void Physics::CheckPaddle(const Paddle& paddle) {
  const double left{static_cast<double>(paddle.get_x_pos())};
  const double right{static_cast<double>(left + Paddle::kPaddleWidth)};
  const double top{static_cast<double>(Paddle::kPaddleYPos)};

  const Line paddle_bound{left, top, right, top};

  CheckCollision(paddle_bound, kPaddle);
}

void Physics::CheckBricks(std::array<Brick, Brick::kMaxBricks>* bricks) {
  hit_brick_ = NULL;

  for (size_t i{0}; i < bricks->size(); ++i) {
    if ((*bricks)[i].is_hit() || (*bricks)[i].get_type() == Brick::kNoType) {
      continue;
    }

    const double left{static_cast<double>((*bricks)[i].get_x_pos())};
    const double right{static_cast<double>(left + Brick::kBrickWidth)};
    const double top{static_cast<double>((*bricks)[i].get_y_pos())};
    const double bottom{static_cast<double>(top + Brick::kBrickHeight)};

    const Line left_bound{left, top, left, bottom};
    const Line right_bound{right, top, right, bottom};
    const Line top_bound{left, top, right, top};
    const Line bottom_bound{left, bottom, right, bottom};

    double x_magnitude{std::abs(path_.x2 - path_.x1)};
    double y_magnitude{std::abs(path_.y2 - path_.y1)};

    if (x_magnitude > y_magnitude) {
      if (x_magnitude > kEpsilon) {
        if (CheckCollision(left_bound, kAxisY) ||
            CheckCollision(right_bound, kAxisY)) {
          hit_brick_ = &(*bricks)[i];
        }
      }

      if (y_magnitude > kEpsilon) {
        if (CheckCollision(top_bound, kAxisX) ||
            CheckCollision(bottom_bound, kAxisX)) {
          hit_brick_ = &(*bricks)[i];
        }
      }
    } else {
      if (y_magnitude > kEpsilon) {
        if (CheckCollision(top_bound, kAxisX) ||
            CheckCollision(bottom_bound, kAxisX)) {
          hit_brick_ = &(*bricks)[i];
        }
      }

      if (x_magnitude > kEpsilon) {
        if (CheckCollision(left_bound, kAxisY) ||
            CheckCollision(right_bound, kAxisY)) {
          hit_brick_ = &(*bricks)[i];
        }
      }
    }
  }
}

void Physics::ApplyVelocity(Ball* ball, int x_velocity, int y_velocity,
                            const Paddle& paddle,
                            std::array<Brick, Brick::kMaxBricks>* bricks) {
  if (x_velocity == 0 && y_velocity == 0) {
    return;
  }

  origin_.x = x_velocity < 0 ? ball->x_pos_ : ball->x_pos_ + Ball::kBallWidth;
  if (x_velocity == 0) {
    origin_.x = ball->x_pos_ + (Ball::kBallWidth / 2);
  }

  origin_.y = y_velocity < 0 ? ball->y_pos_ : ball->y_pos_ + Ball::kBallHeight;
  vertex_.x = origin_.x + x_velocity;
  vertex_.y = origin_.y + y_velocity;

  path_.x1 = origin_.x;
  path_.y1 = origin_.y;
  path_.x2 = vertex_.x;
  path_.y2 = vertex_.y;
  nearest_vertex_ = Distance(origin_, vertex_);
  surface_ = kNone;

  CheckCollision(kScreenTop, kAxisX);
  CheckCollision(kScreenLeft, kAxisY);
  CheckCollision(kScreenRight, kAxisY);
  CheckPaddle(paddle);
  CheckBricks(bricks);

  int dx{static_cast<int>(path_.x2 - path_.x1)};
  int dy{static_cast<int>(path_.y2 - path_.y1)};

  ball->x_pos_ += dx;
  ball->y_pos_ += dy;

  x_velocity = std::abs(dx) > std::abs(x_velocity) ? 0 : x_velocity - dx;
  y_velocity = std::abs(dy) > std::abs(y_velocity) ? 0 : y_velocity - dy;

  int ball_center{ball->x_pos_ + (Ball::kBallWidth / 2)};
  int paddle_center{paddle.get_x_pos() + (Paddle::kPaddleWidth / 2)};
  int ball_paddle_offset{ball_center - paddle_center};
  switch (surface_) {
    case kAxisX:
      if (hit_brick_ == NULL) {
        kMedia.wall.PlayChunk();
      }
      ball->y_vel_ = -ball->y_vel_;
      y_velocity = -y_velocity;
      break;
    case kAxisY:
      if (hit_brick_ == NULL) {
        kMedia.wall.PlayChunk();
      }
      ball->x_vel_ = -ball->x_vel_;
      x_velocity = -x_velocity;
      break;
    case kPaddle:
      kMedia.paddle.PlayChunk();
      if ((ball->x_vel_ < 0 && ball_paddle_offset > 0) ||
          (ball->x_vel_ > 0 && ball_paddle_offset < 0)) {
        // Reverse the x-velocity of the ball if the ball-paddle offset has
        // a different sign than the x-velocity, e.g. the ball is travelling
        // to the left (negative) and hits the right side of the paddle
        // (positve).
        ball->x_vel_ *= -1;
      }
      ball->y_vel_ = -ball->y_vel_;

      x_velocity = ball->x_vel_;
      y_velocity = ball->y_vel_;
      break;
    default:
      break;
  }

  if (hit_brick_ != NULL) {
    kMedia.brick.PlayChunk();
    hit_brick_->hit();
  }

  ApplyVelocity(ball, x_velocity, y_velocity, paddle, bricks);
}
