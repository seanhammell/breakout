#ifndef SRC_GRAPHIC_RENDERER_H_
#define SRC_GRAPHIC_RENDERER_H_

#include "SDL2/SDL.h"

class Renderer {
 public:
  // Renderer dimensions to treat the display as if it were 192x160 pixels.
  static const int kVirtualWidth{ 192 };
  static const int kVirtualHeight{ 160 };

  Renderer();

  ~Renderer();

  // Getters.
  bool instantiated() const;
  SDL_Renderer *renderer() const;

  // Clears the Renderer to prepare for a new frame.
  void Clear();

  // Updates the screen with any rendering done since the previous call.
  void Present();

 private:
  // Creates the SDL_Renderer and returns whether the creation was successful.
  bool Create();

  // Destroys the SDL_Renderer.
  void Destroy();

  bool instantiated_{ false };
  SDL_Renderer *renderer_{ NULL };
};

#endif  // SRC_GRAPHIC_RENDERER_H_
