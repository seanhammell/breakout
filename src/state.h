#ifndef SRC_STATE_H_
#define SRC_STATE_H_

#include "SDL2/SDL.h"

#include "src/fsm/state_machine.h"
#include "src/gfx/renderer.h"
#include "src/gfx/window.h"

struct State {
  Window window;
  Renderer renderer;
  StateMachine *game_state;
};

extern State kState;

#endif  // SRC_STATE_H_
