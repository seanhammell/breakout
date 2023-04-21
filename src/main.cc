#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "src/renderer.h"
#include "src/texture.h"
#include "src/font.h"

// Initializes project SDL libraries.
bool Open() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    return false;
  }

  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    fprintf(stderr, "Error initializing SDL_image: %s\n", IMG_GetError());
    return false;
  }

  if (TTF_Init() != 0) {
    fprintf(stderr, "Error initializing SDL_ttf: %s\n", TTF_GetError());
    return false;
  }

  return true;
}

// Quits project SDL libraries.
void Close() {
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

int main() {
  if (!Open()) {
    return 0;
  }

  Renderer renderer;
  if (!renderer.IsInstantiated()) {
    Close();
    return 0;
  }

  Font font;
  Texture text;
  font.LoadFromFile("./fonts/cs50_font.ttf", 8);
  text.LoadFromText(renderer.GetRenderer(), font, "Breakout");

  SDL_Event e;
  for (;;) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        Close();
        return 0;
      }
    }

    renderer.Clear();
    text.Render(renderer.GetRenderer(), 0, 0);
    renderer.Present();
  }

  return 0;
}
