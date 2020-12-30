#include "constants.h"
#include "game.h"
#include "play_state.h"
#include "main_menu_state.h"

MainMenuState::MainMenuState() {
  mBackground.w = SCREEN_WIDTH / 2;
  mBackground.h = SCREEN_HEIGHT - 20;
  mBackground.x = (SCREEN_WIDTH / 2) - (mBackground.w / 2);
  mBackground.y = (SCREEN_HEIGHT / 2) - (mBackground.h / 2);

  int buttonCounter = 0;

  mMenuFont = TTF_OpenFont("res/fonts/gameboy.ttf", FONT_SIZE);

  // TODO: better algebra, maybe better initializers? can do constants in the button and allow override? => yes
  //   Would be nice for the generic Menu to handle the sizing/placement. just pass in BTN("STR", FONT); to MENU
  // START GAME
  mButtons.push_back(new MenuButton(GUTTER_WIDTH + mBackground.x, (BUTTON_HEIGHT * buttonCounter) + (GUTTER_HEIGHT * (buttonCounter + 1)) + (buttonCounter * GUTTER_HEIGHT) + mBackground.y, mBackground.w - (2 * GUTTER_WIDTH), BUTTON_HEIGHT, "Start", mMenuFont, 4, &newGame));
  ++buttonCounter;

  // LOAD GAME
  mButtons.push_back(new MenuButton(GUTTER_WIDTH + mBackground.x, (BUTTON_HEIGHT * buttonCounter) + (GUTTER_HEIGHT * (buttonCounter + 1)) + (buttonCounter * GUTTER_HEIGHT) + mBackground.y, mBackground.w - (2 * GUTTER_WIDTH), BUTTON_HEIGHT, "Load", mMenuFont, 4, &loadGame));
  ++buttonCounter;

  // QUIT
  mButtons.push_back(new MenuButton(GUTTER_WIDTH + mBackground.x, (BUTTON_HEIGHT * buttonCounter) + (GUTTER_HEIGHT * (buttonCounter + 1)) + (buttonCounter * GUTTER_HEIGHT) + mBackground.y, mBackground.w - (2 * GUTTER_WIDTH), BUTTON_HEIGHT, "Quit", mMenuFont, 4, &quit));
}

MainMenuState::~MainMenuState() {
  TTF_CloseFont(mMenuFont);
  mMenuFont = NULL;
}

void MainMenuState::update() {
  for (int i = 0; i < mButtons.size(); ++i) {
    if (mButtons[i]->isClicked()) {
      mButtons[i]->callCallback();
    }
  }
}

void MainMenuState::render(int frame) {
  SDL_SetRenderDrawColor(Game::Instance()->renderer(), 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(Game::Instance()->renderer(), &mBackground);

  for (int i = 0; i < mButtons.size(); ++i) {
    mButtons[i]->render();
  }
}

void MainMenuState::newGame() {
  Game::Instance()->gameStateManager()->changeState(new PlayState);
}

void MainMenuState::loadGame() {
  printf("TODO: implement loading and saving\n");
}

void MainMenuState::quit() {
  Game::Instance()->quit();
}
