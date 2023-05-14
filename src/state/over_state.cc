#include "src/state/over_state.h"

#include "SDL2/SDL.h"

#include "src/media.h"
#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/graphic/ui_element.h"
#include "src/state/menu_state.h"
#include "src/state/play_state.h"
#include "src/state/state_machine.h"

OverState::OverState(int score)
    : title_{ &kMedia.game_over, 0, 70 - kMedia.game_over.get_height() },
      score_display_{ &score_texture_, 0, 90 - score_texture_.get_height() },
      play_prompt_{ &play_texture_, 0, 130 - play_texture_.get_height() },
      quit_prompt_ { &quit_texture_, 0, 140 - quit_texture_.get_height() } {
  valid();
  title_.AlignCenterHorizontal();
  score_display_.UpdateNumeric(&kMedia.regular, &score_texture_, "SCORE: ",
                               score);
  score_display_.UpdateClip();
  score_display_.AlignCenterHorizontal();
  play_prompt_.AlignCenterHorizontal();
  quit_prompt_.AlignCenterHorizontal();
}

bool OverState::Load() {
  if (!score_texture_.LoadFromText(kMedia.large, "SCORE: ")) { return false; }
  if (!play_texture_.LoadFromText(kMedia.regular,
                                  "PRESS SPACEBAR TO PLAY AGAIN")) {
    return false;
  }
  if (!quit_texture_.LoadFromText(kMedia.regular,
                                  "PRESS Q FOR THE TITLE SCREEN")) {
    return false;
  }

  return true;
}

void OverState::HandleInput(SDL_Event input) {
  if (input.type == SDL_KEYDOWN && input.key.repeat == 0) {
    switch (input.key.keysym.sym) {
      case SDLK_SPACE:
        next_state(kPlayState);
        break;
      case SDLK_q:
        next_state(kMenuState);
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
  score_display_.Render();
  play_prompt_.Render();
  quit_prompt_.Render();
}
