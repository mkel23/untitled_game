#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "texture.h"
#include "tile.h"

enum class PlayerDirection {
  IDLE,
  UP,
  DOWN,
  LEFT,
  RIGHT
};

class Player {
  public:
    static const int PLAYER_HEIGHT = 32;
    static const int PLAYER_WIDTH = 32;

    static const int PLAYER_VEL = 10;

    Player(Texture* playerTexture, SDL_Rect** playerClips);

    void handleEvent(SDL_Event& e);

    void move(Tile* tiles[]);

    void setCamera(SDL_Rect& camera);

    void render(SDL_Rect& camera, int frame);

  private:
    int mVelX, mVelY;

    int mDirection;

    SDL_Rect mBox;

    Texture* mPlayerTexture;
    SDL_Rect** mPlayerClips;
};

#endif
