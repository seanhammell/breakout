#include "src/graphic/window.h"

#include <stdio.h>

#include <cassert>
#include <cstdint>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include "src/game.h"
#include "src/graphic/renderer.h"
#include "src/state/menu.h"

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
  kGame.game_state = new Menu();

  SDL_Event e;
  while (true) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        delete kGame.game_state;
        return;
      }

      kGame.game_state->HandleInput(e);
    }

    StateMachine *new_state = kGame.game_state->Update();
    if (new_state != NULL) {
      if (!new_state->get_valid()) {
        fprintf(stderr, "Invalid state\n");
        return;
      }
      delete kGame.game_state;
      kGame.game_state = new_state;
    }

    kGame.renderer.Clear();
    kGame.game_state->Render();
    kGame.renderer.Present();
    ++fps_;

    uint64_t now{ SDL_GetTicks64() };
    if (now - last_second_ > 1000ull) {
      SDL_Log("FPS: %d\n", fps_);
      fps_ = 0;
      last_second_ = now;
    }
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

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    fprintf(stderr, "Error initializing SDL_mixer: %s\n", Mix_GetError());
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
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();

  window_ = NULL;
}
