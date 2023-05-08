#ifndef SRC_ENTITY_PHYSICS_H_
#define SRC_ENTITY_PHYSICS_H_

namespace physics{

enum Collision {
  kNone,
  kHorizontal,
  kVertical,
};

struct Point {
  int x;
  int y;
};

struct Line {
  int x1;
  int y1;
  int x2;
  int y2;
};

double Distance(const Point& a, const Point& b);

bool FindIntersection(const Line& a, const Line& b, Point *intersect);

Collision WallCollision(const Line& path, Point *intersect);

} // namespace collision

#endif  // SRC_ENTITY_PHYSICS_H_
