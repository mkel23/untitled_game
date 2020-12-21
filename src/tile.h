#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
#include "texture.h"

enum class TileTypes {
  PLAIN,
  GRASS,
  ROCK,
  TALL_GRASS
};

class Tile {
  public:
    static const int TILE_WIDTH = 32;
    static const int TILE_HEIGHT = 32;

    static const int TOTAL_TILE_SPRITES = 4;

    Tile(Texture* tileTexture, SDL_Rect* tileClips, int x, int y, int tileType);

    void render(SDL_Rect& camera);

    int getType();

    SDL_Rect getBox();

  private:
    SDL_Rect mBox;

    int mType;

    Texture* mTileTexture;
    SDL_Rect* mTileClips;
};

#endif
