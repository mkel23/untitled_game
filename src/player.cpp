#include "constants.h"
#include "collision_manager.h"
#include "game.h"
#include "input_handler.h"
#include "player.h"

Player::Player(Tile** tiles) {
  loadMedia();

  mTargetX = 0;
  mTargetY = 0;

  mBox.x = mTargetX;
  mBox.y = mTargetY;

  mBox.w = PLAYER_WIDTH;
  mBox.h = PLAYER_HEIGHT;

  mDirection = static_cast<int>(PlayerDirection::DOWN);

  mMoving = false;

  mTiles = tiles;
}

Player::~Player() {
  mPlayerTexture.free();
}

void Player::loadMedia() {
  mPlayerTexture.loadFromFile(Game::Instance()->renderer(), "res/img/player.png");

  for (int direction = 0; direction < static_cast<int>(PlayerDirection::TOTAL); ++direction) {
    mPlayerClips.push_back(std::vector<SDL_Rect>());
    for (int spriteFrame = 0; spriteFrame < PLAYER_SPRITE_FRAMES; ++spriteFrame) {
      SDL_Rect clip;
      clip.x = spriteFrame * 32;
      clip.y = direction * 32;
      clip.w = PLAYER_WIDTH;
      clip.h = PLAYER_HEIGHT;
      mPlayerClips.back().push_back(clip);
    }
  }
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

void Player::move() {
  int velX = 0, velY = 0;

  if (mTargetX > mBox.x) {
    velX = PLAYER_VEL;
  }

  if (mTargetX < mBox.x) {
    velX = -PLAYER_VEL;
  }

  mBox.x += velX;

  if ((mBox.x < 0) || (mBox.x + PLAYER_WIDTH > LEVEL_WIDTH) || touchesWall(mBox, mTiles)) {
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

  if ((mBox.y < 0) || (mBox.y + PLAYER_HEIGHT > LEVEL_HEIGHT) || touchesWall(mBox, mTiles)) {
    mBox.y -= velY;
    mTargetY = mBox.y;
  }

  if (mTargetX == mBox.x && mTargetY == mBox.y) {
    mMoving = false;
  }
}

void Player::setCamera() {
  // TODO: this feels a little dirty. Should have a function on Game that allows to set X/Y coords on camera
  SDL_Rect* camera = Game::Instance()->camera();

  camera->x = (mBox.x + PLAYER_WIDTH / 2) - SCREEN_WIDTH / 2;
  camera->y = (mBox.y + PLAYER_HEIGHT / 2) - SCREEN_HEIGHT / 2;

  if (camera->x < 0) {
    camera->x = 0;
  }

  if (camera->x > LEVEL_WIDTH - camera->w) {
    camera->x = LEVEL_WIDTH - camera->w;
  }

  if (camera->y < 0) {
    camera->y = 0;
  }

  if (camera->y > LEVEL_HEIGHT - camera->h) {
    camera->y = LEVEL_HEIGHT - camera->h;
  }
}

void Player::render(int frame) {
  int playerFrame = mMoving ? frame : 0;
  SDL_Renderer* renderer = Game::Instance()->renderer();
  SDL_Rect* camera = Game::Instance()->camera();

  mPlayerTexture.render(mBox.x - camera->x, mBox.y - camera->y, renderer, &mPlayerClips[mDirection][playerFrame]);
}
