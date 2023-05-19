#include "src/state/edit.h"

#include "SDL2/SDL.h"

#include "src/game.h"
#include "src/entity/brick.h"
#include "src/graphic/renderer.h"

Edit::Edit(const char *level) {
  if (Brick::Load(&bricks_, level)) {
    set_valid();
  }
}

void Edit::Render() {
  SDL_SetRenderDrawColor(kGame.renderer.get_renderer(), 0xEC, 0xEF, 0xF4, 0xFF);
  SDL_Rect zone{ 1, 19, Renderer::kVirtualWidth - 1,
                 Brick::kBrickHeight * 8 + 1 };
  SDL_RenderDrawRect(kGame.renderer.get_renderer(), &zone);

  for (auto brick : bricks_) {
    if (brick.get_type() != Brick::kNoType) {
      brick.Render();
    }
  }
}
