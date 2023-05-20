#include "src/state/play.h"

#include <stdio.h>

#include <array>
#include <fstream>

#include "SDL2/SDL.h"

#include "src/media.h"
#include "src/entity/ball.h"
#include "src/entity/brick.h"
#include "src/entity/paddle.h"
#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/state/end.h"
#include "src/ui/textbox.h"
#include "src/ui/widget.h"

Play::Play(const char *level)
    : score_display_{ &kMedia.font, new Texture(), { 2, 0 }, { 0, 0 } },
      hearts_{ &kMedia.heart, { 0, 0 }, { 0, 0 } },
      pause_screen_{ &kMedia.pause, { 0, 0 }, { 0, 0 } },
      ball_{ &kMedia.blocks },
      paddle_{ &kMedia.blocks } {
  if (Brick::Load(&bricks_, level)) {
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

    if (ClearBricks()) {
      return new End(score_, true);
    }

    if (ball_.remaining_lives() == 0) {
      return new End(score_, false);
    }
  }

  return NULL;
}

void Play::Render() {
  paddle_.Render();
  ball_.Render();

  for (auto brick : bricks_) {
    if (!brick.is_hit() && brick.get_type() != Brick::kNoType) {
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

bool Play::ClearBricks() {
  score_ = 0;
  size_t broken_bricks{ 0 };
  bool cleared{ true };
  for (auto brick : bricks_) {
    if (brick.is_hit()) {
      score_ += brick.value();
      ++broken_bricks;
      continue;
    } else if (brick.get_type() != Brick::kNoType) {
      cleared = false;
    }
  }

  score_display_.AppendNumber("SCORE: ", score_);
  return cleared;
}
