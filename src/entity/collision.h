#ifndef SRC_ENTITY_COLLISION_H_
#define SRC_ENTITY_COLLISION_H_

namespace collision {

const double kEpsilon{ 0.0001 };

struct Point {
  double x;
  double y;
};

struct Line {
  double x1;
  double y1;
  double x2;
  double y2;
};

// Returns if the lines intersects and records the intersection point.
bool LineLineIntersect(Line a, Line b, Point *intersect);

} // namespace collision

#endif  // SRC_ENTITY_COLLISION_H_
