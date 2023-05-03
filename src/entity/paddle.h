#ifndef SRC_ENTITY_PADDLE_H_
#define SRC_ENTITY_PADDLE_H_

#include "SDL2/SDL.h"

#include "src/graphic/renderer.h"
#include "src/graphic/texture.h"

class Paddle {
 public:
  static const int kPaddleWidth{ 32 };
  static const int kPaddleHeight{ 4 };
  static const int kPaddleVelocity{ 4 };

  Paddle() = default;
  Paddle(Texture *texture, SDL_Rect clip = {16, 6, kPaddleWidth,
                                            kPaddleHeight});

  ~Paddle() = default;

  // Handles user input for the paddle.
  void HandleInput(SDL_Event input);

  // Updates the Paddle with one frame of behavior.
  void Update();

 private:
  int x_{ (Renderer::kVirtualWidth - Paddle::kPaddleWidth) / 2 };
  const int y_{ Renderer::kVirtualHeight - 20 };
  int velocity_{ 0 };
  Texture *texture_{ NULL };
  SDL_Rect clip_{ };
};

#endif  // SRC_ENTITY_PADDLE_H_
