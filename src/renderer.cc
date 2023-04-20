#include "src/renderer.h"

#include <stdio.h>

#include <cassert>

#include <SDL2/SDL.h>

Renderer::Renderer() {
  assert(!instantiated_);
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

bool Renderer::Create() {
  window_ = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, kWindowWidth, kWindowHeight, SDL_WINDOW_SHOWN);
  if (window_ == NULL) {
    fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
    return false;
  }

  renderer_ = SDL_CreateRenderer(window_, -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer_ == NULL) {
    fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
    return false;
  }

  return true;
}

void Renderer::Destroy() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);

  renderer_ = NULL;
  window_ = NULL;
}
