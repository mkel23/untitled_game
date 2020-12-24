#include <fstream>
#include <SDL2/SDL_ttf.h>
#include "constants.h"
#include "player.h"
#include "game.h"

Game::Game() {
  setTiles();
}

bool Game::setup() {
  return init() && loadMedia();
}

void Game::renderDebugGrid(SDL_Rect& camera) {
  SDL_SetRenderDrawColor(mRenderer, 0xFF, 0x00, 0x00, 0xFF);
  for (int i = 0; i < LEVEL_HEIGHT / Tile::TILE_HEIGHT; i++) {
    SDL_RenderDrawLine(mRenderer, 0 - camera.x, i*32 - camera.y, LEVEL_WIDTH - camera.x, i*32 - camera.y);
  }

  for (int i = 0; i < LEVEL_WIDTH / Tile::TILE_WIDTH; i++) {
    SDL_RenderDrawLine(mRenderer, i*32 - camera.x, 0 - camera.y, i*32 - camera.x, LEVEL_HEIGHT - camera.y);
  }
}

void Game::run() {
  const Uint8* keystates = SDL_GetKeyboardState(NULL);
  SDL_Event e;
  bool quit = false;
  int frame = 0;

  // TODO: this can probably live on Player once I get better at initializing arrays in a constructor?
  SDL_Rect* nestedPlayerClips[static_cast<int>(PlayerDirection::TOTAL)];
  for (int i = 0; i < static_cast<int>(PlayerDirection::TOTAL); ++i) {
    nestedPlayerClips[i] = mPlayerClips[i];
  }

  Player player(&mPlayerTexture, nestedPlayerClips);
  SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }

    // TODO: move this into an input handler. Also, might need SDL_PumpEvents() inside that handler because it doesn't know we're polling above?
    if (keystates[SDL_SCANCODE_W]) {
      player.handleEvent(PlayerDirection::UP);
    } else if (keystates[SDL_SCANCODE_S]) {
      player.handleEvent(PlayerDirection::DOWN);
    } else if (keystates[SDL_SCANCODE_A]) {
      player.handleEvent(PlayerDirection::LEFT);
    } else if (keystates[SDL_SCANCODE_D]) {
      player.handleEvent(PlayerDirection::RIGHT);
    }

    player.move(mTiles);
    player.setCamera(camera);

    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(mRenderer);

    for (int i = 0; i < TOTAL_TILES; ++i) {
      mTiles[i]->render(mRenderer, camera);
    }

    player.render(mRenderer, camera, frame / 8);

    renderDebugGrid(camera);

    ++frame;

    if (frame / 8 >= Player::PLAYER_SPRITE_FRAMES) {
      frame = 0;
    }

    SDL_RenderPresent(mRenderer);
  }
}

void Game::teardown() {
  mTileSheetTexture.free();
  mPlayerTexture.free();

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

  if (!mPlayerTexture.loadFromFile(mRenderer, "res/img/player.png")) {
    success = false;
  } else {
    for (int direction = 0; direction < static_cast<int>(PlayerDirection::TOTAL); ++direction) {
      for (int spriteFrame = 0; spriteFrame < Player::PLAYER_SPRITE_FRAMES; ++spriteFrame) {
        mPlayerClips[direction][spriteFrame].x = spriteFrame * 32;
        mPlayerClips[direction][spriteFrame].y = direction * 32;
        mPlayerClips[direction][spriteFrame].w = Player::PLAYER_WIDTH;
        mPlayerClips[direction][spriteFrame].h = Player::PLAYER_HEIGHT;
      }
    }
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
