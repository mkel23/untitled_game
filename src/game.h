#ifndef GAME_H
#define GAME_H

#include "game_state_manager.h"
#include "texture.h"
#include "tile.h"

class Game {
  public:
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

    GameStateManager* gameStateManager();

  // TODO: game data should live in the game instance. we can set it up w/ some dummy data,
  //   and maybe a nice way of indexing it. Can even extract it to it's own class and just keep a
  //   pointer here.
  private:
    Game() {};
    ~Game() {};

    void operator delete(void *) {};

    bool init();

    bool mRunning;

    static Game* sInstance;

    SDL_Window* mWindow = NULL;

    SDL_Renderer* mRenderer = NULL;

    GameStateManager mGameStateManager;

    SDL_Rect mCamera;
};

#endif
