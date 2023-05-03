#include "src/graphic/window.h"

#include <stdio.h>

#include <cassert>
#include <cstdint>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "src/game.h"
#include "src/graphic/renderer.h"
#include "src/state/menu_state.h"
#include "src/state/play_state.h"

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

bool Window::get_instantiated() const {
  return instantiated_;
}

SDL_Window *Window::get_window() const {
  return window_;
}

void Window::Loop() {
  assert(kGame.window.get_instantiated());
  assert(kGame.renderer.get_instantiated());
  assert(LoadMedia());
  kGame.game_state = new MenuState();

  SDL_Event e;
  while (true) {
    ticks_ = SDL_GetTicks64();

    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        delete kGame.game_state;
        return;
      }

      StateMachine *new_state = kGame.game_state->HandleInput(e);
      if (new_state != NULL) {
        delete kGame.game_state;
        kGame.game_state = new_state;
      }
    }

    kGame.game_state->Update();

    kGame.renderer.Clear();
    kGame.game_state->Render();
    kGame.renderer.Present();

    CalculateFPS();
    SynchFPS();
  }
}

bool Window::Create() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    return false;
  }

  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    fprintf(stderr, "Error initializing SDL_image: %s\n", IMG_GetError());
    return false;
  }

  if (TTF_Init() != 0) {
    fprintf(stderr, "Error initializing SDL_ttf: %s\n", TTF_GetError());
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

bool Window::LoadMedia() {
  if (!MenuState::Load()) { return false; }
  if (!PlayState::Load()) { return false; }
  return true;
}

void Window::Destroy() {
  SDL_DestroyWindow(window_);
  TTF_Quit();
  IMG_Quit();
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
