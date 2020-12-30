#include "collision_manager.h"
#include "game.h"
#include "input_handler.h"
#include "menu_button.h"

MenuButton::MenuButton(int x, int y, int width, int height, std::string text, TTF_Font* font, int borderSize, void (*callback)()) {
  mBox.x = x;
  mBox.y = y;
  mBox.w = width;
  mBox.h = height;

  mTextTexture.loadFromRenderedText(text, font);

  // We want the text centered in the button
  mTextX = mBox.x + ((mBox.w / 2) - (mTextTexture.getWidth() / 2));
  mTextY = mBox.y + ((mBox.h / 2) - (mTextTexture.getHeight() / 2));

  mBorderSize = borderSize;

  mCallback = callback;
}

void MenuButton::render() {
  // Outline first since the button will be drawn on top
  SDL_Rect border = { mBox.x, mBox.y, mBox.w, mBox.h };
  SDL_SetRenderDrawColor(Game::Instance()->renderer(), 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(Game::Instance()->renderer(), &border);

  // Button fill color to create illusion of border
  SDL_Rect fill = { mBox.x + mBorderSize, mBox.y + mBorderSize, mBox.w - (2 * mBorderSize), mBox.h - (2 * mBorderSize) };
  SDL_SetRenderDrawColor(Game::Instance()->renderer(), 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(Game::Instance()->renderer(), &fill);

  // Render text on top
  mTextTexture.render(mTextX, mTextY, Game::Instance()->renderer());
}

bool MenuButton::isClicked() {
  std::pair<int, int> mouseCoords = InputHandler::Instance()->mouseCoords();

  if (checkInBounds(mBox, mouseCoords.first, mouseCoords.second)) {
    return InputHandler::Instance()->isMouseClicked();
  }

  return false;
}

void MenuButton::callCallback() {
  (*mCallback)();
}
