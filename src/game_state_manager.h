#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include <vector>
#include "game_state.h"

class GameStateManager {
  public:
    void pushState(GameState* state);
    void changeState(GameState* state);
    void popState();

    void update();
    void render(int frame);
  private:
    std::vector <GameState*> mGameStates;
};

#endif
