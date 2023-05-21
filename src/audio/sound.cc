#include "src/audio/sound.h"

#include <stdio.h>

#include "SDL2/SDL_mixer.h"

#include "src/media.h"

Sound::~Sound() {
  Free();
}

bool Sound::LoadMediaSounds() {
  if (!kMedia.brick.LoadChunk("./res/sound/Brick.wav")) { return false; }
  if (!kMedia.paddle.LoadChunk("./res/sound/Paddle.wav")) { return false; }
  if (!kMedia.wall.LoadChunk("./res/sound/Wall.wav")) { return false; }
  if (!kMedia.enter.LoadChunk("./res/sound/Enter.wav")) { return false; }
  return true;
}

bool Sound::LoadChunk(const char *path) {
  chunk_ = Mix_LoadWAV(path);
  if (chunk_ == NULL) {
    fprintf(stderr, "Failed to load chunk: %s\n", Mix_GetError());
    return false;
  }

  return true;
}

void Sound::PlayChunk() {
  Mix_PlayChannel(-1, chunk_, 0);
}

void Sound::Free() {
  if (chunk_ != NULL) {
    Mix_FreeChunk(chunk_);
    chunk_ = NULL;
  }
}
