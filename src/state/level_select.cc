#include "src/state/level_select.h"

#include <stdio.h>

#include <cstdlib>

#include "src/media/media.h"
#include "src/media/chunk.h"
#include "src/media/texture.h"
#include "src/state/edit.h"
#include "src/state/play.h"

LevelSelect::LevelSelect(StateMachine::States next)
    : title_{ &kMedia.select, { 1, 1 }, { 0, -kMedia.select.get_height() } },
      mode_{ &kMedia.font, new Texture(), { 0, 0 }, { 0, 0 } },
      levels_{ &kMedia.font, new Texture(), { 1, 1 }, { 0, 0 } },
      next_{ next } {
  switch (next_) {
    case kPlayState:
      mode_.Update("PLAY");
      break;
    case kEditState:
      mode_.Update("EDIT");
      break;
    default:
      break;
  }
  levels_.AppendNumber("LEVEL: ", 1);
  set_valid();
}

LevelSelect::~LevelSelect() {
  delete mode_.get_texture();
  delete levels_.get_texture();
}

void LevelSelect::HandleInput(SDL_Event input) {
  if (input.type == SDL_KEYDOWN && input.key.repeat == 0) {
    switch (input.key.keysym.sym) {
      case SDLK_UP:
        selection_ -= selection_ > 1 ? 1 : 0;
        break;
      case SDLK_DOWN:
        selection_ += selection_ < 4 ? 1 : 0;
        break;
      case SDLK_RETURN:
        kMedia.enter.PlayChunk();
        trigger_ = true;
        break;
      default:
        break;
    }
  }
}

StateMachine *LevelSelect::Update() {
  if (trigger_) {
    // It is important that the buffer is static because Edit needs
    // the name of the file when it is time to save.
    static char buffer[25];
    snprintf(buffer, sizeof(buffer), "./res/level/level_0%d.txt", selection_);
    switch (next_) {
      case kPlayState:
        return new Play(buffer);
      case kEditState:
        return new Edit(buffer);
      default:
        return NULL;
    }
  }

  return NULL;
}

void LevelSelect::Render() {
  title_.Render();
  mode_.Render();
  for (int i{ 1 }; i < 5; ++i) {
    levels_.AppendNumber("LEVEL ", i, false);
    levels_.set_offset({ 0, (levels_.get_height() + Widget::kPadding) * i });
    levels_.Render();
    if (i == selection_) {
      levels_.ShowSelected();
    }
  }
  levels_.set_offset({ 0, 0 });
}
