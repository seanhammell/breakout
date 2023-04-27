#include "src/graphic/ui_element.h"

#include "SDL2/SDL.h"

#include "src/graphic/renderer.h"
#include "src/graphic/texture.h"

UIElement::UIElement(Texture *texture, int x, int y)
    : texture_{ texture }, x_{ x }, y_{ y } {
  clip_.x = 0;
  clip_.y = 0;
  clip_.w = texture_->width();
  clip_.h = texture_->height();
}

UIElement::UIElement(Texture *texture, SDL_Rect clip, int x, int y)
    : texture_{ texture }, clip_{ clip }, x_{ x }, y_{ y } {}

void UIElement::CenterHorizontal() {
  x_ = (Renderer::kVirtualWidth / 2) - (texture_->width() / 2);
}

void UIElement::Render() {
  texture_->Render(x_, y_, &clip_);
}
