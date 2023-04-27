#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include "SDL2/SDL.h"

#include "src/fsm/state_machine.h"
#include "src/gfx/renderer.h"
#include "src/gfx/window.h"

struct Game {
  Window window;
  Renderer renderer;
  StateMachine *game_state;
};

extern Game kGame;

#endif  // SRC_GAME_H_
