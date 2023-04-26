#ifndef SRC_ECS_GRAPHICS_COMPONENT_H_
#define SRC_ECS_GRAPHICS_COMPONENT_H_

class GraphicsComponent;

#include <vector>

#include "src/fsm/menu_state.h"
#include "src/gfx/sprite.h"
#include "src/gfx/texture.h"

class GraphicsComponent {
 public:
  enum TextureSelect {
    kMenu,
  };

  explicit GraphicsComponent(TextureSelect selection);
  ~GraphicsComponent() {}

  // Loads all of the games textures. This should be called before entering
  // the game loop to ensure all textures load successfully.
  static bool LoadTextures();

  // Performs any updates to the graphics since the last call and renders the
  // sprites to the screen.
  void Update();

 private:
  Texture *texture_{ NULL };
  std::vector<Sprite> sprites_;
};

#endif  // SRC_ECS_GRAPHICS_COMPONENT_H_
