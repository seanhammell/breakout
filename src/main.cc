#include <stdio.h>

#include "SDL2/SDL.h"

#include "src/state.h"

// Global game state.
State kState;

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
  Open();

  kState.window.Loop();

  Close();
  return 0;
}
