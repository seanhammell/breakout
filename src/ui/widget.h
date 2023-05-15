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

  int get_width() const { return clip_.w; }
  Texture *get_texture() const { return texture_; }

  void set_offset(Point offset) { offset_ = offset; }

  // Checks the clip to see if it was explicitly initialized. If it wasn't,
  // set the clip to the entire Texture.
  void CheckClip();

  // Renders the Widget to the screen.
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
