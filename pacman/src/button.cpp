#include "button.h"

Button::Button()
{
    this->bWidth = 0;
    this->bHeight = 0;

    this->mPosition.x = 0;
    this->mPosition.y = 0;
}

void Button::setWidth(int widthval)
{
    bWidth = widthval;
}

void Button::setHeight(int heightval)
{
    bHeight = heightval;
}

void Button::setPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}

SDL_Point Button::getPosition()
{
    return mPosition;
}

int Button::getWidth()
{
    return bWidth;
}

int Button::getHeight()
{
    return bHeight;
}

int Button::handleEvent(SDL_Event& e, AppInit& app, int bval)
{

    if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        bool inside = true;

        if (x < mPosition.x)
        {
            inside = false;
        }

        else if (x > mPosition.x + bWidth)
        {
            inside = false;
        }

        else if (y < mPosition.y)
        {
            inside = false;
        }

        else if (y > mPosition.y + bHeight)
        {
            inside = false;
        }

        if (inside)
        {

            switch (e.type)
            {

            case SDL_MOUSEBUTTONDOWN:
            {
                SDL_SetRenderDrawColor(app.getRenderer(), 0, 0, 0, 0);
                SDL_RenderClear(app.getRenderer());
                SDL_RenderPresent(app.getRenderer());
                return bval;
            }

            }
        }
    }

    return -1;
}