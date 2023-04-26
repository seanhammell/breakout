#include "src/fsm/menu_state.h"

#include "SDL2/SDL.h"

#include "src/ecs/graphics_component.h"
#include "src/fsm/state_machine.h"

MenuState::MenuState()
  : graphics_{ new GraphicsComponent(GraphicsComponent::kMenu) } {}
MenuState::~MenuState() { delete graphics_; }

StateMachine *MenuState::HandleInput(SDL_Event input) {
  if (input.type == SDL_KEYDOWN) {
    if (input.key.keysym.sym == SDLK_SPACE) {
      return new MenuState();
    }
  }

  return NULL;
}

void MenuState::Update() {
  graphics_->Update();
}
