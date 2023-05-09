#ifndef SRC_ENTITY_PHSX_H_
#define SRC_ENTITY_PHSX_H_

#include <vector>

#include "src/entity/brick.h"
#include "src/entity/paddle.h"

class Ball;

class Physics {
 public:
  enum Collision{
    kNone,
    kAxisX,
    kAxisY,
    kPaddle,
  };

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

  Physics() = default;

  ~Physics() = default;

  // Updates the Ball's position.
  void Update(Ball *ball, const Paddle& paddle, std::vector<Brick> *bricks);

 private:
  // Returns the distance between two points.
  double Distance(const Point& a, const Point& b);

  // Retuns whether two lines intersect and records the vertex if they do.
  bool Intersection(const Line& a, const Line& b);

  // Checks for a collision between the Ball's path and the bound, returning
  // whether the collision is the nearest.
  bool CheckCollision(const Line& bound, Collision type);

  // Creates the bounds for the Paddle and Bricks to check for collisions.
  void CheckPaddle(const Paddle& paddle);
  void CheckBricks(std::vector<Brick> *bricks);

  // Moves the Ball along it's path, adjusting for collisions.
  void ApplyVelocity(Ball *ball, int x_velocity, int y_velocity,
                     const Paddle& paddle, std::vector<Brick> *bricks);

  Point origin_{ };
  Point vertex_{ };
  Line path_{ };
  double nearest_vertex_{ };
  Collision surface_{ };
  Brick *hit_brick_{ NULL };
};

#endif  // SRC_ENTITY_PHSX_H_
