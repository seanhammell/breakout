#include "src/state/select_state.h"

SelectState::SelectState()
    : prompt_{ &prompt_texture_, 0, 50 - prompt_texture_.get_height() } {
  valid();
  prompt_.AlignCenterHorizontal();
}

bool SelectState::Load() {
  if (!font_.LoadFromFile("./font/cs50.ttf", 8)) { return false; }
  if (!prompt_texture_.LoadFromText(font_, "SELECT LEVEL")) { return false; }
  return true;
}

void SelectState::Render() {
  prompt_.Render();
}
