#include <fstream>
#include <SDL2/SDL_ttf.h>
#include "constants.h"
#include "input_handler.h"
#include "play_state.h"
#include "game.h"

Game* Game::sInstance = 0;

Game* Game::Instance() {
  if (sInstance == 0) {
    sInstance = new Game();
  }

  return sInstance;
}

bool Game::setup() {
  bool success = true;

  if (!init()) {
    success = false;
  }

  if (!loadMedia()) {
    success = false;
  }

  // TODO: this should be replaced with MainMenuState
  mGameStateManager.pushState(new PlayState);
  mRunning = true;
  mCamera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

  setTiles();

  return success;
}

void Game::renderDebugGrid() {
  SDL_SetRenderDrawColor(mRenderer, 0xFF, 0x00, 0x00, 0xFF);
  for (int i = 0; i < LEVEL_HEIGHT / Tile::TILE_HEIGHT; i++) {
    SDL_RenderDrawLine(mRenderer, 0 - mCamera.x, i*32 - mCamera.y, LEVEL_WIDTH - mCamera.x, i*32 - mCamera.y);
  }

  for (int i = 0; i < LEVEL_WIDTH / Tile::TILE_WIDTH; i++) {
    SDL_RenderDrawLine(mRenderer, i*32 - mCamera.x, 0 - mCamera.y, i*32 - mCamera.x, LEVEL_HEIGHT - mCamera.y);
  }
}

void Game::run() {
  int frame = 0;

  while (mRunning) {
    InputHandler::Instance()->update();

    mGameStateManager.update();

    /* TODO: should place this code inside of PlayState */
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(mRenderer);

    for (int i = 0; i < TOTAL_TILES; ++i) {
      mTiles[i]->render(mRenderer, mCamera);
    }

    renderDebugGrid();
    /* TODO: END */

    mGameStateManager.render(frame / 8);

    // TODO: clean up this frame stuff to account for capped fps
    ++frame;

    if (frame / 8 >= Player::PLAYER_SPRITE_FRAMES) {
      frame = 0;
    }

    SDL_RenderPresent(mRenderer);
  }
}

void Game::teardown() {
  mTileSheetTexture.free();

  for (int i = 0; i < TOTAL_TILES; ++i) {
    if (mTiles[i] != NULL) {
      delete mTiles[i];
      mTiles[i] = NULL;
    }
  }

  SDL_DestroyRenderer(mRenderer);
  mRenderer = NULL;

  SDL_DestroyWindow(mWindow);
  mWindow = NULL;

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

bool Game::init() {
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    success = false;
  } else {
    mWindow = SDL_CreateWindow("Untitled", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (mWindow == NULL) {
      success = false;
    } else {
      mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

      if (mRenderer == NULL) {
        success = false;
      } else {
        int imgFlags = IMG_INIT_PNG;

        if (!(IMG_Init(imgFlags) & imgFlags)) {
          success = false;
        }

        if (TTF_Init() == -1) {
          success = false;
        }
      }
    }
  }

  return success;
}

bool Game::loadMedia() {
  bool success = true;

  if (!mTileSheetTexture.loadFromFile(mRenderer, "res/img/tile.png")) {
    success = false;
  } else {
    int plain = static_cast<int>(TileTypes::PLAIN);
    mTileClips[plain].x = 0;
    mTileClips[plain].y = 0;
    mTileClips[plain].w = 32;
    mTileClips[plain].h = 32;

    int grass = static_cast<int>(TileTypes::GRASS);
    mTileClips[grass].x = 32;
    mTileClips[grass].y = 0;
    mTileClips[grass].w = 32;
    mTileClips[grass].h = 32;

    int rock = static_cast<int>(TileTypes::ROCK);
    mTileClips[rock].x = 64;
    mTileClips[rock].y = 0;
    mTileClips[rock].w = 32;
    mTileClips[rock].h = 32;

    int tallGrass = static_cast<int>(TileTypes::TALL_GRASS);
    mTileClips[tallGrass].x = 0;
    mTileClips[tallGrass].y = 32;
    mTileClips[tallGrass].w = 32;
    mTileClips[tallGrass].h = 32;
  }

  return success;
}

// TODO: should probably live on Level instead to allow different areas. also error handling here
void Game::setTiles() {
  int x = 0, y = 0;

  std::ifstream map("res/maps/main.map");

  for (int i = 0; i < TOTAL_TILES; ++i) {
    int tileType = -1;

    map >> tileType;

    if (map.fail()) break;

    if ((tileType >= 0) && (tileType < Tile::TOTAL_TILE_SPRITES)) {
      mTiles[i] = new Tile(&mTileSheetTexture, mTileClips, x, y, tileType);
    } else {
      break;
    }

    x += Tile::TILE_WIDTH;

    if (x >= LEVEL_WIDTH) {
      x = 0;
      y += Tile::TILE_HEIGHT;
    }
  }
}

void Game::quit() {
  mRunning = false;
}

SDL_Renderer* Game::renderer() {
  return mRenderer;
}

SDL_Rect* Game::camera() {
  return &mCamera;
}

Tile** Game::tiles() {
  return mTiles;
}
