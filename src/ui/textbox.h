#ifndef SRC_UI_TEXTBOX_H_
#define SRC_UI_TEXTBOX_H_

#include "src/media.h"
#include "src/graphic/font.h"
#include "src/ui/widget.h"

class Textbox : public Widget {
 public:
  Textbox() = default;
  Textbox(Font *font, Texture *texture, Point anchor, Point offset,
          SDL_Rect clip = { });

  ~Textbox() = default;

  Font *get_font() const { return font_; }

  // Appends the integer to the string.
  void AppendNumber(const char *s, int n);

  // Updates the Textbox with the provided string.
  void Update(const char *text);

  void RenderSelected();

 private:
  Font *font_{ NULL };
};

#endif  // SRC_UI_TEXTBOX_H_
