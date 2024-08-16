#include "src/media/media.h"

#include "src/media/font.h"
#include "src/media/chunk.h"
#include "src/media/texture.h"

bool media::LoadMedia() {
  if (!kMedia.font.LoadFromFile("./res/font/font.ttf", 8)) { return false; }

  if (!kMedia.title.LoadFromFile("./res/image/title.png")) { return false; }
  if (!kMedia.end.LoadFromFile("./res/image/end.png")) { return false; }
  if (!kMedia.select.LoadFromFile("./res/image/select.png")) { return false; }
  if (!kMedia.blocks.LoadFromFile("./res/image/blocks.png")) { return false; }
  if (!kMedia.heart.LoadFromFile("./res/image/heart.png")) { return false; }
  if (!kMedia.pause.LoadFromFile("./res/image/pause.png")) { return false; }

  if (!kMedia.brick.LoadChunk("./res/sound/Brick.wav")) { return false; }
  if (!kMedia.paddle.LoadChunk("./res/sound/Paddle.wav")) { return false; }
  if (!kMedia.wall.LoadChunk("./res/sound/Wall.wav")) { return false; }
  if (!kMedia.enter.LoadChunk("./res/sound/Enter.wav")) { return false; }

  return true;
}
