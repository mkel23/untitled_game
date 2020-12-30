#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <vector>
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

    Player(Tile** tiles);
    ~Player();

    void update();

    void move();

    void setCamera();

    void render(int frame);

  private:
    int mDirection;

    bool mMoving;

    int mTargetX, mTargetY;

    SDL_Rect mBox;

    Texture mPlayerTexture;

    std::vector<std::vector<SDL_Rect>> mPlayerClips;

    void loadMedia();

    Tile** mTiles;
};

#endif
