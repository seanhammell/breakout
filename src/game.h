#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include "SDL2/SDL.h"
#include "src/graphic/renderer.h"
#include "src/graphic/window.h"
#include "src/state/state_machine.h"

struct Game {
  Window window;
  Renderer renderer;
  StateMachine *game_state;
};

extern Game kGame;

#endif  // SRC_GAME_H_
