#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "src/constants.h"
#include "src/texture.h"
#include "src/player.h"
#include "src/game.h"

using namespace std;

const int TOTAL_TILES = 1200;

int main(int argc, char* args[]) {
  Game game;

  if (game.setup()) {
    game.run();
  }

  game.teardown();
  /* init(); */

  /* Tile* tileSet[TOTAL_TILES]; */

  /* loadMedia(tileSet); */

  /* loop(tileSet); */
  /* close(tileSet); */

  return 0;
}
