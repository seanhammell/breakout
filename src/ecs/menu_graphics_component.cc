#include "src/ecs/menu_graphics_component.h"

#include "src/gfx/sprite.h"
#include "src/gfx/texture.h"

void MenuGraphicsComponent::Update() {
  sprites_.Render(title_.x, title_.y, &title_.clip);
}
