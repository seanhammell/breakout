#ifndef SRC_GRAPHIC_WINDOW_H_
#define SRC_GRAPHIC_WINDOW_H_

#include <cstdint>

#include "SDL2/SDL.h"

class Window {
 public:
  static const int kWindowWidth{ 796 };
  static const int kWindowHeight{ 640 };

  Window();

  ~Window();

  bool get_instantiated() const;
  SDL_Window *get_window() const;

  // Controls the game loop.
  void Loop();

 private:
  // Creates the SDL_Window and returns whether the creation was successful.
  bool Create();

  // Destroys the SDL_Window.
  void Destroy();

  bool instantiated_{ false };
  SDL_Window *window_{ NULL };
  int fps_{ 0 };
  uint64_t last_second_{ SDL_GetTicks64() };
};

#endif  // SRC_GRAPHIC_WINDOW_H_
