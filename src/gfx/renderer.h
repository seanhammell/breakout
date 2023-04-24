#ifndef SRC_GFX_RENDERER_H_
#define SRC_GFX_RENDERER_H_

#include "SDL2/SDL.h"

class Renderer {
 public:
  // Renderer dimensions to treat the display as if it were 192x160 pixels.
  static const int kVirtualWidth{ 192 };
  static const int kVirtualHeight{ 160 };

  Renderer();
  ~Renderer();

  // Returns whether the Renderer is instantiated.
  bool IsInstantiated() const { return instantiated_; }

  // Provides access to the SDL_Renderer.
  SDL_Renderer *GetRenderer() const { return renderer_; }

 private:
  // Creates the SDL_Renderer and returns whether the creation was successful.
  bool Create();

  // Destroys the SDL_Renderer.
  void Destroy();

  bool instantiated_{ false };
  SDL_Renderer *renderer_{ NULL };
};

#endif  // SRC_GFX_RENDERER_H_
