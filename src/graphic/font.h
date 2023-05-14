#ifndef SRC_GRAPHIC_FONT_H_
#define SRC_GRAPHIC_FONT_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

class Font {
 public:
  Font() = default;

  ~Font();

  static bool LoadMediaFonts();

  TTF_Font *get_font() const { return font_; }
  SDL_Color get_color() const { return color_; }

  // Loads the Font from the given path.
  bool LoadFromFile(const char *path, const int size);

 private:
  // Frees the current font_ if it exists.
  void Free();

  TTF_Font *font_{ NULL };
  SDL_Color color_{ 0xEC, 0xEF, 0xF4, 0xFF };
};

#endif  // SRC_GRAPHIC_FONT_H_
