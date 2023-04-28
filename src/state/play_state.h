#ifndef SRC_STATE_PLAY_STATE_H_
#define SRC_STATE_PLAY_STATE_H_

#include "SDL2/SDL.h"

#include "src/entity/paddle.h"
#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/graphic/ui_element.h"
#include "src/state/state_machine.h"

class PlayState : public StateMachine {
 public:
  PlayState();
  ~PlayState() {}

  // Loads all resources nedded for gameplay.
  static bool Load();

  // Handles user input while playing the game.
  StateMachine *HandleInput(SDL_Event) { return NULL; }

  // Updates the score and game entities with any changes since the last frame.
  void Update() {}

  // Render the game to the screen.
  void Render();

 private:
  static inline Font font_{ };
  static inline Texture score_texture_{ };
  static inline Texture blocks_texture_{ };
  UIElement score_display_{ };
  Paddle paddle_{ };
};

#endif  // SRC_STATE_PLAY_STATE_H_
