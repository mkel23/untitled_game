#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <vector>
#include "texture.h"
#include "tile.h"
#include "level.h"

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

    Player(std::vector<std::shared_ptr<Tile>>* tiles, int x, int y, int direction);
    ~Player();

    void update();

    void move(Level* level);

    void setCamera(Level* level);

    void render(int frame);

    // TODO: should create a PlayerSaveData struct that grabs all relevant data. Can return that here in one call instead.
    SDL_Rect* box();
    int direction();

  private:
    int mDirection;

    bool mMoving;

    int mTargetX, mTargetY;

    SDL_Rect mBox;

    std::vector<std::vector<SDL_Rect>> mPlayerClips;

    void loadMedia();

    std::vector<std::shared_ptr<Tile>>* mTiles;
};

#endif
