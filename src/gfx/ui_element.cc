#include "src/gfx/ui_element.h"

#include "SDL2/SDL.h"

#include "src/gfx/texture.h"

UIElement::UIElement(Texture *texture, SDL_Rect clip, int x, int y)
  : texture_{ texture }, clip_{ clip }, x_{ x }, y_{ y } {}

void UIElement::Render() {
  texture_->Render(x_, y_, &clip_);
}
