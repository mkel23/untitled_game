#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "game_state.h"
#include "player.h"
#include "menu.h"
#include "level.h"

class PlayState : public GameState {
  public:
    // TODO: when moving player save info into a struct, replace these params as well
    PlayState(std::string levelKey, int x = 0, int y = 0, int direction = static_cast<int>(PlayerDirection::DOWN));

    virtual void update();

    virtual void render(int frame);

  private:
    static PlayState* sCurrentPlayState;

    Player* mPlayer;

    Level* mLevel;

    void createMenu();

    void clearMenu();

    static void resumeGame();

    static void quit();

    std::vector<std::shared_ptr<Tile>> mTiles;

    Menu* mMenu = NULL;
};

#endif
