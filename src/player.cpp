#include "constants.h"
#include "collision_manager.h"
#include "input_handler.h"
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

  mDirection = static_cast<int>(PlayerDirection::DOWN);

  mMoving = false;
}

void Player::update() {
  if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)) {
    if (mTargetY == mBox.y) {
      mTargetY -= PLAYER_HEIGHT;
      mDirection = static_cast<int>(PlayerDirection::UP);
      mMoving = true;
    }
  } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)) {
    if (mTargetY == mBox.y) {
      mTargetY += PLAYER_HEIGHT;
      mDirection = static_cast<int>(PlayerDirection::DOWN);
      mMoving = true;
    }
  } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) {
    if (mTargetX == mBox.x) {
      mTargetX -= PLAYER_WIDTH;
      mDirection = static_cast<int>(PlayerDirection::LEFT);
      mMoving = true;
    }
  } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)) {
    if (mTargetX == mBox.x) {
      mTargetX += PLAYER_WIDTH;
      mDirection = static_cast<int>(PlayerDirection::RIGHT);
      mMoving = true;
    }
  }
}

void Player::move(Tile* tiles[]) {
  int velX = 0, velY = 0;

  if (mTargetX > mBox.x) {
    velX = PLAYER_VEL;
  }

  if (mTargetX < mBox.x) {
    velX = -PLAYER_VEL;
  }

  mBox.x += velX;

  if ((mBox.x < 0) || (mBox.x + PLAYER_WIDTH > LEVEL_WIDTH) || touchesWall(mBox, tiles)) {
    mBox.x -= velX;
    mTargetX = mBox.x;
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
    mTargetY = mBox.y;
  }

  if (mTargetX == mBox.x && mTargetY == mBox.y) {
    mMoving = false;
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
  int playerFrame = mMoving ? frame : 0;

  mPlayerTexture->render(mBox.x - camera.x, mBox.y - camera.y, renderer, &mPlayerClips[mDirection][playerFrame]);
}
