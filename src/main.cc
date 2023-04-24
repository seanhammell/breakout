#include <stdio.h>

#include "SDL2/SDL.h"

#include "src/state.h"

// Global game state.
State kState;

int main() {
  kState.window.Loop();

  return 0;
}
