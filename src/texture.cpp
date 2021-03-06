#include "game.h"
#include "texture.h"

Texture::Texture() {
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

Texture::~Texture() {
  free();
}

bool Texture::loadFromFile(SDL_Renderer* renderer, std::string path) {
  free();

  SDL_Texture* newTexture = NULL;

  SDL_Surface* loadedSurface = IMG_Load(path.c_str());

  SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
  newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

  mWidth = loadedSurface->w;
  mHeight = loadedSurface->h;

  SDL_FreeSurface(loadedSurface);

  mTexture = newTexture;
  return mTexture != NULL;
}

bool Texture::loadFromRenderedText(std::string textureText, TTF_Font* font, SDL_Color textColor) {
  free();

  SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);

  if (textSurface != NULL) {
    mTexture = SDL_CreateTextureFromSurface(Game::Instance()->renderer(), textSurface);
    if (mTexture != NULL) {
      mWidth = textSurface->w;
      mHeight = textSurface->h;
    }

    SDL_FreeSurface(textSurface);
  }

  return mTexture != NULL;
}

void Texture::free() {
  if (mTexture != NULL) {
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
  SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending) {
  SDL_SetTextureBlendMode(mTexture, blending);
}

void Texture::setAlpha(Uint8 alpha) {
  SDL_SetTextureAlphaMod(mTexture, alpha);
}

void Texture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
  SDL_Rect renderQuad = { x, y, mWidth, mHeight };

  if (clip != NULL) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int Texture::getWidth() {
  return mWidth;
}

int Texture::getHeight() {
  return mHeight;
}
