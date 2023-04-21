#include "src/frame_rate.h"

#include <cstdint>

#include <SDL2/SDL.h>

// Starts the timer to calculate FPS.
void FrameRate::StartTimerFPS() {
  fps_start_ = SDL_GetTicks64();
}

// Starts the timer to cap the frame rate.
void FrameRate::StartTimerCap() {
  cap_start_ = SDL_GetTicks64();
}

// Synchronizes rendering by delaying if the frame took less ticks than the
// desired ticks per frame.
void FrameRate::Synch() {
  uint64_t frame_ticks{ SDL_GetTicks64() - cap_start_ };
  if (frame_ticks < kTicksPerFrame) {
    SDL_Delay(kTicksPerFrame - frame_ticks);
  }
}

// Calculated frames per second by dividing the total frames by the time since
// the game loop began. This function assumes that it is called every frame.
double FrameRate::CalculateFPS() {
  ++counted_frames_;
  uint64_t ticks{ SDL_GetTicks64() - fps_start_ };
  return static_cast<double>(counted_frames_ / (ticks / 1000.0));
}
