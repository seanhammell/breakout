#include "src/state/play_state.h"

#include <stdio.h>

#include <fstream>

#include "SDL2/SDL.h"

#include "src/entity/ball.h"
#include "src/entity/brick.h"
#include "src/entity/paddle.h"
#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/graphic/ui_element.h"

PlayState::PlayState()
    : score_display_{ &score_texture_, 0, 5 }, ball_{ &blocks_texture_ },
      paddle_{ &blocks_texture_ } {
  if (LoadLevel()) {
    valid();
  }
  score_display_.AlignRightHorizontal();
}

bool PlayState::Load() {
  if (!font_.LoadFromFile("./font/cs50.ttf", 8)) { return false; }
  if (!score_texture_.LoadFromText(font_, "SCORE: 0")) { return false; }
  if (!blocks_texture_.LoadFromFile("./img/blocks.png")) { return false; }
  return true;
}

StateMachine *PlayState::HandleInput(SDL_Event input) {
  ball_.HandleInput(input);
  paddle_.HandleInput(input);
  return NULL;
}

void PlayState::Update() {
  paddle_.Update();
  ball_.Update(paddle_, &bricks_);
}

void PlayState::Render() {
  score_display_.Render();
  paddle_.Render();
  ball_.Render();
  
  int broken_bricks{ 0 };
  for (auto brick : bricks_) {
    if (brick.is_hit()) {
      ++broken_bricks;
      continue;
    }

    brick.Render();
  }

  if (broken_bricks > n_bricks_hit_) {
    n_bricks_hit_ = broken_bricks;
    UpdateScore();
  }
}

bool PlayState::LoadLevel() {
  static const int kMaxBricks{ 176 };

  int x{ 1 };
  int y{ 20 };

  std::ifstream map{ "./meta/level_01.txt" };

  if (map.fail()) {
    fprintf(stderr, "Error loading map file\n");
    return false;
  }

  for (int i{ 0 }; i < kMaxBricks; ++i) {
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
      bricks_.push_back(Brick(x, y, type, &blocks_texture_));
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

void PlayState::UpdateScore() {
  int score{ 0 };
  for (auto brick : bricks_) {
    if (brick.is_hit()) {
      score += brick.value();
    }
  }
  
  char score_buffer[20];
  sprintf(score_buffer, "SCORE: %d", score);
  score_texture_.LoadFromText(font_, score_buffer);
  score_display_.UpdateClip();
  score_display_.AlignRightHorizontal();
}
