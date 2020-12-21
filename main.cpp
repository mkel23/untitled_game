#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "src/constants.h"
#include "src/globals.h"
#include "src/texture.h"
#include "src/player.h"

using namespace std;

SDL_Renderer* gRenderer = NULL;
const int TOTAL_TILES = 1200;

Texture gTextTexture;
SDL_Window* gWindow = NULL;

SDL_Rect gTileClips[4];
Texture gTileSheetTexture;
SDL_Rect gPlayerClips[1];
Texture gPlayerTexture;

bool init();
bool loadMedia(Tile* tiles[]);
void close(Tile* tiles[]);
void loop(Tile* tiles[]);
bool setTiles(Tile* tiles[]);

bool init() {
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    success = false;
  } else {
    gWindow = SDL_CreateWindow("Untitled", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      success = false;
    } else {
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (gRenderer == NULL) {
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

bool loadMedia(Tile* tiles[]) {
  bool success = true;

  if (!gTileSheetTexture.loadFromFile("res/img/tile.png")) {
    success = false;
  } else {
    int plain = static_cast<int>(TileTypes::PLAIN);
    gTileClips[plain].x = 0;
    gTileClips[plain].y = 0;
    gTileClips[plain].w = 32;
    gTileClips[plain].h = 32;

    int grass = static_cast<int>(TileTypes::GRASS);
    gTileClips[grass].x = 32;
    gTileClips[grass].y = 0;
    gTileClips[grass].w = 32;
    gTileClips[grass].h = 32;

    int rock = static_cast<int>(TileTypes::ROCK);
    gTileClips[rock].x = 64;
    gTileClips[rock].y = 0;
    gTileClips[rock].w = 32;
    gTileClips[rock].h = 32;

    int tallGrass = static_cast<int>(TileTypes::TALL_GRASS);
    gTileClips[tallGrass].x = 0;
    gTileClips[tallGrass].y = 32;
    gTileClips[tallGrass].w = 32;
    gTileClips[tallGrass].h = 32;
  }

  if (!gPlayerTexture.loadFromFile("res/img/player.png")) {
    success = false;
  } else {
    gPlayerClips[0].x = 0;
    gPlayerClips[0].y = 0;
    gPlayerClips[0].w = 32;
    gPlayerClips[0].h = 32;
  }

  if (!setTiles(tiles)) {
    success = false;
  }

  return success;
}

bool setTiles(Tile* tiles[]) {
  bool tilesLoaded = true;

  int x = 0, y = 0;

  std::ifstream map("res/maps/main.map");

  if (map.fail()) {
    tilesLoaded = false;
    printf("Unable to load map file!\n");
  } else {
    for (int i = 0; i < TOTAL_TILES; ++i) {
      int tileType = -1;

      map >> tileType;

      if (map.fail()) {
        printf("Error loading map: Unexpected end of file!\n");
        tilesLoaded = false;
        break;
      }

      if ((tileType >= 0) && (tileType < Tile::TOTAL_TILE_SPRITES)) {
        tiles[i] = new Tile(&gTileSheetTexture, gTileClips, x, y, tileType);
      } else {
        printf("Error loading map: Invalid tile type at %d!\n", i);
        tilesLoaded = false;
        break;
      }

      x += Tile::TILE_WIDTH;

      if (x >= LEVEL_WIDTH) {
        x = 0;
        y += Tile::TILE_HEIGHT;
      }
    }
  }

  map.close();

  return tilesLoaded;
}

void close(Tile* tiles[]) {
  gTextTexture.free();
  gTileSheetTexture.free();
  gPlayerTexture.free();

  for (int i = 0; i < TOTAL_TILES; ++i) {
    if (tiles[i] != NULL) {
      delete tiles[i];
      tiles[i] = NULL;
    }
  }

  SDL_DestroyRenderer(gRenderer);
  gRenderer = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void loop(Tile* tiles[]) {
  SDL_Event e;
  bool quit = false;
  Player player(&gPlayerTexture, gPlayerClips);
  SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }

      player.handleEvent(e);
    }

    player.move(tiles);
    player.setCamera(camera);

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    for (int i = 0; i < TOTAL_TILES; ++i) {
      tiles[i]->render(camera);
    }

    player.render(camera);

    SDL_RenderPresent(gRenderer);
  }
}

int main(int argc, char* args[]) {
  init();

  Tile* tileSet[TOTAL_TILES];

  loadMedia(tileSet);

  loop(tileSet);
  close(tileSet);

  return 0;
}
