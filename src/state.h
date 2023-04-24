#ifndef SRC_STATE_H_
#define SRC_STATE_H_

#include "src/gfx/window.h"
#include "src/gfx/renderer.h"

struct State {
  Window window;
  Renderer renderer;
};

extern State kState;

#endif  // SRC_STATE_H_
