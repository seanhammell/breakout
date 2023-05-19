#include "src/entity/brick.h"

#include <array>
#include <fstream>

#include "SDL2/SDL.h"

#include "src/media.h"
#include "src/graphic/renderer.h"
#include "src/graphic/texture.h"

Brick::Brick(int x, int y, BrickType type, Texture *texture)
    : x_pos_{ x }, y_pos_{ y }, type_{ type }, texture_{ texture },
      clip_{ type * kClipWidth - kClipWidth, 0, kClipWidth, kClipHeight } {}

constexpr int Brick::operator+(BrickType type) {
  return static_cast<int>(type);
}

void Brick::set_type(int type) {
  type_ = static_cast<BrickType>(type);
  clip_.x = type * kClipWidth - kClipWidth;
}

bool Brick::Load(std::array<Brick, kMaxBricks> *bricks, const char *file) {
  int x{ 1 };
  int y{ 20 };

  std::ifstream map{ file };

  if (map.fail()) {
    fprintf(stderr, "Error loading map file\n");
    return false;
  }

  for (size_t i{ 0 }; i < kMaxBricks; ++i) {
    int tile{ -1 };
    map >> tile;
    Brick::BrickType type{ static_cast<Brick::BrickType>(tile) };

    if (map.fail()) {
      fprintf(stderr, "Unexpected EOF\n");
      return false;
    }

    if (type < Brick::kNoType || type > Brick::kTotalTypes) {
      fprintf(stderr, "Invalid brick type\n");
      return false;
    }

    if (type > Brick::kNoType && type < Brick::kTotalTypes) {
      (*bricks)[i] = Brick(x, y, type, &kMedia.blocks);
    }

    x += Brick::kBrickWidth;
    if (x >= Renderer::kVirtualWidth) {
      x = 1;
      y += Brick::kBrickHeight;
    }
  }

  map.close();
  return true;
}

void Brick::Render() {
  texture_->Render(x_pos_, y_pos_, &clip_);
}
