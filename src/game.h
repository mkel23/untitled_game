#ifndef GAME_H
#define GAME_H

#include "game_state_manager.h"
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

    SDL_Renderer* renderer();

    SDL_Rect* camera();

    Tile** tiles();

  private:
    Game() {};
    ~Game() {};

    void operator delete(void *) {};

    bool init();

    bool loadMedia();

    void setTiles();

    void renderDebugGrid();

    bool mRunning;

    static Game* sInstance;

    Tile* mTiles[TOTAL_TILES];

    Texture mTileSheetTexture;

    SDL_Rect mTileClips[Tile::TOTAL_TILE_SPRITES];

    SDL_Window* mWindow = NULL;

    SDL_Renderer* mRenderer = NULL;

    GameStateManager mGameStateManager;

    SDL_Rect mCamera;
};

#endif
