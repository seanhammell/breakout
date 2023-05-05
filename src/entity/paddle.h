#ifndef SRC_ENTITY_PADDLE_H_
#define SRC_ENTITY_PADDLE_H_

#include "SDL2/SDL.h"

#include "src/graphic/renderer.h"
#include "src/graphic/texture.h"

class Paddle {
 public:
  static const int kPaddleY{ Renderer::kVirtualHeight - 20 };
  static const int kPaddleWidth{ 24 };
  static const int kPaddleHeight{ 2 };
  static const int kPaddleVelocity{ 2 };

  Paddle() = default;
  Paddle(Texture *texture, SDL_Rect clip = {0, 3, kPaddleWidth,
                                            kPaddleHeight});

  ~Paddle() = default;

  int get_x_pos() const { return x_pos_; }

  // Handles user input for the Paddle.
  void HandleInput(SDL_Event input);

  // Updates the Paddle with one frame of behavior.
  void Update();

  // Renders the Paddle to the screen.
  void Render();

 private:
  int x_pos_{ (Renderer::kVirtualWidth - Paddle::kPaddleWidth) / 2 };
  int x_vel_{ 0 };
  Texture *texture_{ NULL };
  SDL_Rect clip_{ };
};

#endif  // SRC_ENTITY_PADDLE_H_
