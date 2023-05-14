#include "src/state/menu_state.h"

#include "SDL2/SDL.h"

#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/graphic/ui_element.h"
#include "src/state/play_state.h"
#include "src/state/select_state.h"
#include "src/state/state_machine.h"

MenuState::MenuState()
    : title_{ &title_texture_, {1, 1}, {0, -title_texture_.get_height() / 2} },
      prompt_{ &prompt_texture_, 0, 80 + prompt_texture_.get_height() } {
  valid();
  prompt_.AlignCenterHorizontal();
}

bool MenuState::Load() {
  if (!font_.LoadFromFile("./font/cs50.ttf", 8)) { return false; }
  if (!title_texture_.LoadFromFile("./img/menu.png")) { return false; }
  if (!prompt_texture_.LoadFromText(font_, "PRESS SPACEBAR TO PLAY")) {
    return false;
  }

  return true;
}

void MenuState::HandleInput(SDL_Event input) {
  if (input.type == SDL_KEYDOWN && input.key.repeat == 0) {
    switch (input.key.keysym.sym) {
      case SDLK_SPACE:
        next_state(kPlayState);
        break;
      case SDLK_l:
        next_state(kSelectState);
        break;
      default:
        break;
    }
  }
}

StateMachine *MenuState::Update() {
  switch (get_next_state()) {
    case kPlayState:
      return new PlayState();
    case kSelectState:
      return new SelectState();
    default:
      return NULL;
  }
}

void MenuState::Render() {
  title_.Render();
  prompt_.Render();
}
