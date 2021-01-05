#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "game_state.h"
#include "player.h"

class PlayState : public GameState {
  public:
    static const int TOTAL_TILES = 1200;

    PlayState(int x = 0, int y = 0, int direction = static_cast<int>(PlayerDirection::DOWN));
    ~PlayState();

    virtual void update();

    virtual void render(int frame);

  private:
    Player* mPlayer;

    void setTiles();

    void loadMedia();

    void renderDebugGrid();

    std::vector<Tile*> mTiles;

    Texture mTileSheetTexture;

    SDL_Rect mTileClips[Tile::TOTAL_TILE_SPRITES];
};

#endif
