#include "src/ui/textbox.h"

#include <cstdlib>

#include "src/media.h"
#include "src/graphic/font.h"
#include "src/ui/widget.h"

Textbox::Textbox(Font *font, Texture *texture, Point anchor, Point offset,
                 SDL_Rect clip)
    : Widget{ texture, anchor, offset, clip }, font_{ font } {}

void Textbox::UpdateScore(int score) {
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "SCORE: %d", score);
  Update(buffer);
}

void Textbox::Update(const char *text) {
  Texture *texture = get_texture();
  texture->LoadFromText(*font_, text);
  set_clip({ 0, 0, texture->get_width(), texture->get_height() });
}

void Textbox::RenderSelected() {
  static Widget selected{ &kMedia.blocks, { 1, 1 }, { 0, 0 }, {24, 3, 2, 2} };
  int x{ get_x_pos() - (selected.get_width() + Widget::kPadding) };
  int y{ get_y_pos() + (get_height() / 2) - selected.get_height() };
  selected.Render(x, y);
}
