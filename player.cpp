#include "constants.h"
#include "player.h"

Player::Player(LTexture* playerTexture, SDL_Rect* playerClips) {
  mPlayerTexture = playerTexture;
  mPlayerClips = playerClips;

  mPosX = 0;
  mPosY = 0;

  mVelX = 0;
  mVelY = 0;
}

void Player::handleEvent(SDL_Event& e) {
  if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
      case SDLK_w: mVelY -= PLAYER_VEL; break;
      case SDLK_s: mVelY += PLAYER_VEL; break;
      case SDLK_a: mVelX -= PLAYER_VEL; break;
      case SDLK_d: mVelX += PLAYER_VEL; break;
    }
  } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
      case SDLK_w: mVelY += PLAYER_VEL; break;
      case SDLK_s: mVelY -= PLAYER_VEL; break;
      case SDLK_a: mVelX += PLAYER_VEL; break;
      case SDLK_d: mVelX -= PLAYER_VEL; break;
    }
  }
}

void Player::move() {
  mPosX += mVelX;

  if ((mPosX < 0) || (mPosX + PLAYER_WIDTH > SCREEN_WIDTH)) {
    mPosX -= mVelX;
  }

  mPosY += mVelY;

  if ((mPosY < 0) || (mPosY + PLAYER_HEIGHT > SCREEN_HEIGHT)) {
    mPosY -= mVelY;
  }
}

void Player::render() {
  mPlayerTexture->render(mPosX, mPosY, &mPlayerClips[0]);
}
