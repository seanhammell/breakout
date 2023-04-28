#ifndef SRC_GRAPHIC_UI_ELEMENT_H_
#define SRC_GRAPHIC_UI_ELEMENT_H_

#include "SDL2/SDL.h"

#include "src/graphic/texture.h"

class UIElement {
 public:
  UIElement() = default;
  UIElement(Texture *texture, int x, int y, SDL_Rect clip = { });
  ~UIElement() {}

  // Aligns the element horizontally.
  void AlignCenterHorizontal();
  void AlignRightHorizontal();

  // Renders the element to the screen.
  void Render();

 private:
  Texture *texture_{ NULL };
  SDL_Rect clip_{ };
  int x_{ 0 };
  int y_{ 0 };
};

#endif  // SRC_GRAPHIC_UI_ELEMENT_H_
