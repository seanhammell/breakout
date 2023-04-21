#include "src/states/state_machine.h"

#include <cassert>

#include <SDL2/SDL.h>

#include "src/states/state.h"
#include "src/states/menu_state.h"

// Constructs a StateMachine, setting the state to the main menu.
StateMachine::StateMachine() {
  assert(!instantiated_);
  state_ = new MenuState();
  instantiated_ = true;
}

// Destructs a StateMachine.
StateMachine::~StateMachine() {
  delete state_;
  instantiated_ = false;
}

// Passes input to the state to handle, updating the state if the input
// triggered a transition.
void StateMachine::HandleInput(SDL_Event input) {
  State *state = state_->HandleInput(*this, input);
  if (state != NULL) {
    delete state_;
    state_ = state;
  }
}

// Updates the state.
void StateMachine::Update() {
  state_->Update();
}
