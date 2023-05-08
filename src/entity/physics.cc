#include "src/entity/physics.h"

#include <cmath>

#include "src/entity/ball.h"
#include "src/graphic/renderer.h"

static const Physics::Line kScreenTop{ 0, 0, Renderer::kVirtualWidth, 0 };
static const Physics::Line kScreenLeft{ 0, 0, 0, Renderer::kVirtualHeight };
static const Physics::Line kScreenRight{ Renderer::kVirtualWidth, 0,
                                         Renderer::kVirtualWidth,
                                         Renderer::kVirtualHeight };

void Physics::Update(Ball *ball) {
  ApplyVelocity(ball, ball->x_vel_, ball->y_vel_);
}

bool Physics::Intersection(const Line& a, const Line& b, Point *vertex) {
  int denom{ ((b.y2 - b.y1) * (a.x2 - a.x1) - (b.x2 - b.x1) * (a.y2 - a.y1)) };
  int num_a{ ((b.x2 - b.x1) * (a.y1 - b.y1) - (b.y2 - b.y1) * (a.x1 - b.x1)) };
  int num_b{ ((a.x2 - a.x1) * (a.y1 - b.y1) - (a.y2 - a.y1) * (a.x1 - b.x1)) };

  if (denom == 0) {
    if (num_a == 0 && num_b == 0) {
      vertex->x = (a.x1 + a.x2) / 2;
      vertex->y = (a.y1 + a.y2) / 2;
      return true;
    }

    return false;
  }

  double ua{ num_a / static_cast<double>(denom) };
  double ub{ num_b / static_cast<double>(denom) };

  if (ua < 0 || ua > 1 || ub < 0 || ub > 1) {
    return false;
  }

  vertex->x = a.x1 + ua * (a.x2 - a.x1);
  vertex->y = a.y1 + ua * (a.y2 - a.y1);
  return true;
}

void Physics::ApplyVelocity(Ball *ball, int x_velocity, int y_velocity) {
  if (x_velocity == 0 && y_velocity == 0) {
    return;
  }

  Line path{ };
  Point vertex{ };
  CollisionAxis axis{ kNone };

  path.x1 = x_velocity < 0 ? ball->x_pos_ : ball->x_pos_ + Ball::kBallWidth;
  path.y1 = y_velocity < 0 ? ball->y_pos_ : ball->y_pos_ + Ball::kBallHeight;
  path.x2 = path.x1 + x_velocity;
  path.y2 = path.y1 + y_velocity;

  vertex.x = path.x2;
  vertex.y = path.y2;

  if (Intersection(path, kScreenTop, &vertex)) {
    axis = kAxisX;
  }

  if (Intersection(path, kScreenLeft, &vertex) ||
      Intersection(path, kScreenRight, &vertex)) {
    axis = kAxisY;
  }

  int dx{ vertex.x - path.x1 };
  int dy{ vertex.y - path.y1 };

  ball->x_pos_ += dx;
  ball->y_pos_ += dy;

  x_velocity = abs(dx) > abs(x_velocity) ? 0 : x_velocity - dx;
  y_velocity = abs(dy) > abs(y_velocity) ? 0 : y_velocity - dy;

  if (axis == kAxisX) {
    ball->y_vel_ = -ball->y_vel_;
    y_velocity = -y_velocity;
  }

  if (axis == kAxisY) {
    ball->x_vel_ = -ball->x_vel_;
    x_velocity = -x_velocity;
  }

  ApplyVelocity(ball, x_velocity, y_velocity);
}
