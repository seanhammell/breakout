#include "src/state/menu_state.h"

#include "SDL2/SDL.h"

#include "src/media.h"
#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/state/play_state.h"
#include "src/state/select_state.h"
#include "src/state/state_machine.h"
#include "src/ui/widget.h"
#include "src/ui/textbox.h"

MenuState::MenuState()
    : title_{ &kMedia.title, { 1, 1 }, { 0, -kMedia.title.get_height() / 2 } },
      prompt_{ &kMedia.regular, new Texture(), { 1, 1 },
               { 0, kMedia.regular.get_size() * 2 } } {
  Texture *prompt{ new Texture() };
  prompt_.set_texture(prompt);
}

MenuState::~MenuState() {
  delete prompt_.get_texture();
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
  prompt_.Update("PRESS SPACEBAR TO PLAY");
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
