#ifndef SRC_STATE_STATE_MACHINE_H_
#define SRC_STATE_STATE_MACHINE_H_

#include "SDL2/SDL.h"

class StateMachine {
 public:
  enum States {
    kNoState,
    kMenuState,
    kPlayState,
  };

  virtual ~StateMachine() = default;

  bool is_valid() const { return valid_; }
  States get_next_state() const { return next_state_; }

  void valid() { valid_ = true; }
  void next_state(States next_state) { next_state_ = next_state; }

  virtual void HandleInput(SDL_Event) = 0;
  virtual StateMachine *Update() = 0;
  virtual void Render() = 0;

 private:
  bool valid_{ false };
  States next_state_{ kNoState };
};

#endif  // SRC_STATE_STATE_MACHINE_H_
