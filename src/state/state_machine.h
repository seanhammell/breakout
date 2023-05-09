#ifndef SRC_STATE_STATE_MACHINE_H_
#define SRC_STATE_STATE_MACHINE_H_

#include "SDL2/SDL.h"

class StateMachine {
 public:
  virtual ~StateMachine() = default;

  bool is_valid() const { return valid_; }
  void valid(){ valid_ = true; }

  virtual StateMachine *HandleInput(SDL_Event) = 0;
  virtual void Update() = 0;
  virtual void Render() = 0;
 
 private:
  bool valid_{ false };
};

#endif  // SRC_STATE_STATE_MACHINE_H_
