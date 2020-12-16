#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "texture.h"

class Player {
  public:
    static const int PLAYER_HEIGHT = 32;
    static const int PLAYER_WIDTH = 32;

    static const int PLAYER_VEL = 10;

    Player(Texture* playerTexture, SDL_Rect* playerClips);

    void handleEvent(SDL_Event& e);

    void move();

    void render();

  private:
    int mPosX, mPosY;

    int mVelX, mVelY;

    Texture* mPlayerTexture;
    SDL_Rect* mPlayerClips;
};

#endif
