#ifndef SRC_STATE_EDIT_H_
#define SRC_STATE_EDIT_H_

#include <vector>

#include "SDL2/SDL.h"

#include "src/entity/brick.h"
#include "src/state/state_machine.h"

class Edit : public StateMachine {
 public:
  explicit Edit(const char *level);

  ~Edit() = default;

  // Allows the user to edit the level and save when finished.
  void HandleInput(SDL_Event) override {}

  // Updates the bricks with any edits.
  StateMachine *Update() override { return NULL; }

  // Renders the level to the screen.
  void Render() override;

 private:
  std::vector<Brick> bricks_{ };
};

#endif  // SRC_STATE_EDIT_H_
