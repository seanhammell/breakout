#include "src/ecs/gfx/menu_graphics_component.h"

#include "src/gfx/texture.h"

void MenuGraphicsComponent::Update() {
  sprites_.Render(0, 0, &title_clip_);
}
