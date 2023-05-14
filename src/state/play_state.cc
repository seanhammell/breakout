#include "src/state/play_state.h"

#include <stdio.h>

#include <fstream>

#include "SDL2/SDL.h"

#include "src/media.h"
#include "src/entity/ball.h"
#include "src/entity/brick.h"
#include "src/entity/paddle.h"
#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/graphic/ui_element.h"
#include "src/state/over_state.h"

PlayState::PlayState()
    : score_display_{ &score_texture_, 0, 5 },
      pause_screen_{ &kMedia.pause, 0, 0 },
      ball_{ &kMedia.blocks },
      paddle_{ &kMedia.blocks } {
  if (LoadLevel()) { valid(); }
  score_display_.AlignRightHorizontal();
  for (int i{ 0 }; i < ball_.remaining_lives(); ++i) {
    int x{ (kMedia.heart.get_width() + 2) * i + 2 };
    heart_icons_.push_back({&kMedia.heart, x, 5});
  }
}

bool PlayState::Load() {
  if (!score_texture_.LoadFromText(kMedia.regular, "SCORE: 0")) {
    return false;
  }
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
      return new OverState(score_);
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

  for (int i{ 0 }; i < ball_.remaining_lives(); ++i) {
    heart_icons_[i].Render();
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
      bricks_.push_back(Brick(x, y, type, &kMedia.blocks));
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
  score_ = 0;
  for (auto brick : bricks_) {
    if (brick.is_hit()) {
      score_ += brick.value();
    }
  }

  score_display_.UpdateNumeric(&kMedia.regular, &score_texture_, "SCORE: ",
                               score_);
  score_display_.UpdateClip();
  score_display_.AlignRightHorizontal();
}
