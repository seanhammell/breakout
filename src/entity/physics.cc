#include "src/entity/physics.h"

#include <cmath>

#include "src/graphic/renderer.h"

static const double kEpsilon{ 0.0001 };

double physics::Distance(const Point& a, const Point& b) {
  return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

bool physics::FindIntersection(const Line& a, const Line& b, Point *intersect) {
  double denominator{ static_cast<double>((b.y2 - b.y1) * (a.x2 - a.x1) -
                                          (b.x2 - b.x1) * (a.y2 - a.y1)) };
  double numerator_a{ static_cast<double>((b.x2 - b.x1) * (a.y1 - b.y1) -
                                          (b.y2 - b.y1) * (a.x1 - b.x1)) };
  double numerator_b{ static_cast<double>((a.x2 - a.x1) * (a.y1 - b.y1) -
                                          (a.y2 - a.y1) * (a.x1 - b.x1)) };

  if (abs(denominator) < kEpsilon) {
    if (abs(numerator_a) < kEpsilon && abs(numerator_b) < kEpsilon) {
      intersect->x = (a.x1 + a.y1) / 2;
      intersect->y = (a.x2 + a.y2) / 2;
      return true;
    }

    return false;
  }

  double ua{ numerator_a / denominator };
  double ub{ numerator_b / denominator };

  if (ua < 0 || ua > 1 || ub < 0 || ub > 1) {
    return false;
  }

  intersect->x = a.x1 + ua * (a.x2 - a.x1);
  intersect->y = a.y1 + ua * (a.y2 - a.y1);
  return true;
}

physics::Collision physics::WallCollision(const Line& path, Point *intersect) {
  static const physics::Line kScreenTop{ 0, 0, Renderer::kVirtualWidth, 0 };
  static const physics::Line kScreenLeft{ 0, 0, 0, Renderer::kVirtualHeight };
  static const physics::Line kScreenRight{ Renderer::kVirtualWidth, 0,
                                           Renderer::kVirtualWidth,
                                           Renderer::kVirtualHeight };

  if (FindIntersection(path, kScreenTop, intersect)) {
    return kHorizontal;
  } else if (FindIntersection(path, kScreenLeft, intersect) ||
             FindIntersection(path, kScreenRight, intersect)) {
    return kVertical;
  }

  return kNone;
}
