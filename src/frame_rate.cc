#include "src/frame_rate.h"

// Starts the timer to calculate FPS.
void FrameRate::StartTimerFPS() {
  fps_ticks_ = SDL_GetTicks64();
}

// Starts the timer to cap the frame rate.
void FrameRate::StartTimerCap() {
  cap_ticks_ = SDL_GetTicks64();
}
