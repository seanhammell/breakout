#include "src/state/menu_state.h"

#include "SDL2/SDL.h"

#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/graphic/ui_element.h"
#include "src/state/state_machine.h"
#include "src/state/play_state.h"

MenuState::MenuState() {
  title_ = UIElement(&title_texture_, 0, 80 - title_texture_.height());
  prompt_ = UIElement(&prompt_texture_, 0, 80 + prompt_texture_.height());
  title_.AlignCenterHorizontal();
  prompt_.AlignCenterHorizontal();
}

bool MenuState::Load() {
  if (!font_.LoadFromFile("./font/cs50.ttf", 8)) {
    return false;
  }

  if (!title_texture_.LoadFromFile("./img/menu.png")) {
    return false;
  }

  if (!prompt_texture_.LoadFromText(font_, "PRESS SPACEBAR TO PLAY")) {
    return false;
  }

  return true;
}

StateMachine *MenuState::HandleInput(SDL_Event input) {
  if (input.type == SDL_KEYDOWN) {
    if (input.key.keysym.sym == SDLK_SPACE) {
      return new PlayState();
    }
  }

  return NULL;
}

void MenuState::Render() {
  title_.Render();
  prompt_.Render();
}
