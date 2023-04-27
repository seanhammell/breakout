#ifndef SRC_GRAPHIC_TEXTURE_H_
#define SRC_GRAPHIC_TEXTURE_H_

#include "SDL2/SDL.h"

#include "src/graphic/font.h"

class Texture {
 public:
  Texture() {}
  ~Texture() { Free(); }

  // Loads a texture from the given path.
  bool LoadFromFile(const char *path);

  // Loads a texture of the text in the given font.
  bool LoadFromText(const Font& font, const char *text);

  // Renders the texture to the screen.
  void Render(const int x, const int y, SDL_Rect *clip = NULL);

 private:
  // Frees the current texture if it exists.
  void Free();

  SDL_Texture *texture_{ NULL };
  int width_{ 0 };
  int height_{ 0 };
};

#endif  // SRC_GRAPHIC_TEXTURE_H_
