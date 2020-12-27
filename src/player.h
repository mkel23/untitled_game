#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "texture.h"
#include "tile.h"

enum class PlayerDirection {
  UP,
  DOWN,
  LEFT,
  RIGHT,
  TOTAL
};

class Player {
  public:
    static const int PLAYER_HEIGHT = 32;
    static const int PLAYER_WIDTH = 32;

    static const int PLAYER_VEL = 4;

    static const int PLAYER_SPRITE_FRAMES = 4;

    Player(Texture* playerTexture, SDL_Rect** playerClips);

    void update();

    void move(Tile* tiles[]);

    void setCamera(SDL_Rect& camera);

    void render(SDL_Renderer* renderer, SDL_Rect& camera, int frame);

  private:
    int mDirection;

    bool mMoving;

    int mTargetX, mTargetY;

    SDL_Rect mBox;

    Texture* mPlayerTexture;
    SDL_Rect** mPlayerClips;
};

#endif
