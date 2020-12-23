#include "constants.h"
#include "collision_manager.h"
#include "player.h"

Player::Player(Texture* playerTexture, SDL_Rect** playerClips) {
  mPlayerTexture = playerTexture;
  mPlayerClips = playerClips;

  mTargetX = 0;
  mTargetY = 0;

  mBox.x = mTargetX;
  mBox.y = mTargetY;

  mBox.w = PLAYER_WIDTH;
  mBox.h = PLAYER_HEIGHT;

  mDirection = static_cast<int>(PlayerDirection::IDLE);

  mMoving = false;
}

void Player::handleEvent(SDL_Event& e) {
  if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && !mMoving) {
    switch (e.key.keysym.sym) {
      case SDLK_w:
        mTargetY -= PLAYER_HEIGHT;
        mDirection = static_cast<int>(PlayerDirection::UP);
        mMoving = true;
        break;
      case SDLK_s:
        mTargetY += PLAYER_HEIGHT;
        mDirection = static_cast<int>(PlayerDirection::DOWN);
        mMoving = true;
        break;
      case SDLK_a:
        mTargetX -= PLAYER_WIDTH;
        mDirection = static_cast<int>(PlayerDirection::LEFT);
        mMoving = true;
        break;
      case SDLK_d:
        mTargetX += PLAYER_WIDTH;
        mDirection = static_cast<int>(PlayerDirection::RIGHT);
        mMoving = true;
        break;
    }
  }
}

void Player::move(Tile* tiles[]) {
  int velX, velY;

  if (mTargetX > mBox.x) {
    velX = PLAYER_VEL;
  }

  if (mTargetX < mBox.x) {
    velX = -PLAYER_VEL;
  }

  mBox.x += velX;

  if ((mBox.x < 0) || (mBox.x + PLAYER_WIDTH > LEVEL_WIDTH) || touchesWall(mBox, tiles)) {
    mBox.x -= velX;
    mMoving = false;
    mDirection = static_cast<int>(PlayerDirection::IDLE);
  }

  if (mTargetY > mBox.y) {
    velY = PLAYER_VEL;
  }

  if (mTargetY < mBox.y) {
    velY = -PLAYER_VEL;
  }

  mBox.y += velY;

  if ((mBox.y < 0) || (mBox.y + PLAYER_HEIGHT > LEVEL_HEIGHT) || touchesWall(mBox, tiles)) {
    mBox.y -= velY;
    mMoving = false;
    mDirection = static_cast<int>(PlayerDirection::IDLE);
  }

  if (mTargetX == mBox.x && mTargetY == mBox.y) {
    mMoving = false;
    mDirection = static_cast<int>(PlayerDirection::IDLE);
  }
}

void Player::setCamera(SDL_Rect& camera) {
  camera.x = (mBox.x + PLAYER_WIDTH / 2) - SCREEN_WIDTH / 2;
  camera.y = (mBox.y + PLAYER_HEIGHT / 2) - SCREEN_HEIGHT / 2;

  if (camera.x < 0) {
    camera.x = 0;
  }

  if (camera.x > LEVEL_WIDTH - camera.w) {
    camera.x = LEVEL_WIDTH - camera.w;
  }

  if (camera.y < 0) {
    camera.y = 0;
  }

  if (camera.y > LEVEL_HEIGHT - camera.h) {
    camera.y = LEVEL_HEIGHT - camera.h;
  }
}

void Player::render(SDL_Renderer* renderer, SDL_Rect& camera, int frame) {
  mPlayerTexture->render(mBox.x - camera.x, mBox.y - camera.y, renderer, &mPlayerClips[mDirection][frame]);
}
