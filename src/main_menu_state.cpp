#include <vector>
#include "constants.h"
#include "game.h"
#include "play_state.h"
#include "save_state_manager.h"
#include "main_menu_state.h"

MainMenuState::MainMenuState() {
  std::vector<std::pair<std::string, void(*)()>> labelsAndCallbacks;

  labelsAndCallbacks.push_back(std::pair<std::string, void(*)()>("Start", &newGame));
  labelsAndCallbacks.push_back(std::pair<std::string, void(*)()>("Load", &SaveStateManager::loadGame));
  labelsAndCallbacks.push_back(std::pair<std::string, void(*)()>("Quit", &quit));

  mMenu = new Menu(labelsAndCallbacks, true);
}

void MainMenuState::update() {
  mMenu->update();
}

void MainMenuState::render(int frame) {
  mMenu->render();
}

void MainMenuState::newGame() {
  Game::Instance()->gameStateManager()->changeState(new PlayState("main"));
}

void MainMenuState::quit() {
  Game::Instance()->quit();
}
