#include "src/entity/physics.h"

#include <cmath>

#include "src/entity/ball.h"
#include "src/entity/paddle.h"
#include "src/graphic/renderer.h"

static const Physics::Line kScreenTop{ 0, 0, Renderer::kVirtualWidth, 0 };
static const Physics::Line kScreenLeft{ 0, 0, 0, Renderer::kVirtualHeight };
static const Physics::Line kScreenRight{ Renderer::kVirtualWidth, 0,
                                         Renderer::kVirtualWidth,
                                         Renderer::kVirtualHeight };

void Physics::Update(Ball *ball, const Paddle& paddle,
                     std::vector<Brick> *bricks) {
  ApplyVelocity(ball, ball->x_vel_, ball->y_vel_, paddle, bricks);
}

double Physics::Distance(const Point& a, const Point& b) {
  return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

bool Physics::Intersection(const Line& a, const Line& b) {
  int denom{ ((b.y2 - b.y1) * (a.x2 - a.x1) - (b.x2 - b.x1) * (a.y2 - a.y1)) };
  int num_a{ ((b.x2 - b.x1) * (a.y1 - b.y1) - (b.y2 - b.y1) * (a.x1 - b.x1)) };
  int num_b{ ((a.x2 - a.x1) * (a.y1 - b.y1) - (a.y2 - a.y1) * (a.x1 - b.x1)) };

  if (denom == 0) {
    if (num_a == 0 && num_b == 0) {
      vertex_.x = (a.x1 + a.x2) / 2;
      vertex_.y = (a.y1 + a.y2) / 2;
      return true;
    }

    return false;
  }

  double ua{ num_a / static_cast<double>(denom) };
  double ub{ num_b / static_cast<double>(denom) };

  if (ua < 0 || ua > 1 || ub < 0 || ub > 1) {
    return false;
  }

  vertex_.x = a.x1 + ua * (a.x2 - a.x1);
  vertex_.y = a.y1 + ua * (a.y2 - a.y1);
  return true;
}

void Physics::CheckCollision(const Line& bound, Collision type) {
  if (Intersection(path_, bound)) {
    if (Distance(origin_, vertex_) < nearest_vertex_) {
      path_.x2 = vertex_.x;
      path_.y2 = vertex_.y;
      nearest_vertex_ = Distance(origin_, vertex_);
      surface_ = type;
    }
  }
}

void Physics::CheckPaddle(const Paddle& paddle) {
  const Line paddle_bound{ paddle.get_x_pos(),
                           Paddle::kPaddleYPos,
                           paddle.get_x_pos() + Paddle::kPaddleWidth,
                           Paddle::kPaddleYPos };
  CheckCollision(paddle_bound, kPaddle);
}

void Physics::CheckBricks(std::vector<Brick> *bricks) {
  for (auto brick : *bricks) {
    int i{ brick.get_x() };
    i++;
  }
  return;
}

void Physics::ApplyVelocity(Ball *ball, int x_velocity, int y_velocity,
                            const Paddle& paddle, std::vector<Brick> *bricks) {
  if (x_velocity == 0 && y_velocity == 0) {
    return;
  }

  origin_.x = x_velocity < 0 ? ball->x_pos_ : ball->x_pos_ + Ball::kBallWidth;
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

  int dx{ path_.x2 - path_.x1 };
  int dy{ path_.y2 - path_.y1 };

  ball->x_pos_ += dx;
  ball->y_pos_ += dy;

  x_velocity = abs(dx) > abs(x_velocity) ? 0 : x_velocity - dx;
  y_velocity = abs(dy) > abs(y_velocity) ? 0 : y_velocity - dy;

  int ball_center{ };
  int paddle_center{ };
  switch (surface_) {
    case kAxisX:
      ball->y_vel_ = -ball->y_vel_;
      y_velocity = -y_velocity;
      break;
    case kAxisY:
      ball->x_vel_ = -ball->x_vel_;
      x_velocity = -x_velocity;
      break;
    case kPaddle:
      ball_center = ball->x_pos_ + (Ball::kBallWidth / 2);
      paddle_center = paddle.get_x_pos() + (Paddle::kPaddleWidth / 2);
      ball->x_vel_ = (ball_center - paddle_center) / 4;
      ball->y_vel_ = -ball->y_vel_;
      y_velocity = -y_velocity;
      break;
    default:
      break;
  }

  ApplyVelocity(ball, x_velocity, y_velocity, paddle, bricks);
}
