#include "src/state/menu.h"

#include "SDL2/SDL.h"

#include "src/media.h"
#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/state/play.h"
#include "src/state/state_machine.h"
#include "src/ui/textbox.h"
#include "src/ui/widget.h"

Menu::Menu()
    : title_{ &kMedia.title, { 1, 1 }, { 0, -kMedia.title.get_height() / 2 } },
      play_{ &kMedia.font, new Texture(), { 1, 1 }, { 0, 16 } } {
  play_.Update("PRESS SPACEBAR TO PLAY");
  set_valid();
}

Menu::~Menu() {
  delete play_.get_texture();
}

void Menu::HandleInput(SDL_Event input) {
  if (input.type == SDL_KEYDOWN && input.key.repeat == 0) {
    switch (input.key.keysym.sym) {
      case SDLK_SPACE:
        set_next_state(kPlayState);
        break;
      default:
        break;
    }
  }
}

StateMachine *Menu::Update() {
  switch (get_next_state()) {
    case kPlayState:
      return new Play();
    default:
      return NULL;
  }
}

void Menu::Render() {
  title_.Render();
  play_.Render();
}
