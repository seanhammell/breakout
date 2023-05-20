#ifndef SRC_MEDIA_H_
#define SRC_MEDIA_H_

#include "src/graphic/font.h"
#include "src/graphic/texture.h"

struct Media {
  Font font;

  Texture title;
  Texture end;
  Texture select;
  Texture blocks;
  Texture heart;
  Texture pause;
};

extern Media kMedia;

#endif  // SRC_MEDIA_H_
