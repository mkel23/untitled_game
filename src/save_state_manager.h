#ifndef SAVE_STATE_MANAGER_H
#define SAVE_STATE_MANAGER_H

#include "player.h"

class SaveStateManager {
  public:
    static SaveStateManager* Instance();
    SaveStateManager(SaveStateManager&) = delete;
    void operator=(const SaveStateManager&) = delete;
    SaveStateManager& operator=(SaveStateManager&&) = delete;

    void setPlayer(Player* player);

    static void saveGame();
    static void loadGame();

  private:
    const std::string FILE_NAME = "saves/main.json";

    SaveStateManager() {};
    ~SaveStateManager() {};

    void operator delete(void *) {};
    static SaveStateManager* sInstance;

    void save();
    void load();

    Player* mPlayer;
};

#endif
