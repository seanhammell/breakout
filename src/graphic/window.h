#ifndef SRC_GRAPHIC_WINDOW_H_
#define SRC_GRAPHIC_WINDOW_H_

#include <cstdint>

#include "SDL2/SDL.h"

class Window {
 public:
  // Window dimensions are based on the Atari 2600 (scaled up by a factor of 4).
  static const int kWindowWidth{ 768 };
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

  // Loads all media for the game and returns whether the load was successful.
  bool LoadMedia();

  // Destroys the SDL_Window.
  void Destroy();

  bool instantiated_{ false };
  SDL_Window *window_{ NULL };
  int fps_{ 0 };
  uint64_t last_second_{ SDL_GetTicks64() };
};

#endif  // SRC_GRAPHIC_WINDOW_H_
