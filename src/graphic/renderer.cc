#include "src/graphic/renderer.h"

#include <stdio.h>

#include <cassert>

#include "SDL2/SDL.h"
#include "src/game.h"
#include "src/graphic/window.h"

Renderer::Renderer() {
  assert(!instantiated_);  // ensures there is only one Renderer instance.
  if (!Create()) {
    Destroy();
  } else {
    instantiated_ = true;
  }
}

Renderer::~Renderer() {
  Destroy();
  instantiated_ = false;
}

bool Renderer::get_instantiated() const { return instantiated_; }

SDL_Renderer *Renderer::get_renderer() const { return renderer_; }

void Renderer::Clear() {
  SDL_SetRenderDrawColor(renderer_, 0x2E, 0x34, 0x40, 0xFF);
  SDL_RenderClear(renderer_);
}

void Renderer::Present() { SDL_RenderPresent(renderer_); }

bool Renderer::Create() {
  assert(kGame.window.get_instantiated());
  renderer_ =
      SDL_CreateRenderer(kGame.window.get_window(), -1,
                         SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
