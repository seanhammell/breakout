#ifndef SRC_STATE_PLAY_STATE_H_
#define SRC_STATE_PLAY_STATE_H_

#include <cstddef>
#include <vector>

#include "SDL2/SDL.h"

#include "src/entity/ball.h"
#include "src/entity/brick.h"
#include "src/entity/paddle.h"
#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/graphic/ui_element.h"
#include "src/state/state_machine.h"

class PlayState : public StateMachine {
 public:
  PlayState();

  ~PlayState() = default;

  // Loads the Textures and Font needed by PlayState.
  static bool Load();

  // Responds to user input during the game.
  void HandleInput(SDL_Event input) override;

  // Updates the entities and score.
  StateMachine *Update() override;

  // Renders the game objects and score to the screen.
  void Render() override;

 private:
  // Loads the starting Bricks for a given level.
  bool LoadLevel();

  void UpdateScore();

  static inline Font font_{ };
  static inline Texture score_texture_{ };
  static inline Texture blocks_texture_{ };
  static inline Texture heart_texture_{ };
  static inline Texture pause_texture_{ };

  UIElement score_display_{ };
  UIElement pause_screen_{ };
  std::vector<UIElement> heart_icons_{ };
  bool paused_{ false };
  Ball ball_{ };
  Paddle paddle_{ };
  std::vector<Brick> bricks_{ };
  size_t n_bricks_hit_{ };
  int milestone_{ 1 };
  int score_{ };
};

#endif  // SRC_STATE_PLAY_STATE_H_
