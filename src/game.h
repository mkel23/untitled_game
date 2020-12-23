#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "texture.h"
#include "tile.h"

class Game {
  public:
    static const int TOTAL_TILES = 1200;

    Game();

    bool setup();

    void run();

    void teardown();

  private:
    bool init();

    bool loadMedia();

    void setTiles();

    void renderDebugGrid(SDL_Rect& camera);

    Tile* mTiles[TOTAL_TILES];

    Texture mTileSheetTexture, mPlayerTexture;

    SDL_Rect mTileClips[Tile::TOTAL_TILE_SPRITES], mPlayerClips[static_cast<int>(PlayerDirection::TOTAL)][Player::PLAYER_SPRITE_FRAMES];

    SDL_Window* mWindow = NULL;

    SDL_Renderer* mRenderer = NULL;
};

#endif
