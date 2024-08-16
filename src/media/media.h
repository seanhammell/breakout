#ifndef SRC_MEDIA_MEDIA_H_
#define SRC_MEDIA_MEDIA_H_

#include "src/media/chunk.h"
#include "src/media/font.h"
#include "src/media/music.h"
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

  Music music;

  Chunk brick;
  Chunk paddle;
  Chunk wall;
  Chunk enter;
};

bool LoadMedia();
}  // namespace media

extern media::Media kMedia;

#endif  // SRC_MEDIA_MEDIA_H_
