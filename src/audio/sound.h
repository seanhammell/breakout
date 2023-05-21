#ifndef SRC_AUDIO_SOUND_H_
#define SRC_AUDIO_SOUND_H_

#include "SDL2/SDL_mixer.h"

class Sound {
 public:
  Sound() = default;

  ~Sound();

  static bool LoadMediaSounds();

  bool LoadChunk(const char *path);

  void PlayChunk();

 private:
  void Free();

  Mix_Chunk *chunk_{ NULL };
};

#endif  // SRC_AUDIO_SOUND_H_
