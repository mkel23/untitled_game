#ifndef GAME_STATE_H
#define GAME_STATE_H

class GameState {
  public:
    virtual void update() = 0;
    // TODO: move the frame to Game when dealing with capping FPS
    virtual void render(int frame) = 0;
};

#endif
