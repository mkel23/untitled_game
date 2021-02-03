#include "game.h"
#include "input_handler.h"
#include "save_state_manager.h"
#include "play_state.h"

PlayState* PlayState::sCurrentPlayState = 0;

PlayState::PlayState(std::string levelKey, int x, int y, int direction) {
  mLevel = new Level(levelKey);
  // TODO: doesn't feel right to pass in tiles here, maybe on move instead?
  mPlayer = new Player(mLevel->tiles(), x, y, direction);
  SaveStateManager::Instance()->setPlayer(mPlayer);
}

void PlayState::update() {
  if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
    createMenu();
  }

  if (mMenu == NULL) {
    mPlayer->update();
    mPlayer->move(mLevel);
    mPlayer->setCamera(mLevel);
  } else {
    mMenu->update();
  }
}

void PlayState::render(int frame) {
  mLevel->render();

  mPlayer->render(frame);

  if (mMenu != NULL) {
    mMenu->render();
  }
}

void PlayState::createMenu() {
  std::vector<std::pair<std::string, void(*)()>> labelsAndCallbacks;

  labelsAndCallbacks.push_back(std::pair<std::string, void(*)()>("Resume", &resumeGame));
  labelsAndCallbacks.push_back(std::pair<std::string, void(*)()>("Save", &SaveStateManager::saveGame));
  labelsAndCallbacks.push_back(std::pair<std::string, void(*)()>("Load", &SaveStateManager::loadGame));
  labelsAndCallbacks.push_back(std::pair<std::string, void(*)()>("Quit", &quit));

  mMenu = new Menu(labelsAndCallbacks);

  sCurrentPlayState = this;
}

void PlayState::clearMenu() {
  mMenu = NULL;
  sCurrentPlayState = 0;
};

void PlayState::resumeGame() {
  if (sCurrentPlayState != 0) {
    sCurrentPlayState->clearMenu();
  }
}

void PlayState::quit() {
  Game::Instance()->quit();
}
