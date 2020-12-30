#include "constants.h"
#include "game.h"
#include "play_state.h"
#include "pause_menu_state.h"

PauseMenuState::PauseMenuState() {
  mBackground.w = SCREEN_WIDTH / 2;
  mBackground.h = SCREEN_HEIGHT - 20;
  mBackground.x = (SCREEN_WIDTH / 2) - (mBackground.w / 2);
  mBackground.y = (SCREEN_HEIGHT / 2) - (mBackground.h / 2);

  int buttonCounter = 0;

  mMenuFont = TTF_OpenFont("res/fonts/gameboy.ttf", FONT_SIZE);

  // TODO: better algebra, maybe better initializers? can do constants in the button and allow override? => yes
  //   Would be nice for the generic Menu to handle the sizing/placement. just pass in BTN("STR", FONT); to MENU
  // RESUME GAME
  mButtons.push_back(new MenuButton(GUTTER_WIDTH + mBackground.x, (BUTTON_HEIGHT * buttonCounter) + (GUTTER_HEIGHT * (buttonCounter + 1)) + (buttonCounter * GUTTER_HEIGHT) + mBackground.y, mBackground.w - (2 * GUTTER_WIDTH), BUTTON_HEIGHT, "Resume", mMenuFont, 4, &resumeGame));
  ++buttonCounter;

  // SAVE GAME
  mButtons.push_back(new MenuButton(GUTTER_WIDTH + mBackground.x, (BUTTON_HEIGHT * buttonCounter) + (GUTTER_HEIGHT * (buttonCounter + 1)) + (buttonCounter * GUTTER_HEIGHT) + mBackground.y, mBackground.w - (2 * GUTTER_WIDTH), BUTTON_HEIGHT, "Save", mMenuFont, 4, &saveGame));
  ++buttonCounter;

  // LOAD GAME
  mButtons.push_back(new MenuButton(GUTTER_WIDTH + mBackground.x, (BUTTON_HEIGHT * buttonCounter) + (GUTTER_HEIGHT * (buttonCounter + 1)) + (buttonCounter * GUTTER_HEIGHT) + mBackground.y, mBackground.w - (2 * GUTTER_WIDTH), BUTTON_HEIGHT, "Load", mMenuFont, 4, &loadGame));
  ++buttonCounter;

  // QUIT
  mButtons.push_back(new MenuButton(GUTTER_WIDTH + mBackground.x, (BUTTON_HEIGHT * buttonCounter) + (GUTTER_HEIGHT * (buttonCounter + 1)) + (buttonCounter * GUTTER_HEIGHT) + mBackground.y, mBackground.w - (2 * GUTTER_WIDTH), BUTTON_HEIGHT, "Quit", mMenuFont, 4, &quit));
}

PauseMenuState::~PauseMenuState() {
  TTF_CloseFont(mMenuFont);
}

void PauseMenuState::update() {
  for (int i = 0; i < mButtons.size(); ++i) {
    if (mButtons[i]->isClicked()) {
      mButtons[i]->callCallback();
    }
  }
}

void PauseMenuState::render(int frame) {
  SDL_SetRenderDrawColor(Game::Instance()->renderer(), 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(Game::Instance()->renderer(), &mBackground);

  for (int i = 0; i < mButtons.size(); ++i) {
    mButtons[i]->render();
  }
}

void PauseMenuState::resumeGame() {
  Game::Instance()->gameStateManager()->popState();
}

void PauseMenuState::saveGame() {
  int totalData = 10;
  Sint32 data[totalData];
  SDL_RWops* file = SDL_RWFromFile("saves/save.bin", "w+b");

  data[0] = 32;
  data[1] = 32;

  if (file != NULL) {
    for (int i = 0; i < totalData; ++i) {
      SDL_RWwrite(file, &data[i], sizeof(Sint32), 1);
    }
  }

  SDL_RWclose(file);
}

void PauseMenuState::loadGame() {
  printf("TODO: implement loading and saving\n");
}

void PauseMenuState::quit() {
  Game::Instance()->quit();
}
