#include "game_state_manager.h"

void GameStateManager::pushState(GameState* state) {
  mGameStates.push_back(state);
}

void GameStateManager::popState() {
  if (!mGameStates.empty()) {
    delete mGameStates.back();
    mGameStates.pop_back();
  }
}

void GameStateManager::changeState(GameState* state) {
  popState();
  pushState(state);
}

void GameStateManager::update() {
  if (!mGameStates.empty()) {
    mGameStates.back()->update();
  }
}

void GameStateManager::render(int frame) {
  if (!mGameStates.empty()) {
    mGameStates.back()->render(frame);
  }
}
