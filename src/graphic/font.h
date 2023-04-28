#ifndef SRC_GRAPHIC_FONT_H_
#define SRC_GRAPHIC_FONT_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

class Font {
 public:
  Font() = default;

  ~Font();

  // Getters.
  TTF_Font *font() const;
  SDL_Color color() const;

  // Loads a font from the given path.
  bool LoadFromFile(const char *path, const int size);

 private:
  // Frees the resources associated with the font.
  void Free();

  TTF_Font *font_{ NULL };
  SDL_Color color_{ 0xEC, 0xEF, 0xF4, 0xFF };
};

#endif  // SRC_GRAPHIC_FONT_H_
