#include "src/gfx/window.h"

#include <stdio.h>

#include <cassert>
#include <cstdint>

#include "SDL2/SDL.h"

#include "src/state.h"
#include "src/ecs/graphics_component.h"
#include "src/fsm/menu_state.h"
#include "src/gfx/renderer.h"

Window::Window() {
  assert(!instantiated_);  // ensures there is only one Window instance.
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
  assert(kState.window.IsInstantiated());
  assert(kState.renderer.IsInstantiated());
  assert(GraphicsComponent::LoadTextures());
  kState.game_state = new MenuState();

  SDL_Event e;
  while (true) {
    ticks_ = SDL_GetTicks64();

    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        delete kState.game_state;
        return;
      }
    }

    kState.renderer.Clear();
    kState.game_state->Update();
    kState.renderer.Present();

    CalculateFPS();
    SynchFPS();
  }
}

bool Window::Create() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    return false;
  }

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
  SDL_Quit();

  window_ = NULL;
}

void Window::CalculateFPS() {
  const uint64_t now{ SDL_GetTicks64() };
  if (now - last_second_ > 1000) {
    SDL_Log("FPS: %llu\n", fps_);
    fps_ = 0;
    last_second_ = now;
  }

  ++fps_;
}

void Window::SynchFPS() const {
  const uint64_t remainder{ SDL_GetTicks64() - ticks_ };
  if (remainder < kTicksPerFrame) {
    SDL_Delay(kTicksPerFrame - remainder);
  }
}
