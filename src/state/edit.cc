#include "src/state/edit.h"

#include <algorithm>
#include <fstream>

#include "SDL2/SDL.h"
#include "src/entity/brick.h"
#include "src/game.h"
#include "src/graphic/renderer.h"
#include "src/media/chunk.h"
#include "src/media/media.h"
#include "src/state/menu.h"
#include "src/state/state_machine.h"

Edit::Edit(const char *level)
    : file_{level},
      controls_{&kMedia.font, new Texture(), {0, 2}, {0, 0}},
      hover_{0, 0, Brick::kYellow, &kMedia.blocks} {
  controls_.Update(
      "LEFT-CLICK:  PLACE BLOCK\n"
      "RIGHT-CLICK: REMOVE BLOCK\n"
      "SCROLL:      CHANGE BLOCK\n"
      "RETURN:      SAVE AND EXIT");
  if (Brick::Load(&bricks_, level)) {
    set_valid();
  }
}

Edit::~Edit() { delete controls_.get_texture(); }

void Edit::HandleInput(SDL_Event input) {
  int x{};
  int y{};

  SDL_GetMouseState(&x, &y);

  x /= 4;
  y /= 4;

  int index{(x / Brick::kBrickWidth) + ((y - 20) / Brick::kBrickHeight * 22)};

  switch (drag_) {
    case kPlace:
      bricks_[index] = hover_;
      break;
    case kRemove:
      bricks_[index].set_type(+Brick::kNoType);
      break;
    default:
      break;
  }

  switch (input.type) {
    case SDL_MOUSEMOTION:
      if (x <= kZone.x || x >= kZone.x + kZone.w || y <= kZone.y ||
          y >= kZone.y + kZone.h) {
        in_zone_ = false;
        break;
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
        bricks_[index] = hover_;
        drag_ = kPlace;
      } else if (input.button.button == SDL_BUTTON_RIGHT) {
        bricks_[index].set_type(+Brick::kNoType);
        drag_ = kRemove;
      }
      break;
    case SDL_MOUSEBUTTONUP:
      drag_ = kNoEvent;
      break;
    case SDL_KEYDOWN:
      if (input.key.keysym.sym == SDLK_RETURN) {
        kMedia.enter.PlayChunk();
        SaveLevel();
        set_next_state(StateMachine::kMenuState);
        break;
      }
    default:
      break;
  }
}

StateMachine *Edit::Update() {
  if (get_next_state() == StateMachine::kMenuState) {
    return new Menu();
  }

  return NULL;
}

void Edit::Render() {
  controls_.Render();
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

void Edit::SaveLevel() {
  std::ofstream map{file_};

  for (size_t i{0}; i < Brick::kMaxBricks; ++i) {
    map << "0" << +bricks_[i].get_type() << " ";
    if (i % 21 == 0) {
      map << "\n";
    }
  }

  map.close();
}
