#include "texture.h"

Texture::Texture() {
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

Texture::~Texture() {
  free();
}

bool Texture::loadFromFile(std::string path) {
  free();

  SDL_Texture* newTexture = NULL;

  SDL_Surface* loadedSurface = IMG_Load(path.c_str());

  SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
  newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

  mWidth = loadedSurface->w;
  mHeight = loadedSurface->h;

  SDL_FreeSurface(loadedSurface);

  mTexture = newTexture;
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

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
  SDL_Rect renderQuad = { x, y, mWidth, mHeight };

  if (clip != NULL) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int Texture::getWidth() {
  return mWidth;
}

int Texture::getHeight() {
  return mHeight;
}

