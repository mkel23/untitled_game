#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "texture.h"
#include "tile.h"

class Game {
  public:
    static const int TOTAL_TILES = 1200;

    static Game* Instance();
    Game(Game&) = delete;
    void operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    bool setup();

    void run();

    void teardown();

    void quit();

  private:
    Game() {};
    ~Game() {};

    void operator delete(void *) {};

    bool init();

    bool loadMedia();

    void setTiles();

    void renderDebugGrid(SDL_Rect& camera);

    bool mRunning;

    static Game* sInstance;

    Tile* mTiles[TOTAL_TILES];

    Texture mTileSheetTexture, mPlayerTexture;

    SDL_Rect mTileClips[Tile::TOTAL_TILE_SPRITES], mPlayerClips[static_cast<int>(PlayerDirection::TOTAL)][Player::PLAYER_SPRITE_FRAMES];

    SDL_Window* mWindow = NULL;

    SDL_Renderer* mRenderer = NULL;
};

#endif
