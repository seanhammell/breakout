#include "src/media/sound.h"

#include <stdio.h>

#include "SDL2/SDL_mixer.h"

Sound::~Sound() {
  Free();
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
