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

  ~PlayState() = default;

  // Loads the Textures and Font needed by PlayState.
  static bool Load();

  // Responds to user input and updates the entities and score.
  StateMachine *Update(SDL_Event input) override;

  // Renders the entities and score.
  void Render() override;

 private:
  static inline Font font_{ };
  static inline Texture score_texture_{ };
  static inline Texture blocks_texture_{ };

  UIElement score_display_{ };
  Paddle paddle_{ };
};

#endif  // SRC_STATE_PLAY_STATE_H_
