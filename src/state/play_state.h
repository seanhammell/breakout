#ifndef SRC_STATE_PLAY_STATE_H_
#define SRC_STATE_PLAY_STATE_H_

#include <cstddef>
#include <vector>

#include "SDL2/SDL.h"

#include "src/entity/ball.h"
#include "src/entity/brick.h"
#include "src/entity/paddle.h"
#include "src/state/state_machine.h"
#include "src/ui/textbox.h"
#include "src/ui/widget.h"

class PlayState : public StateMachine {
 public:
  PlayState();

  ~PlayState() = default;

  // Responds to user input during the game.
  void HandleInput(SDL_Event input) override;

  // Updates the entities and score.
  StateMachine *Update() override;

  // Renders the game objects and score to the screen.
  void Render() override;

 private:
  // Loads the starting Bricks for a given level.
  bool LoadLevel();

  // Counts the number of live bricks, updating the score and ball speed
  // accordingly.
  void CountBricks();

  Textbox score_display_{ };
  Widget hearts_{ };
  Widget pause_screen_{ };
  bool paused_{ false };
  Ball ball_{ };
  Paddle paddle_{ };
  std::vector<Brick> bricks_{ };
  int milestone_{ 1 };
  int score_{ };
};

#endif  // SRC_STATE_PLAY_STATE_H_
