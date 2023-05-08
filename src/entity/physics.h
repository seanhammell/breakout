#ifndef SRC_ENTITY_PHSX_H_
#define SRC_ENTITY_PHSX_H_

class Ball;

class Physics {
 public:
  enum CollisionAxis{
    kNone,
    kAxisX,
    kAxisY,
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

  Physics() = default;

  ~Physics() = default;

  // Updates the Ball's position.
  void Update(Ball *ball);

 private:
  // Retuns whether two lines intersect and records the vertex if they do.
  bool Intersection(const Line& a, const Line& b, Point *vertex);

  // Moves the Ball along it's path, adjusting for collisions.
  void ApplyVelocity(Ball *ball, int x_velocity, int y_velocity);
};

#endif  // SRC_ENTITY_PHSX_H_
