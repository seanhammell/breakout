#include "src/state/play.h"

#include <stdio.h>

#include <fstream>

#include "SDL2/SDL.h"

#include "src/media.h"
#include "src/entity/ball.h"
#include "src/entity/brick.h"
#include "src/entity/paddle.h"
#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/state/game_over.h"
#include "src/ui/textbox.h"
#include "src/ui/widget.h"

Play::Play(const char *level)
    : score_display_{ &kMedia.font, new Texture(), { 2, 0 }, { 0, 0 } },
      hearts_{ &kMedia.heart, { 0, 0 }, { 0, 0 } },
      pause_screen_{ &kMedia.pause, { 0, 0 }, { 0, 0 } },
      ball_{ &kMedia.blocks },
      paddle_{ &kMedia.blocks } {
  if (LoadLevel(level)) {
    set_valid();
  }
}

Play::~Play() {
  delete score_display_.get_texture();
}

void Play::HandleInput(SDL_Event input) {
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

StateMachine *Play::Update() {
  if (!paused_) {
    paddle_.Update();
    ball_.Update(paddle_, &bricks_);
    CountBricks();
    if (ball_.remaining_lives() == 0) {
      return new GameOver(score_);
    }
  }

  return NULL;
}

void Play::Render() {
  paddle_.Render();
  ball_.Render();

  for (auto brick : bricks_) {
    if (!brick.is_hit()) {
      brick.Render();
    }
  }

  score_display_.Render();

  for (int i{ 0 }; i < ball_.remaining_lives(); ++i) {
    hearts_.set_offset({ (hearts_.get_width() + Widget::kPadding) * i, 0 });
    hearts_.Render();
  }
  hearts_.set_offset({ 0, 0 });

  if (paused_) {
    pause_screen_.Render();
    return;
  }
}

bool Play::LoadLevel(const char *level) {
  static const int kMaxBricks{ 176 };

  int x{ 1 };
  int y{ 20 };

  std::ifstream map{ level };

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

void Play::CountBricks() {
  score_ = 0;
  size_t broken_bricks{ 0 };
  for (auto brick : bricks_) {
    if (brick.is_hit()) {
      score_ += brick.value();
      ++broken_bricks;
      continue;
    }
  }

  score_display_.AppendNumber("SCORE: ", score_);
}
