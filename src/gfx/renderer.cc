#include "src/gfx/renderer.h"

#include <stdio.h>

#include <cassert>

#include <SDL2/SDL.h>

// Constructs the Renderer, destroying the window and renderer if the creation
// was unsuccessful.
Renderer::Renderer() {
  assert(!instantiated_);
  if (!Create()) {
    Destroy();
  } else {
    instantiated_ = true;
  }
}

// Destructs the Renderer and destroys the window and renderer.
Renderer::~Renderer() {
  Destroy();
  instantiated_ = false;
}

// Clears the rendering target.
void Renderer::Clear() {
  SDL_SetRenderDrawColor(renderer_, 0x2E, 0x34, 0x40, 0xFF);
  SDL_RenderClear(renderer_);
}

// Presents any rendering performed since the previous call.
void Renderer::Present() {
  SDL_RenderPresent(renderer_);
}

// Creates the window and renderer and returns whether the creation was
// successful.
bool Renderer::Create() {
  window_ = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, kWindowWidth,
                             kWindowHeight, SDL_WINDOW_SHOWN);
  if (window_ == NULL) {
    fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
    return false;
  }

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
  if (renderer_ == NULL) {
    fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
    return false;
  }

  if (SDL_RenderSetLogicalSize(renderer_, kVirtualWidth, kVirtualHeight) != 0) {
    fprintf(stderr, "Error setting locigal dimensions: %s\n", SDL_GetError());
    return false;
  }

  return true;
}

// Destroys the window and renderer.
void Renderer::Destroy() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);

  renderer_ = NULL;
  window_ = NULL;
}
