#include "src/ui/textbox.h"

#include "src/graphic/font.h"

Textbox::Textbox(Font *font, Texture *texture, Point anchor, Point offset,
                 SDL_Rect clip)
    : Widget{ texture, anchor, offset, clip }, font_{ font } {}

void Textbox::Update(const char *text) {
  get_texture()->LoadFromText(*font_, text);
  CheckClip();
}
