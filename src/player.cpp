#include "constants.h"
#include "collision_manager.h"
#include "player.h"

Player::Player(Texture* playerTexture, SDL_Rect** playerClips) {
  mPlayerTexture = playerTexture;
  mPlayerClips = playerClips;

  mVelX = 0;
  mVelY = 0;

  mBox.x = 0;
  mBox.y = 0;

  mBox.w = PLAYER_WIDTH;
  mBox.h = PLAYER_HEIGHT;

  mDirection = static_cast<int>(PlayerDirection::IDLE);
}

void Player::handleEvent(SDL_Event& e) {
  if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
      case SDLK_w:
        mVelY -= PLAYER_VEL;
        mDirection = static_cast<int>(PlayerDirection::UP);
        break;
      case SDLK_s:
        mVelY += PLAYER_VEL;
        mDirection = static_cast<int>(PlayerDirection::DOWN);
        break;
      case SDLK_a:
        mVelX -= PLAYER_VEL;
        mDirection = static_cast<int>(PlayerDirection::LEFT);
        break;
      case SDLK_d:
        mVelX += PLAYER_VEL;
        mDirection = static_cast<int>(PlayerDirection::RIGHT);
        break;
    }
  } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
      case SDLK_w:
        mVelY += PLAYER_VEL;
        mDirection = static_cast<int>(PlayerDirection::IDLE);
        break;
      case SDLK_s:
        mVelY -= PLAYER_VEL;
        mDirection = static_cast<int>(PlayerDirection::IDLE);
        break;
      case SDLK_a:
        mVelX += PLAYER_VEL;
        mDirection = static_cast<int>(PlayerDirection::IDLE);
        break;
      case SDLK_d:
        mVelX -= PLAYER_VEL;
        mDirection = static_cast<int>(PlayerDirection::IDLE);
        break;
    }
  }
}

void Player::move(Tile* tiles[]) {
  mBox.x += mVelX;

  if ((mBox.x < 0) || (mBox.x + PLAYER_WIDTH > LEVEL_WIDTH) || touchesWall(mBox, tiles)) {
    mBox.x -= mVelX;
  }

  mBox.y += mVelY;

  if ((mBox.y < 0) || (mBox.y + PLAYER_HEIGHT > LEVEL_HEIGHT) || touchesWall(mBox, tiles)) {
    mBox.y -= mVelY;
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

void Player::render(SDL_Rect& camera, int frame) {
  mPlayerTexture->render(mBox.x - camera.x, mBox.y - camera.y, &mPlayerClips[mDirection][frame]);
}
