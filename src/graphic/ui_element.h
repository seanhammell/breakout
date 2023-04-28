#ifndef SRC_GRAPHIC_UI_ELEMENT_H_
#define SRC_GRAPHIC_UI_ELEMENT_H_

#include "SDL2/SDL.h"

#include "src/graphic/texture.h"

class UIElement {
 public:
  UIElement() = default;
  UIElement(Texture *texture, int x, int y, SDL_Rect clip = { });

  ~UIElement() = default;

  // Aligns the UIElement horizontally.
  void AlignCenterHorizontal();
  void AlignRightHorizontal();

  // Renders the UIElement to the screen.
  void Render();

 private:
  Texture *texture_{ NULL };
  int x_{ 0 };
  int y_{ 0 };
  SDL_Rect clip_{ };
};

#endif  // SRC_GRAPHIC_UI_ELEMENT_H_
