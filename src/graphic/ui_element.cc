#include "src/graphic/ui_element.h"

#include "SDL2/SDL.h"

#include "src/graphic/renderer.h"
#include "src/graphic/texture.h"

UIElement::UIElement(Texture *texture, int x, int y, SDL_Rect clip)
    : texture_{ texture }, x_{ x }, y_{ y }, clip_{ clip } {
  UpdateClip();
}

void UIElement::AlignCenterHorizontal() {
  x_ = (Renderer::kVirtualWidth - texture_->get_width()) / 2;
}

void UIElement::AlignRightHorizontal() {
  x_ = Renderer::kVirtualWidth - texture_->get_width() - 5;
}

void UIElement::Render() {
  texture_->Render(x_, y_, &clip_);
}

void UIElement::UpdateClip(SDL_Rect clip) {
  // If the width of the clip is 0, assume the element is the entire texture.
  if (clip.w == 0) {
    clip_.w = texture_->get_width();
    clip_.h = texture_->get_height();
  }
}

void UIElement::UpdateNumeric(Font *font, Texture *texture, const char *s,
                              int n) {
  static constexpr int kBufferLength{ 20 };
  char buffer[kBufferLength];
  snprintf(buffer, kBufferLength - 1, "%s%d", s, n);
  texture->LoadFromText(*font, buffer);
  UpdateClip();
}
