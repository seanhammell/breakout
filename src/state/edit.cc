#include "src/state/edit.h"

#include <algorithm>

#include "SDL2/SDL.h"

#include "src/game.h"
#include "src/media.h"
#include "src/entity/brick.h"
#include "src/graphic/renderer.h"

Edit::Edit(const char *level)
    : hover_{ 0, 0, Brick::kYellow, &kMedia.blocks } {
  if (Brick::Load(&bricks_, level)) {
    set_valid();
  }
}

void Edit::HandleInput(SDL_Event input) {
  int x{ };
  int y{ };

  SDL_GetMouseState(&x, &y);

  x /= 4;
  y /= 4;

  int index{ };
  switch (input.type) {
    case SDL_MOUSEMOTION:

      if (x <= kZone.x || x >= kZone.x + kZone.w ||
          y <= kZone.y || y >= kZone.y + kZone.h) {
        in_zone_ = false;
        return;
      }

      in_zone_ = true;
      hover_.set_x_pos(x - (x % Brick::kBrickWidth) + 1);
      hover_.set_y_pos(y - (y % Brick::kBrickHeight));
      break;
    case SDL_MOUSEWHEEL:
      if (input.wheel.y > 0) {
        hover_.set_type(std::min(hover_.get_type() + 1, +Brick::kRed));
      } else if (input.wheel.y < 0) {
        hover_.set_type(std::max(hover_.get_type() - 1, +Brick::kYellow));
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      if (input.button.button == SDL_BUTTON_LEFT) {
        index = (x / Brick::kBrickWidth) +
                (((y - 20) / Brick::kBrickHeight) * 22);
        bricks_[index] = hover_;
        break;
      }
    default:
      break;
  }
}

void Edit::Render() {
  SDL_SetRenderDrawColor(kGame.renderer.get_renderer(), 0xEC, 0xEF, 0xF4, 0xFF);
  SDL_RenderDrawRect(kGame.renderer.get_renderer(), &kZone);

  for (auto brick : bricks_) {
    if (brick.get_type() != Brick::kNoType) {
      brick.Render();
    }
  }

  if (in_zone_) {
    hover_.Render();
  }
}
