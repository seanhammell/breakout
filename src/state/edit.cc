#include "src/state/edit.h"

#include "src/entity/brick.h"

Edit::Edit(const char *level) {
  if (Brick::LoadBricks(&bricks_, level)) {
    set_valid();
  }
}

void Edit::Render() {
  for (auto brick : bricks_) {
    brick.Render();
  }
}
