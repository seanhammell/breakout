#include "src/state/over_state.h"

#include "SDL2/SDL.h"

#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/graphic/ui_element.h"
#include "src/state/state_machine.h"
#include "src/state/menu_state.h"
#include "src/state/play_state.h"

OverState::OverState(int score)
    : title_{ &title_texture_, 0, 70 - title_texture_.get_height() },
      score_display_{ &score_texture_, 0, 90 - score_texture_.get_height() },
      play_prompt_{ &play_texture_, 0, 130 - play_texture_.get_height() },
      quit_prompt_ { &quit_texture_, 0, 140 - quit_texture_.get_height() } {
  valid();
  title_.AlignCenterHorizontal();
  score_display_.UpdateNumeric(&font_, &score_texture_, "SCORE: ", score);
  score_display_.UpdateClip();
  score_display_.AlignCenterHorizontal();
  play_prompt_.AlignCenterHorizontal();
  quit_prompt_.AlignCenterHorizontal();
}

bool OverState::Load() {
  if (!font_.LoadFromFile("./font/cs50.ttf", 8)) { return false; }
  if (!title_texture_.LoadFromFile("./img/game_over.png")) { return false; }
  if (!score_texture_.LoadFromText(font_, "SCORE: ")) { return false; }
  if (!play_texture_.LoadFromText(font_, "PRESS SPACEBAR TO PLAY AGAIN")) {
    return false;
  }
  if (!quit_texture_.LoadFromText(font_, "PRESS Q FOR THE TITLE SCREEN")) {
    return false;
  }

  return true;
}

void OverState::HandleInput(SDL_Event input) {
  if (input.type == SDL_KEYDOWN && input.key.repeat == 0) {
    if (input.key.keysym.sym == SDLK_SPACE) {
      next_state(kPlayState);
    } else if (input.key.keysym.sym == SDLK_q) {
      next_state(kMenuState);
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
