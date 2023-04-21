#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "src/renderer.h"
#include "src/texture.h"
#include "src/font.h"
#include "src/frame_rate.h"

static Renderer kRenderer;

static Font kFont;
static Texture kTextTexture;

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

// Loads the top-level meida files.
bool LoadMedia() {
  if (!kFont.LoadFromFile("./fonts/cs50_font.ttf", 8)) {
    fprintf(stderr, "Failed to load font\n");
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
  if (!Open() || !LoadMedia() || !kRenderer.IsInstantiated()) {
    Close();
    return 0;
  }

  if (!LoadMedia()) {
    Close();
    return 0;
  }

  SDL_Event e;
  FrameRate fps;
  char fps_buffer[10];

  fps.StartTimerFPS();
  for (;;) {
    fps.StartTimerCap();
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        Close();
        return 0;
      }
    }

    sprintf(fps_buffer, "FPS: %2.0f", fps.CalculateFPS());
    kTextTexture.LoadFromText(kRenderer.GetRenderer(), kFont, fps_buffer);

    kRenderer.Clear();
    kTextTexture.Render(kRenderer.GetRenderer(), 1, 0);
    kRenderer.Present();

    fps.Synch();
  }

  return 0;
}
