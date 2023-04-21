#ifndef SRC_FONT_H_
#define SRC_FONT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Font {
 public:
  Font() {}
  ~Font() { Free(); }

  TTF_Font *GetFont() const { return font_; }
  SDL_Color GetColor() const { return color_; }

  bool LoadFromFile(const char *path, const int size);

 private:
  void Free();

  TTF_Font *font_{ NULL };
  SDL_Color color_{ 0xEC, 0xEF, 0xF4, 0xFF };
};

#endif  // SRC_FONT_H_
