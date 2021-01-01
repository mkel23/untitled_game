#include <fstream>
#include <cereal/archives/json.hpp>
#include "game.h"
#include "play_state.h"
#include "notification_manager.h"
#include "save_state_manager.h"

SaveStateManager* SaveStateManager::sInstance = 0;

SaveStateManager* SaveStateManager::Instance() {
  if (sInstance == 0) {
    sInstance = new SaveStateManager();
  }

  return sInstance;
}

void SaveStateManager::setPlayer(Player* player) {
  mPlayer = player;
}

void SaveStateManager::saveGame() {
  SaveStateManager::Instance()->save();
}

void SaveStateManager::save() {
  {
    std::ofstream file(FILE_NAME);
    cereal::JSONOutputArchive archive(file);

    SDL_Rect* playerBox = mPlayer->box();

    // TODO: need to look up templates maybe? could add serialize to PlayerSaveData struct. Then, 1. grab from mPlayer, 2. toss in archive. And that part lives in PlayerSaveData
    archive(
      cereal::make_nvp("playerX", playerBox->x),
      cereal::make_nvp("playerY", playerBox->y),
      cereal::make_nvp("playerDirection", mPlayer->direction())
    );
  }

  NotificationManager::Instance()->addNotification("Game saved!");
}

void SaveStateManager::loadGame() {
  SaveStateManager::Instance()->load();
}

void SaveStateManager::load() {
  {
    std::ifstream file(FILE_NAME);
    cereal::JSONInputArchive archive(file);

    int x, y, direction;

    archive(
      cereal::make_nvp("playerX", x),
      cereal::make_nvp("playerY", y),
      cereal::make_nvp("playerDirection", direction)
    );

    Game::Instance()->gameStateManager()->changeState(new PlayState(x, y, direction));
  }
}
