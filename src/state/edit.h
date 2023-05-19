#ifndef SRC_STATE_EDIT_H_
#define SRC_STATE_EDIT_H_

#include <array>

#include "SDL2/SDL.h"

#include "src/entity/brick.h"
#include "src/graphic/renderer.h"
#include "src/state/state_machine.h"

class Edit : public StateMachine {
 public:
  static constexpr SDL_Rect kZone{ 0, 19, Renderer::kVirtualWidth,
                                   Brick::kBrickHeight * 8 + 1 };

  explicit Edit(const char *level);

  ~Edit() = default;

  // Allows the user to edit the level and save when finished.
  void HandleInput(SDL_Event input) override;

  // Updates the bricks with any edits.
  StateMachine *Update() override;

  // Renders the level to the screen.
  void Render() override;

 private:
  // Write the brick data to the level file.
  void SaveLevel();

  const char *file_{ };
  std::array<Brick, Brick::kMaxBricks> bricks_{ };
  Brick hover_{ };
  bool in_zone_{ false };
};

#endif  // SRC_STATE_EDIT_H_
