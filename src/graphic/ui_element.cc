#include "src/graphic/ui_element.h"

#include "SDL2/SDL.h"

#include "src/graphic/renderer.h"
#include "src/graphic/texture.h"

UIElement::UIElement(Texture *texture, int x, int y, SDL_Rect clip)
    : texture_{ texture }, x_{ x }, y_{ y }, clip_{ clip } {
  // If the width of the clip is 0, assume the element is the entire texture.
  if (clip.w == 0) {
    clip_.w = texture->width();
    clip_.h = texture_->height();
  }
}

void UIElement::AlignCenterHorizontal() {
  x_ = (Renderer::kVirtualWidth / 2) - (texture_->width() / 2);
}

void UIElement::AlignRightHorizontal() {
  x_ = Renderer::kVirtualWidth - texture_->width() - 5;
}

void UIElement::Render() {
  texture_->Render(x_, y_, &clip_);
}
