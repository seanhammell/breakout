#ifndef SRC_AUDIO_SOUND_H_
#define SRC_AUDIO_SOUND_H_

#include "SDL2/SDL_mixer.h"

class Sound {
 public:
  Sound() = default;

  ~Sound();

  static bool LoadMediaSounds();

  // Loads a chunk of sound from the file at the given path.
  bool LoadChunk(const char *path);

  // Plays the Sound's chunk.
  void PlayChunk();

 private:
  // Frees the current chunk_ if it exists.
  void Free();

  Mix_Chunk *chunk_{ NULL };
};

#endif  // SRC_AUDIO_SOUND_H_
