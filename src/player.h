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

    Player(std::vector<Tile*>* tiles, int x, int y, int direction);
    ~Player();

    void update();

    void move();

    void setCamera();

    void render(int frame);

    // TODO: should create a PlayerSaveData struct that grabs all relevant data. Can return that here in one call instead.
    SDL_Rect* box();
    int direction();

  private:
    int mDirection;

    bool mMoving;

    int mTargetX, mTargetY;

    SDL_Rect mBox;

    Texture mPlayerTexture;

    std::vector<std::vector<SDL_Rect>> mPlayerClips;

    void loadMedia();

    std::vector<Tile*>* mTiles;
};

#endif
