#ifndef SRC_ENTITY_GRAPHICS_COMPONENT_H_
#define SRC_ENTITY_GRAPHICS_COMPONENT_H_

#include "SDL2/SDL.h"

#include "src/graphic/texture.h"

class GraphicsComponent {
 public:
  GraphicsComponent() = default;
  GraphicsComponent(Texture *texture_, SDL_Rect clip);

  ~GraphicsComponent() = default;

  // Renders the GraphicsComponent at the specified coordinates.
  void Render(int x, int y);

 private:
  Texture *texture_{ NULL };
  SDL_Rect clip_{ };
};

#endif  // SRC_ENTITY_GRAPHICS_COMPONENT_H_
