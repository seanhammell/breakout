#include "src/state/select_state.h"

#include "src/media.h"

SelectState::SelectState()
    : prompt_{ &prompt_texture_, 0, 50 - prompt_texture_.get_height() } {
  valid();
  prompt_.AlignCenterHorizontal();
}

bool SelectState::Load() {
  if (!prompt_texture_.LoadFromText(kMedia.regular, "SELECT LEVEL")) {
    return false;
  }
  return true;
}

void SelectState::Render() {
  prompt_.Render();
}
