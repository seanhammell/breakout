#ifndef SRC_FRAME_RATE_H_
#define SRC_FRAME_RATE_H_

#include <cstdint>

#include <SDL2/SDL.h>

class FrameRate {
 public:
  static constexpr int kTicksPerFrame{ 16 };

  FrameRate() {}
  ~FrameRate() {}

  void StartTimerFPS();
  void StartTimerCap();

  void Synch();

  double CalculateFPS();

 private:
  uint64_t fps_start_{ 0 };
  uint64_t cap_start_{ 0 };
  uint64_t counted_frames_{ 0 };
};

#endif  // SRC_FRAME_RATE_H_
