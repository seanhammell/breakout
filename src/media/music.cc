#include "src/media/music.h"

#include <stdio.h>

#include "SDL2/SDL_mixer.h"

Music::~Music() { Free(); }

bool Music::LoadMusic(const char *path) {
  music_ = Mix_LoadMUS(path);
  if (music_ == NULL) {
    fprintf(stderr, "Failed to load music: %s\n", Mix_GetError());
    return false;
  }

  return true;
}

void Music::ToggleMusic() {
  if (!Mix_PlayingMusic()) {
    Mix_PlayMusic(music_, -1);
  } else {
    if (Mix_PausedMusic()) {
      Mix_ResumeMusic();
    } else {
      Mix_PauseMusic();
    }
  }
}

void Music::Free() {
  if (music_ != NULL) {
    Mix_HaltMusic();
    Mix_FreeMusic(music_);
    music_ = NULL;
  }
}
