#include "src/ui/textbox.h"

#include <cstdlib>

#include "src/graphic/font.h"

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
