#ifndef SRC_GRAPHIC_WINDOW_H_
#define SRC_GRAPHIC_WINDOW_H_

#include <cstdint>

#include "SDL2/SDL.h"

class Window {
 public:
  // Window dimensions are based on the Atari 2600 (scaled up by a factor of 4).
  static const int kWindowWidth{ 768 };
  static const int kWindowHeight{ 640 };

  // Number of milliseconds per frame.
  static const int kTicksPerFrame{ 16 };

  Window();
  ~Window();

  // Getters.
  bool instantiated() const;
  SDL_Window *window() const;

  // Controls the game loop.
  void Loop();

 private:
  // Creates the SDL_Window and returns whether the creation was successful.
  bool Create();

  // Loads all media for the game and returns whether the load was successful.
  bool LoadMedia();

  // Destroys the SDL_Window.
  void Destroy();

  // Calculates and logs the fps each second.
  void CalculateFPS();

  // Delays the game loop to match the specified kTicksPerFrame.
  void SynchFPS() const;

  bool instantiated_{ false };
  SDL_Window *window_{ NULL };
  uint64_t ticks_{ 0 };
  uint64_t fps_{ 0 };
  uint64_t last_second_{ 0 };
};

#endif  // SRC_GRAPHIC_WINDOW_H_