#include "src/media/chunk.h"

#include <stdio.h>

#include "SDL2/SDL_mixer.h"

Chunk::~Chunk() { Free(); }

bool Chunk::LoadChunk(const char *path) {
  chunk_ = Mix_LoadWAV(path);
  if (chunk_ == NULL) {
    fprintf(stderr, "Failed to load chunk: %s\n", Mix_GetError());
    return false;
  }

  return true;
}

void Chunk::PlayChunk() { Mix_PlayChannel(-1, chunk_, 0); }

void Chunk::Free() {
  if (chunk_ != NULL) {
    Mix_FreeChunk(chunk_);
    chunk_ = NULL;
  }
}
