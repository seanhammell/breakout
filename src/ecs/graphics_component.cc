#include "src/ecs/graphics_component.h"

#include "src/gfx/texture.h"

bool GraphicsComponent::LoadTextures() {
  if (!menu_texture_.LoadFromFile("./img/menu.png")) {
    return false;
  }

  return true;
}
