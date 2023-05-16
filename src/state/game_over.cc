#include "src/state/game_over.h"

#include <stdio.h>

#include "SDL2/SDL.h"

#include "src/media.h"
#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/state/menu.h"
#include "src/state/play.h"
#include "src/state/state_machine.h"

GameOver::GameOver(int score)
    : title_{ &kMedia.game_over, { 1, 1 },
              { 0, -kMedia.game_over.get_height() } },
      score_{ &kMedia.font, new Texture(), { 1, 1 }, { 0, 0 } },
      play_{ &kMedia.font, new Texture(), { 1, 1 }, { 0, 24 } },
      quit_ { &kMedia.font, new Texture(), { 1, 1 }, { 0, 32} } {
  score_.UpdateScore(score);
  play_.Update("PRESS SPACEBAR TO PLAY AGAIN");
  quit_.Update("PRESS Q TO QUIT");
  set_valid();
}

void GameOver::HandleInput(SDL_Event input) {
  if (input.type == SDL_KEYDOWN && input.key.repeat == 0) {
    switch (input.key.keysym.sym) {
      case SDLK_SPACE:
        set_next_state(kPlayState);
        break;
      case SDLK_q:
        set_next_state(kMenuState);
        break;
      default:
        break;
    }
  }
}

StateMachine *GameOver::Update() {
  switch (get_next_state()) {
    case kPlayState:
      return new Play();
    case kMenuState:
      return new Menu();
    default:
      return NULL;
  }
}

void GameOver::Render() {
  title_.Render();
  score_.Render();
  play_.Render();
  quit_.Render();
}
