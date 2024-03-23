#pragma once
#include "SDL2/include/SDL.h"
#include "SDL2_image/include/SDL_image.h"
#include "SDL2_ttf/include/SDL_ttf.h"
#include "init.h"
#include <string>

class LTexture:public AppInit
{

private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;

public:
    LTexture();
    ~LTexture();
    bool loadFromFile(std::string, AppInit&);
    bool loadFromRenderedText(std::string, SDL_Color, TTF_Font&,AppInit&);
    void free();
    void render(int, int, AppInit&, SDL_Rect*clip=nullptr);
    int getWidth();
    int getHeight();

};
