#ifndef GAME_H
#define GAME_H

#include "game_state_manager.h"
#include "texture.h"

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
