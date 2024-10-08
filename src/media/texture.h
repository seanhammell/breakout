#ifndef SRC_MEDIA_TEXTURE_H_
#define SRC_MEDIA_TEXTURE_H_

#include "SDL2/SDL.h"
#include "src/media/font.h"

class Texture {
 public:
  Texture() = default;

  ~Texture();

  static bool LoadMediaTextures();

  int get_width() const { return width_; }
  int get_height() const { return height_; }

  // Loads the Texture from the file at the given path.
  bool LoadFromFile(const char *path);

  // Loads the Texture of the text in the given font.
  bool LoadFromText(const Font &font, const char *text);

  // Renders the Texture to the screen.
  void Render(const int x, const int y, SDL_Rect *clip = NULL);

 private:
  // Frees the current texture_ if it exists.
  void Free();

  SDL_Texture *texture_{NULL};
  int width_{0};
  int height_{0};
};

#endif  // SRC_MEDIA_TEXTURE_H_
