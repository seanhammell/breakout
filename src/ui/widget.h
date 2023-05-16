#ifndef SRC_UI_WIDGET_H_
#define SRC_UI_WIDGET_H_

#include "SDL2/SDL.h"

#include "src/graphic/texture.h"

class Widget {
 public:
  struct Point {
    int x;
    int y;
  };

  static const int kPadding{ 2 };

  Widget() = default;
  Widget(Texture *texture, Point anchor, Point offset, SDL_Rect clip = { });

  ~Widget() = default;

  Texture *get_texture() const { return texture_; }
  Point get_anchor() const { return anchor_; }
  Point get_offset() const { return offset_; }
  int get_width() const { return clip_.w; }
  int get_height() const { return clip_.h; }

  void set_offset(Point offset) { offset_ = offset; }
  void set_clip(SDL_Rect clip) { clip_ = clip; }

  // Renders the Widget to the screen. Widgets use their anchors and offsets by
  // default but true x and y rendering positions may be passed in.
  virtual void Render();

 private:
  // Calculates the x and y positions of the Widget by its anchor and offset.
  int CalculatePosX() const;
  int CalculatePosY() const;

  Texture *texture_{ NULL };
  Point anchor_{ };
  Point offset_{ };
  SDL_Rect clip_{ };
};

#endif  // SRC_UI_WIDGET_H_
