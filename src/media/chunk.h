#ifndef SRC_MEDIA_CHUNK_H_
#define SRC_MEDIA_CHUNK_H_

#include "SDL2/SDL_mixer.h"

class Chunk {
 public:
  Chunk() = default;

  ~Chunk();

  // Loads a chunk of sound from the file at the given path.
  bool LoadChunk(const char *path);

  // Plays the Chunk's chunk.
  void PlayChunk();

 private:
  // Frees the current chunk_ if it exists.
  void Free();

  Mix_Chunk *chunk_{NULL};
};

#endif  // SRC_MEDIA_CHUNK_H_
