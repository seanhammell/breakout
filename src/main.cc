#include <cstdlib>
#include <ctime>

#include "src/game.h"

// Global game state.
Game kGame;

int main() {
  std::srand(std::time(nullptr));
  kGame.window.Loop();

  return 0;
}
