#include "src/state/end.h"

#include <stdio.h>

#include "SDL2/SDL.h"

#include "src/media.h"
#include "src/audio/sound.h"
#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/state/menu.h"
#include "src/state/level_select.h"
#include "src/state/state_machine.h"

End::End(int score, bool victory)
    : title_{ &kMedia.end,
              { 1, 1 },
              { 0, -kMedia.end.get_height() },
              { 0, victory ? 16 : 0, 144, 16} },
      score_{ &kMedia.font, new Texture(), { 1, 1 }, { 0, 0 } },
      play_{ &kMedia.font, new Texture(), { 1, 1 }, { 0, 24 } },
      menu_ { &kMedia.font, new Texture(), { 1, 1 }, { 0, 32} } {
  score_.AppendNumber("SCORE: ", score);
  play_.Update("PLAY AGAIN");
  menu_.Update("MAIN MENU");
  menu_.set_width(play_.get_width());
  set_valid();
}

End::~End() {
  delete score_.get_texture();
  delete play_.get_texture();
  delete menu_.get_texture();
}

void End::HandleInput(SDL_Event input) {
  if (input.type == SDL_KEYDOWN && input.key.repeat == 0) {
    switch (input.key.keysym.sym) {
      case SDLK_UP:
        selection_ = kPlayState;
        break;
      case SDLK_DOWN:
        selection_ = kMenuState;
        break;
      case SDLK_RETURN:
        kMedia.enter.PlayChunk();
        set_next_state(selection_);
        break;
      default:
        break;
    }
  }
}

StateMachine *End::Update() {
  switch (get_next_state()) {
    case kPlayState:
      return new LevelSelect(kPlayState);
    case kMenuState:
      return new Menu();
    default:
      return NULL;
  }
}

void End::Render() {
  title_.Render();
  score_.Render();
  play_.Render();
  menu_.Render();
  switch (selection_) {
    case kPlayState:
      play_.ShowSelected();
      break;
    case kMenuState:
      menu_.ShowSelected();
      break;
    default:
      break;
  }
}
