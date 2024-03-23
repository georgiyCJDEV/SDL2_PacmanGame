#pragma once
#include "texture.h"
#include "SDL2/include/SDL.h"

class Button:public LTexture
{

protected:
    SDL_Point mPosition;
    int bWidth;
    int bHeight;

public:
    Button();
    void setPosition(int, int);
    SDL_Point getPosition();
    void setWidth(int);
    void setHeight(int);
    int getWidth();
    int getHeight();
    int handleEvent(SDL_Event&, AppInit&,int);

};