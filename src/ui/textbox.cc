#include "src/ui/textbox.h"

#include <cstdlib>

#include "src/media.h"
#include "src/graphic/font.h"
#include "src/ui/widget.h"

Textbox::Textbox(Font *font, Texture *texture, Point anchor, Point offset,
                 SDL_Rect clip)
    : Widget{ texture, anchor, offset, clip }, font_{ font } {}

void Textbox::AppendNumber(const char *s, int n) {
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%s%d", s, n);
  Update(buffer);
}

void Textbox::Update(const char *text) {
  Texture *texture = get_texture();
  texture->LoadFromText(*font_, text);
  set_clip({ 0, 0, texture->get_width(), texture->get_height() });
}

void Textbox::RenderSelected() {
  Widget selected{ &kMedia.blocks, get_anchor(), get_offset(), {24, 3, 2, 2} };
  Point adjusted_offset{ selected.get_offset() };
  adjusted_offset.x -= (get_width() / 2) + kPadding;
  selected.set_offset(adjusted_offset);
  selected.Render();
}
