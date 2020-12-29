#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "game_state.h"
#include "player.h"

class PlayState : public GameState {
  public:
    PlayState();
    virtual void update();
    virtual void render(int frame);
  private:
    Player* mPlayer;
};

#endif
