#include "src/entity/graphics_component.h"

#include "SDL2/SDL.h"

#include "src/graphic/texture.h"

GraphicsComponent::GraphicsComponent(Texture *texture, SDL_Rect clip)
    : texture_{ texture }, clip_{ clip } {}


void GraphicsComponent::Render(int x, int y) {
  texture_->Render(x, y, &clip_);
}
