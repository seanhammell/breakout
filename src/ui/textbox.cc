#include "src/ui/textbox.h"

#include <stdio.h>

#include <cstdlib>

#include "src/media/media.h"
#include "src/media/font.h"
#include "src/ui/widget.h"

Textbox::Textbox(Font *font, Texture *texture, Point anchor, Point offset,
                 SDL_Rect clip)
    : Widget{ texture, anchor, offset, clip }, font_{ font } {}

void Textbox::AppendNumber(const char *s, int n, bool fit) {
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%s%d", s, n);
  Update(buffer, fit);
}

void Textbox::ShowSelected() {
  Widget selected{ &kMedia.blocks, get_anchor(), get_offset(), {24, 3, 2, 2} };
  Point adjusted_offset{ selected.get_offset() };
  adjusted_offset.x -= (get_width() / 2) + selected.get_width() + kPadding;
  adjusted_offset.y -= selected.get_height() / 2;
  selected.set_offset(adjusted_offset);
  selected.Render();
}

void Textbox::Update(const char *text, bool fit) {
  Texture *texture = get_texture();
  texture->LoadFromText(*font_, text);
  set_clip({ 0, 0, texture->get_width(), texture->get_height() });
  if (fit) {
    FitToText();
  }
}

void Textbox::FitToText() {
  set_width(get_clip_width());
  set_height(get_clip_height());
}
