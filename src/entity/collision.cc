#include "src/entity/collision.h"

#include <cstdlib>

bool collision::LineLineIntersect(Line a, Line b, Point *intersect) {
  double denom{ (b.y2 - b.y1) * (a.x2 - a.x1) - (b.x2 - b.x1) * (a.y2 - a.y1) };
  double num_a{ (b.x2 - b.x1) * (a.y1 - b.y1) - (b.y2 - b.y1) * (a.x1 - b.x1) };
  double num_b{ (a.x2 - a.x1) * (a.y1 - b.y1) - (a.y2 - a.y1) * (a.x1 - b.x1) };

  if (abs(denom) < kEpsilon) {
    if (abs(num_a) < kEpsilon && abs(num_b) < kEpsilon) {
      intersect->x = (a.x1 + a.x2) / 2;
      intersect->y = (a.y1 + a.y2) / 2;
      return true;
    }
    intersect->x = 0;
    intersect->y = 0;
    return false;
  }

  double ua{ num_a / denom };
  double ub{ num_b / denom };
  if (ua < 0 || ua > 1 || ub < 0 || ub > 1) {
    intersect->x = 0;
    intersect->y = 0;
    return false;
  }
  intersect->x = a.x1 + ua * (a.x2 - a.x1);
  intersect->y = a.y1 + ua * (a.y2 - a.y1);
  return true;
}
