#include "src/state/over_state.h"

#include <stdio.h>

#include "SDL2/SDL.h"

#include "src/media.h"
#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/graphic/ui_element.h"
#include "src/state/menu_state.h"
#include "src/state/play_state.h"
#include "src/state/state_machine.h"

OverState::OverState(int score)
    : title_{ &kMedia.game_over, { 1, 1 },
              { 0, -kMedia.game_over.get_height() } },
      score_{ &kMedia.font, new Texture(), { 1, 1 }, { 0, 0 } },
      play_{ &kMedia.font, new Texture(), { 1, 1 }, { 0, 24 } },
      quit_ { &kMedia.font, new Texture(), { 1, 1 }, { 0, 32} } {
  score_.UpdateScore(score);
  play_.Update("PRESS SPACEBAR TO PLAY AGAIN");
  quit_.Update("PRESS Q TO QUIT");
  set_valid();
}

void OverState::HandleInput(SDL_Event input) {
  if (input.type == SDL_KEYDOWN && input.key.repeat == 0) {
    switch (input.key.keysym.sym) {
      case SDLK_SPACE:
        set_next_state(kPlayState);
        break;
      case SDLK_q:
        set_next_state(kMenuState);
        break;
      default:
        break;
    }
  }
}

StateMachine *OverState::Update() {
  switch (get_next_state()) {
    case kPlayState:
      return new PlayState();
    case kMenuState:
      return new MenuState();
    default:
      return NULL;
  }
}

void OverState::Render() {
  title_.Render();
  score_.Render();
  play_.Render();
  quit_.Render();
}
