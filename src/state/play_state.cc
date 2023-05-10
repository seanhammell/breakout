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
#include "src/state/menu_state.h"

PlayState::PlayState()
    : score_display_{ &score_texture_, 0, 5 },
      pause_screen_{ &pause_texture_, 0, 0 }, ball_{ &blocks_texture_ },
      paddle_{ &blocks_texture_ } {
  if (LoadLevel()) { valid(); }
  score_display_.AlignRightHorizontal();
}

bool PlayState::Load() {
  if (!font_.LoadFromFile("./font/cs50.ttf", 8)) { return false; }
  if (!score_texture_.LoadFromText(font_, "SCORE: 0")) { return false; }
  if (!blocks_texture_.LoadFromFile("./img/blocks.png")) { return false; }
  if (!pause_texture_.LoadFromFile("./img/pause.png")) { return false; }
  return true;
}

void PlayState::HandleInput(SDL_Event input) {
  if (input.type == SDL_KEYDOWN && input.key.repeat == 0) {
    if (input.key.keysym.sym == SDLK_p) {
      paused_ = !paused_;
    }
  }

  if (!paused_) {
    ball_.HandleInput(input);
    paddle_.HandleInput(input);
  }
}

StateMachine *PlayState::Update() {
  if (!paused_) {
    paddle_.Update();
    ball_.Update(paddle_, &bricks_);
    if (ball_.remaining_lives() == 0) {
      return new MenuState();
    }
  }

  return NULL;
}

void PlayState::Render() {
  score_display_.Render();
  paddle_.Render();
  ball_.Render();

  size_t broken_bricks{ 0 };
  for (auto brick : bricks_) {
    if (brick.is_hit()) {
      ++broken_bricks;
      continue;
    }

    brick.Render();
  }

  if (paused_) {
    pause_screen_.Render();
    return;
  }

  if (broken_bricks > n_bricks_hit_) {
    n_bricks_hit_ = broken_bricks;
    if (n_bricks_hit_ > (bricks_.size() / (4 / milestone_))) {
      ++milestone_;
      ball_.set_speed(milestone_);
    }
    UpdateScore();
  }
}

bool PlayState::LoadLevel() {
  static const int kMaxBricks{ 176 };

  int x{ 1 };
  int y{ 20 };

  std::ifstream map{ "./res/level_01.txt" };

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

  constexpr int kBufferLength{ 20 };
  char score_buffer[kBufferLength];
  snprintf(score_buffer, kBufferLength - 1, "SCORE: %d", score);
  score_texture_.LoadFromText(font_, score_buffer);
  score_display_.UpdateClip();
  score_display_.AlignRightHorizontal();
}
