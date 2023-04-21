#ifndef SRC_FONT_H_
#define SRC_FONT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Font {
 public:
  Font() {}
  ~Font() { Free(); }

  bool LoadFromFile(const char *path, const int size);

 private:
  void Free();

  TTF_Font *font_{ NULL };
  //SDL_Color color_{ 0x00, 0x00, 0x00, 0xFF };
};

#endif  // SRC_FONT_H_
