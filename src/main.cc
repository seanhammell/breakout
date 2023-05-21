#include <cstdlib>
#include <ctime>

#include "src/game.h"
#include "src/media.h"
#include "src/audio/sound.h"
#include "src/graphic/texture.h"
#include "src/graphic/window.h"

// Global game state.
Game kGame;

// Global media.
Media kMedia;

int main() {
  std::srand(std::time(nullptr));

  if (!Texture::LoadMediaTextures() ||
      !Font::LoadMediaFonts() ||
      !Sound::LoadMediaSounds()) {
    return 0;
  }

  kGame.window.Loop();

  return 0;
}
