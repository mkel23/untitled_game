#include "src/game.h"

using namespace std;

int main(int argc, char* args[]) {
  if (Game::Instance()->setup()) {
    Game::Instance()->run();
  }

  Game::Instance()->teardown();

  return 0;
}
