#include "constants.h"
#include "game.h"
#include "notification_manager.h"
#include "notification.h"

Notification::Notification(std::string text, TTF_Font* font) {
  mBox.x = (SCREEN_WIDTH / 2) - (WIDTH / 2);
  mBox.y = 20;
  mBox.w = WIDTH;
  mBox.h = HEIGHT;

  mTextTexture.loadFromRenderedText(text, font);

  mTextX = mBox.x + ((mBox.w / 2) - (mTextTexture.getWidth() / 2));
  mTextY = mBox.y + ((mBox.h / 2) - (mTextTexture.getHeight() / 2));
}

void Notification::update() {
  if (mRemainingFrames == 0) {
    NotificationManager::Instance()->popNotification();
  }

  --mRemainingFrames;
}

// TODO: some animation stuff would be nice here, either a slide in/out or a fade in/out
void Notification::render() {
  SDL_Rect border = { mBox.x, mBox.y, mBox.w, mBox.h };
  SDL_SetRenderDrawColor(Game::Instance()->renderer(), 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(Game::Instance()->renderer(), &border);

  SDL_Rect fill = { mBox.x + BORDER_SIZE, mBox.y + BORDER_SIZE, mBox.w - (2 * BORDER_SIZE), mBox.h - (2 * BORDER_SIZE) };
  SDL_SetRenderDrawColor(Game::Instance()->renderer(), 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(Game::Instance()->renderer(), &fill);

  mTextTexture.render(mTextX, mTextY, Game::Instance()->renderer());
}
