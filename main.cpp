#include <execinfo.h>
#include <unistd.h>
#include "src/game.h"

using namespace std;

void handler(int sig) {
  void* array[10];
  size_t size;

  size = backtrace(array, 10);

  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

int main(int argc, char* args[]) {
  signal(SIGSEGV, handler);
  if (Game::Instance()->setup()) {
    Game::Instance()->run();
  }

  Game::Instance()->teardown();

  return 0;
}
