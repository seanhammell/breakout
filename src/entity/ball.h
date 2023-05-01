#ifndef SRC_ENTITY_BALL_H_
#define SRC_ENTITY_BALL_H_

#include "SDL2/SDL.h"

#include "src/entity/graphics_component.h"
#include "src/entity/physics_component.h"
#include "src/graphic/renderer.h"
#include "src/graphic/texture.h"

class Ball {
 public:
  static const int kBallWidth{ 4 };
  static const int kBallHeight{ 4 };

  Ball() = default;
  Ball(Texture *texture, SDL_Rect clip = {48, 6, kBallWidth, kBallHeight});

  ~Ball() = default;

  // Updates the Ball with one frame of behavior.
  void Update();

 private:
  int x_{ (Renderer::kVirtualWidth - kBallWidth) / 2 };
  int y_{ Renderer::kVirtualHeight - 24};
  PhysicsComponent physics_{ };
  GraphicsComponent graphics_{ };
};

#endif  // SRC_ENTITY_BALL_H_
