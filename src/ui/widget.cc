#include "src/ui/widget.h"

#include "SDL2/SDL.h"

#include "src/graphic/renderer.h"
#include "src/graphic/texture.h"

Widget::Widget(Texture *texture, Point anchor, Point offset, SDL_Rect clip) 
    : texture_{ texture },
      anchor_{ anchor },
      offset_{ offset },
      clip_{ clip } {
  CheckClip();
}

void Widget::Render() {
  texture_->Render(CalculatePosX(), CalculatePosY(), &clip_);
}

void Widget::CheckClip() {
  // If the width of the clip is 0, assume the element is the entire Texture.
  if (clip_.w == 0) {
    clip_.w = texture_->get_width();
    clip_.h = texture_->get_height();
  }
}

int Widget::CalculatePosX() const {
  int anchor{ };
  switch (anchor_.x) {
    case 0:
      anchor = 0 + kPadding;
      break;
    case 1:
      anchor = (Renderer::kVirtualWidth - clip_.w) / 2;
      break;
    case 2:
      anchor = (Renderer::kVirtualWidth - clip_.w) - kPadding;
      break;
    default:
      SDL_Log("Invalid anchor x coordinate: %d\n", anchor_.x);
      break;
  }

  return anchor + offset_.x;
}

int Widget::CalculatePosY() const {
  int anchor{ };
  switch (anchor_.y) {
    case 0:
      anchor = 0 + kPadding;
      break;
    case 1:
      anchor = (Renderer::kVirtualHeight - clip_.h) / 2;
      break;
    case 2:
      anchor = (Renderer::kVirtualHeight - clip_.h) - kPadding;
      break;
    default:
      SDL_Log("Invalid anchor y coordinate: %d\n", anchor_.y);
      break;
  }

  return anchor + offset_.y;
}