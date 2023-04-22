#include "src/gfx/window.h"

#include <stdio.h>

#include <cassert>

#include <SDL2/SDL.h>

Window::Window() {
  assert(!instantiated_);
  if (!Create()) {
    Destroy();
  } else {
    instantiated_ = true;
  }
}

Window::~Window() {
  Destroy();
  instantiated_ = false;
}

void Window::Loop() {
  SDL_Event e;
  ticks_ = SDL_GetTicks64();
  while (true) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        return;
      }
    }
  }
}

bool Window::Create() {
  window_ = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, kWindowWidth,
                             kWindowHeight, SDL_WINDOW_SHOWN);
  if (window_ == NULL) {
    fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
    return false;
  }

  return true;
}

void Window::Destroy() {
  SDL_DestroyWindow(window_);
  window_ = NULL;
}
