#ifndef SRC_AUDIO_MUSIC_H_
#define SRC_AUDIO_MUSIC_H_

#include "SDL2/SDL_mixer.h"

class Music {
 public:
  Music() = default;

  ~Music();

  // Loads music from the file at the given path.
  bool LoadMusic(const char *path);

  // Toggles playing/pausing the music.
  void ToggleMusic();

 private:
  // Frees the current music_ if it exists.
  void Free();

  Mix_Music *music_{ NULL };
};

#endif  // SRC_AUDIO_MUSIC_H_
