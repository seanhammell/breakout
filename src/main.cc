#include <stdio.h>

#include <SDL2/SDL.h>

#include "src/renderer.h"

bool Open() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    return false;
  }

  return true;
}

void Close() {
  SDL_Quit();
}

int main() {
  if (!Open()) {
    return 0;
  }

  Renderer renderer;
  if (!renderer.IsInstantiated()) {
    Close();
    return 0;
  }

  SDL_Event e;
  for (;;) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        Close();
        return 0;
      }
    }

    renderer.Clear();
    renderer.Present();
  }

  return 0;
}
