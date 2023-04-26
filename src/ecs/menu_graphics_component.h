#ifndef SRC_ECS_MENU_GRAPHICS_COMPONENT_H_
#define SRC_ECS_MENU_GRAPHICS_COMPONENT_H_

#include "SDL2/SDL.h"

#include "src/ecs/graphics_component.h"
#include "src/gfx/sprite.h"
#include "src/gfx/texture.h"

class MenuGraphicsComponent : public GraphicsComponent {
 public:
  ~MenuGraphicsComponent() {}

  // Updates the menu graphics and renders them to the screen.
  void Update() override;

 private:
  Texture sprites_{ GraphicsComponent::GetMenuTexture() };
  Sprite title_{ {0, 0, 142, 16}, 25, 40 };
};

#endif  // SRC_ECS_MENU_GRAPHICS_COMPONENT_H_
