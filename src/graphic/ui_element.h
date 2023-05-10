#ifndef SRC_GRAPHIC_UI_ELEMENT_H_
#define SRC_GRAPHIC_UI_ELEMENT_H_

#include "SDL2/SDL.h"

#include "src/graphic/font.h"
#include "src/graphic/texture.h"

class UIElement {
 public:
  UIElement() = default;
  UIElement(Texture *texture, int x, int y, SDL_Rect clip = { });

  ~UIElement() = default;

  // Aligns the UIElement horizontally.
  void AlignCenterHorizontal();
  void AlignRightHorizontal();

  // Updates the texture clip to account for changing UI Elements.
  void UpdateClip(SDL_Rect clip = { });

  // Updates the texture by appending the number n to the string s.
  void UpdateNumeric(Font *font, Texture *texture, const char *s, int n);

  // Renders the UIElement to the screen.
  void Render();

 private:
  Texture *texture_{ NULL };
  int x_{ 0 };
  int y_{ 0 };
  SDL_Rect clip_{ };
};

#endif  // SRC_GRAPHIC_UI_ELEMENT_H_
