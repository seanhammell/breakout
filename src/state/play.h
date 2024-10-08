#ifndef SRC_STATE_PLAY_H_
#define SRC_STATE_PLAY_H_

#include <array>

#include "SDL2/SDL.h"
#include "src/entity/ball.h"
#include "src/entity/brick.h"
#include "src/entity/paddle.h"
#include "src/state/state_machine.h"
#include "src/ui/textbox.h"
#include "src/ui/widget.h"

class Play : public StateMachine {
 public:
  explicit Play(const char *level);

  ~Play();

  // Responds to user input during the game.
  void HandleInput(SDL_Event input) override;

  // Updates the entities and score.
  StateMachine *Update() override;

  // Renders the game objects and score to the screen.
  void Render() override;

 private:
  // Counts the number of live bricks, updating the score and ball speed
  // and returning if the level is cleared.
  bool ClearBricks();

  Textbox score_display_{};
  Widget hearts_{};
  Widget pause_screen_{};
  bool paused_{false};
  Ball ball_{};
  Paddle paddle_{};
  std::array<Brick, Brick::kMaxBricks> bricks_{};
  int score_{};
};

#endif  // SRC_STATE_PLAY_H_
