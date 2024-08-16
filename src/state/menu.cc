#include "src/state/menu.h"

#include "SDL2/SDL.h"

#include "src/media/media.h"
#include "src/media/chunk.h"
#include "src/media/font.h"
#include "src/media/texture.h"
#include "src/state/level_select.h"
#include "src/state/state_machine.h"
#include "src/ui/textbox.h"
#include "src/ui/widget.h"

Menu::Menu()
    : title_{ &kMedia.title, { 1, 1 }, { 0, -kMedia.title.get_height() / 2 } },
      play_{ &kMedia.font, new Texture(), { 1, 1 }, { 0, 16 } },
      edit_{ &kMedia.font, new Texture(), { 1, 1 }, { 0, 24 } } {
  play_.Update("PLAY");
  edit_.Update("LEVEL EDITOR");
  play_.set_width(edit_.get_width());
  set_valid();
}

Menu::~Menu() {
  delete play_.get_texture();
  delete edit_.get_texture();
}

void Menu::HandleInput(SDL_Event input) {
  if (input.type == SDL_KEYDOWN && input.key.repeat == 0) {
    switch (input.key.keysym.sym) {
      case SDLK_UP:
        selection_ = kPlayState;
        break;
      case SDLK_DOWN:
        selection_ = kEditState;
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

StateMachine *Menu::Update() {
  switch (get_next_state()) {
    case kPlayState:
      return new LevelSelect(kPlayState);
    case kEditState:
      return new LevelSelect(kEditState);
    default:
      return NULL;
  }
}

void Menu::Render() {
  title_.Render();
  play_.Render();
  edit_.Render();
  switch (selection_) {
    case kPlayState:
      play_.ShowSelected();
      break;
    case kEditState:
      edit_.ShowSelected();
      break;
    default:
      break;
  }
}
