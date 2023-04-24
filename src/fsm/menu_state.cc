#include "src/fsm/menu_state.h"

#include "SDL2/SDL.h"

#include "src/fsm/state_machine.h"

StateMachine *MenuState::HandleInput(SDL_Event input) {
  if (input.type == SDL_KEYDOWN) {
    if (input.key.keysym.sym == SDLK_SPACE) {
      return new MenuState();
    }
  }

  return NULL;
}
