#include "src/ecs/graphics_component.h"

#include <vector>

#include "src/fsm/menu_state.h"
#include "src/gfx/texture.h"

static Texture kMenuTexture;

GraphicsComponent::GraphicsComponent(TextureSelect selection) {
  switch (selection) {
    case kMenu:
      texture_ = &kMenuTexture;
      sprites_.clear();
      sprites_.push_back({ {0, 0, 142, 16}, 25, 40 });
      break;
    default:
      break;
  }
}

bool GraphicsComponent::LoadTextures() {
  if (!kMenuTexture.LoadFromFile("./img/menu.png")) {
    return false;
  }

  return true;
}

void GraphicsComponent::Update() {
  for (Sprite sprite : sprites_) {
    texture_->Render(sprite.x, sprite.y, &sprite.clip);
  }
}
