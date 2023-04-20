#ifndef SRC_RENDERER_H_
#define SRC_RENDERER_H_

#include <SDL2/SDL.h>

class Renderer {
 public:
  static constexpr int kWindowWidth{ 1280 };
  static constexpr int kWindowHeight{ 720 };

  Renderer();
  ~Renderer();

 private:
  bool Create();
  void Destroy();

  static bool instantiated_;
  SDL_Window *window_{ NULL };
  SDL_Renderer *renderer_{ NULL };
};

#endif  // SRC_RENDERER_H_
