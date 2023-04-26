#ifndef SRC_ECS_GFX_GRAPHICS_COMPONENT_H_
#define SRC_ECS_GFX_GRAPHICS_COMPONENT_H_

#include "src/gfx/texture.h"

class GraphicsComponent {
 public:
  virtual ~GraphicsComponent() {}

  // Loads all the game textures at once.
  static bool LoadTextures();

  static Texture GetMenuTexture() { return menu_texture_; }

  virtual void Update() = 0;

 private:
  static inline Texture menu_texture_;
};

#endif  // SRC_ECS_GFX_GRAPHICS_COMPONENT_H_
