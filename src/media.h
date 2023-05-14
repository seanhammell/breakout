#ifndef SRC_MEDIA_H_
#define SRC_MEDIA_H_

#include "src/graphic/font.h"
#include "src/graphic/texture.h"

struct Media {
  Font regular_font;
  Font large_font;

  Texture title_texture;
  Texture game_over_texture;
  Texture blocks_texture;
  Texture heart_texture;
  Texture pause_texture;
};

extern Media kMedia;

#endif  // SRC_MEDIA_H_
