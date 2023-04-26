#ifndef SRC_ECS_GFX_MENU_GRAPHICS_COMPONENT_H_
#define SRC_ECS_GFX_MENU_GRAPHICS_COMPONENT_H_

#include "SDL2/SDL.h"

#include "src/ecs/gfx/graphics_component.h"
#include "src/gfx/texture.h"

class MenuGraphicsComponent : public GraphicsComponent {
 public:
  ~MenuGraphicsComponent() {}

  void Update() override;

 private:
  Texture sprites_{ GraphicsComponent::GetMenuTexture() };
  SDL_Rect title_clip_{ 0, 0, 142, 16 };
};

#endif  // SRC_ECS_GFX_MENU_GRAPHICS_COMPONENT_H_
