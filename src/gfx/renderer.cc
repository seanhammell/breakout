#include "src/gfx/renderer.h"

#include <stdio.h>

#include <cassert>

#include "SDL2/SDL.h"

#include "src/state.h"

Renderer::Renderer() {
  assert(!instantiated_);  // ensures there is only one Renderer instance.
  if (!Create()) {
    Destroy();
  } else {
    instantiated_ = true;
  }
}

Renderer::Renderer() {
  Destroy();
  instantiated_ = false;
}

bool Renderer::Create() {
  renderer_ = SDL_CreateRenderer(kState.window.GetWindow(), -1,
                                 SDL_RENDERER_ACCELERATED);
  if (renderer_ == NULL) {
    fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
    return false;
  }

  if (SDL_RenderSetLogicalSize(renderer_, kVirtualWidth, kVirtualHeight) != 0) {
    fprintf(stderr, "Error setting virtual dimensions: %s\n", SDL_GetError());
    return false;
  }

  return true;
}

void Renderer::Destroy() {
  SDL_DestroyRenderer(renderer_);
  renderer_ = NULL;
}
