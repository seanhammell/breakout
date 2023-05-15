#ifndef SRC_UI_TEXTBOX_H_
#define SRC_UI_TEXTBOX_H_

#include "src/graphic/font.h"
#include "src/ui/widget.h"

class Textbox : public Widget {
 public:
  Textbox() = default;
  Textbox(Font *font, Texture *texture, Point anchor, Point offset,
          SDL_Rect clip = { });

  ~Textbox() = default;

  Font *get_font() const { return font_; }

  // Updates score text with the provided score.
  void UpdateScore(int score);

  // Updates the Textbox with the provided string.
  void Update(const char *text);

 private:
  Font *font_{ NULL };
};

#endif  // SRC_UI_TEXTBOX_H_
