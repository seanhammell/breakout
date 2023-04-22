#ifndef SRC_GFX_WINDOW_H_
#define SRC_GFX_WINDOW_H_

#include <cstdint>

#include <SDL2/SDL.h>

class Window {
 public:
  static const int kWindowWidth{ 768 };
  static const int kWindowHeight{ 640 };

  static const int kTicksPerFrame{ 16 };

  Window();
  ~Window();

  void Loop();

 private:
  bool Create();
  void Destroy();

  void CalculateFPS();
  void SynchFPS();

  bool instantiated_{ false };
  SDL_Window *window_{ NULL };

  uint64_t ticks_{ 0 };
  uint64_t fps_{ 0 };
  uint64_t last_second_{ 0 };
};

#endif  // SRC_GFX_WINDOW_H_
