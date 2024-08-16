#include <cstdlib>
#include <ctime>

#include "src/game.h"
#include "src/graphic/window.h"
#include "src/media/media.h"

// Global game state.
Game kGame;

// Global media.
media::Media kMedia;

int main() {
  std::srand(std::time(nullptr));

  if (!media::LoadMedia()) {
    return 0;
  }

  kGame.window.Loop();

  return 0;
}
