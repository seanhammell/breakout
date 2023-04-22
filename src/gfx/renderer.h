#ifndef SRC_GFX_RENDERER_H_
#define SRC_GFX_RENDERER_H_

#include <SDL2/SDL.h>

class Renderer {
 public:
  static constexpr int kWindowWidth{ 768 };
  static constexpr int kWindowHeight{ 640 };

  static constexpr int kVirtualWidth{ 384 };
  static constexpr int kVirtualHeight{ 320 };

  Renderer();
  ~Renderer();

  bool IsInstantiated() { return instantiated_; }
  SDL_Renderer *GetRenderer() { return renderer_; }

  void Clear();
  void Present();

 private:
  bool Create();
  void Destroy();

  static inline bool instantiated_{ false };
  SDL_Window *window_{ NULL };
  SDL_Renderer *renderer_{ NULL };
};

#endif  // SRC_GFX_RENDERER_H_
