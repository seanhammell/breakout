#ifndef SRC_UI_WIDGET_H_
#define SRC_UI_WIDGET_H_

#include "SDL2/SDL.h"

#include "src/media/texture.h"

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
  int get_clip_width() const { return clip_.w; }
  int get_clip_height() const { return clip_.h; }
  int get_width() const { return width_; }
  int get_height() const { return height_; }

  void set_offset(Point offset) { offset_ = offset; }
  void set_clip(SDL_Rect clip) { clip_ = clip; }
  void set_width(int width) { width_ = width; }
  void set_height(int height) { height_ = height; }

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

  // The width and height below are used to align groups of Widgets, they do
  // not necessarily reflect the width and height of the Widget itself.
  int width_{ };
  int height_{ };
};

#endif  // SRC_UI_WIDGET_H_
