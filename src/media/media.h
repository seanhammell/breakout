#ifndef SRC_MEDIA_MEDIA_H_
#define SRC_MEDIA_MEDIA_H_

#include "src/media/sound.h"
#include "src/media/font.h"
#include "src/media/texture.h"

namespace media {
struct Media {
  Font font;

  Texture title;
  Texture end;
  Texture select;
  Texture blocks;
  Texture heart;
  Texture pause;

  Sound brick;
  Sound paddle;
  Sound wall;
  Sound enter;
};

bool LoadMedia();
}  // namespace media

extern media::Media kMedia;

#endif  // SRC_MEDIA_MEDIA_H_
