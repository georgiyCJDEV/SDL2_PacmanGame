#include "ghost.h"
#include <iostream>

Ghost::Ghost()
{
    this->objType = UNDEFINED;
}

Ghost::Ghost(AppInit& app)
{
    loadMedia(app);

    this->ghosts = new Ghost*[4];
    setGhosts();

    this->objType = MAIN;
}

Ghost::Ghost(Uint16 mPosX, Uint16 mPosY, Uint8 color, LTexture* gGhostTex)
{
    this->gGhostTex = gGhostTex;
    this->color = color;
    setGSprites(this->color);

    this->side = 0;
    this->frame = 0;

    this->mPosX = mPosX;
    this->mPosY = mPosY;

    this->mVelX = 0;
    this->mVelY = 0;

    this->mBox.x = this->mPosX;
    this->mBox.y = this->mPosY;
    this->mBox.w = 16;
    this->mBox.h = 16;
    this->isColliding = false;

    this->movXFlagEqYl = 0;
    this->movXFlagEqYl2 = 0;
    this->movXFlagEqYm = 0;
    this->movXFlagEqYm2 = 0;
    this->movYFlagEqxXl = 0;
    this->movYFlagEqxXl2 = 0;
    this->movYFlagEqxXm = 0;
    this->movYFlagEqxXm2 = 0;
    this->movXFlaglYl = 0;
    this->movXFlaglYm = 0;
    this->movXFlagmYl = 0;
    this->movXFlagmYm = 0;

    this->currentClip = &gGhostMov[0][0][0];

    this->objType = SUB;
}

Ghost::~Ghost()
{
    std::cout << "\nGhost destructor called";
    if (this->objType == MAIN && gGhostTex != nullptr)
    {
        gGhostTex->~LTexture();
        delete gGhostTex;
        gGhostTex = nullptr;
    }
    std::cout << "\nGhost destructor worked";
}

Ghost** Ghost::getGhosts()
{
    return ghosts;
}

void Ghost::setGhosts()
{
    ghosts[Red] = new Ghost(BOUNDS_X + 88, BOUNDS_Y + 144, Red, gGhostTex);
    ghosts[Blue] = new Ghost(BOUNDS_X + 168, BOUNDS_Y + 144, Blue, gGhostTex);
    ghosts[Yellow] = new Ghost(BOUNDS_X + 88, BOUNDS_Y + 208, Yellow, gGhostTex);
    ghosts[Pink] = new Ghost(BOUNDS_X + 168, BOUNDS_Y + 208, Pink, gGhostTex);
    
    for (size_t i = 0; i < TOTAL_GHOSTS; i++)
    {
        ghosts[i]->setGSprites(ghosts[i]->getColor());
    }
}

void Ghost::remove_objects()
{
    for (int i = 0; i < TOTAL_GHOSTS; i++)
    {
        if (ghosts != nullptr)
        {
            if (ghosts[i] != nullptr)
            {
                ghosts[i]->~Ghost();
                delete ghosts[i];
                ghosts[i] = nullptr;
            }
        }
    }
    delete[] ghosts;
    ghosts = nullptr;
}

void Ghost::renderGhosts(AppInit&app)
{
    for (int i = 0; i < TOTAL_GHOSTS; i++)
    {
        ghosts[i]->render(app);
    }
}

void Ghost::loadMedia(AppInit& app)
{
    gGhostTex = new LTexture();
    gGhostTex->loadFromFile("res/sprites/ghost.png", app);
}

void Ghost::setBox(int boxXval, int boxYval)
{
    mBox.x = boxXval;
    mBox.y = boxYval;
}

void Ghost::setFlags(int xEqYl, int xEqYl2, int xEqYm, int xEqYm2, int yEqXl, int yEqXl2, int yEqXm, int yEqXm2, int xlYl, int xlYm, int xmYl, int xmYm)
{
    this->movXFlagEqYl = xEqYl;
    this->movXFlagEqYl2 = xEqYl2;
    this->movXFlagEqYm = xEqYm;
    this->movXFlagEqYm2 = xEqYm2;
    this->movYFlagEqxXl = yEqXl;
    this->movYFlagEqxXl2 = yEqXl2;
    this->movYFlagEqxXm = yEqXm;
    this->movYFlagEqxXm2 = yEqXm2;
    this->movXFlaglYl = xlYl;
    this->movXFlaglYm = xlYm;
    this->movXFlagmYl = xmYl;
    this->movXFlagmYm = xmYm;
}

void Ghost::setColor(int colorVal)
{
    color = colorVal;
}

Uint8& Ghost::getColor()
{
    return color;
}

void Ghost::setMSide(int sideVal)
{
    side = sideVal;
}

void Ghost::setCurrentClip()
{
    currentClip = &gGhostMov[color][side][frame / 4];
}

bool Ghost::moveRight(Wall& walls)
{
    bool success = false;
    int mVelX2 = 0, mVelY2 = 0;
    mVelX2 += ENT_VEL;

    mPosX += mVelX2;
    mBox.x = mPosX;
    mPosY += mVelY2;
    mBox.y = mPosY;

    if (walls.touchesWall(mBox))
    {

        mPosX -= mVelX2;
        mBox.x = mPosX;
        mPosY -= mVelY2;
        mBox.y = mPosY;

        mVelX2 -= ENT_VEL;
        success = false;

    }

    else
    {

        mPosX -= mVelX2;
        mBox.x = mPosX;
        mPosY -= mVelY2;
        mBox.y = mPosY;

        mVelX2 -= ENT_VEL;
        mVelX += ENT_VEL;
        setColor(color);
        setMSide(rMov);
        move(walls);

        mVelX -= ENT_VEL;
        success = true;

    }
    return success;
}

bool Ghost::moveLeft(Wall& walls)
{
    bool success = false;
    int mVelX2 = 0, mVelY2 = 0;
    mVelX2 -= ENT_VEL;

    mPosX += mVelX2;
    mBox.x = mPosX;
    mPosY += mVelY2;
    mBox.y = mPosY;

    if (walls.touchesWall(mBox))
    {

        mPosX -= mVelX2;
        mBox.x = mPosX;
        mPosY -= mVelY2;
        mBox.y = mPosY;

        mVelX2 += ENT_VEL;
        success = false;

    }

    else
    {

        mPosX -= mVelX2;
        mBox.x = mPosX;
        mPosY -= mVelY2;
        mBox.y = mPosY;

        mVelX2 += ENT_VEL;
        mVelX -= ENT_VEL;
        setColor(color);
        setMSide(lMov);
        move(walls);

        mVelX += ENT_VEL;
        success = true;

    }
    return success;
}

bool Ghost::moveUp(Wall& walls)
{
    bool success = false;
    int mVelX2 = 0, mVelY2 = 0;
    mVelY2 -= ENT_VEL;

    mPosX += mVelX2;
    mBox.x = mPosX;
    mPosY += mVelY2;
    mBox.y = mPosY;

    if (walls.touchesWall(mBox))
    {

        mPosX -= mVelX2;
        mBox.x = mPosX;
        mPosY -= mVelY2;
        mBox.y = mPosY;

        mVelY2 += ENT_VEL;
        success = false;

    }

    else
    {

        mPosX -= mVelX2;
        mBox.x = mPosX;
        mPosY -= mVelY2;
        mBox.y = mPosY;

        mVelY2 += ENT_VEL;
        mVelY -= ENT_VEL;
        setColor(color);
        setMSide(uMov);
        move(walls);

        mVelY += ENT_VEL;
        success = true;

    }
    return success;
}

bool Ghost::moveDown(Wall& walls)
{
    bool success = false;
    int mVelX2 = 0, mVelY2 = 0;
    mVelY2 += ENT_VEL;

    mPosX += mVelX2;
    mBox.x = mPosX;
    mPosY += mVelY2;
    mBox.y = mPosY;

    if (walls.touchesWall(mBox))
    {

        mPosX -= mVelX2;
        mBox.x = mPosX;
        mPosY -= mVelY2;
        mBox.y = mPosY;

        mVelY2 -= ENT_VEL;
        success = false;

    }

    else
    {

        mPosX -= mVelX2;
        mBox.x = mPosX;
        mPosY -= mVelY2;
        mBox.y = mPosY;

        mVelY2 -= ENT_VEL;
        mVelY += ENT_VEL;
        setColor(color);
        setMSide(dMov);
        move(walls);

        mVelY -= ENT_VEL;
        success = true;

    }
    return success;
}

void Ghost::moveTo(int wPosX, int wPosY, Wall& walls, bool& moved)
{

    if ((mPosX != wPosX) || (mPosY != wPosY))
    {

        if (movXFlagEqYl == 0 && movXFlagEqYm == 0 && movYFlagEqxXm == 0 && movYFlagEqxXl == 0 && movXFlaglYl == 0 && movXFlaglYm == 0 && movXFlagmYl == 0 && movXFlagmYm == 0 && movXFlagEqYl2 == 0 && movXFlagEqYm2 == 0 && movYFlagEqxXl2 == 0 && movYFlagEqxXm2 == 0)
        {

            if (mPosX < wPosX)
            {

                if (moveRight(walls))
                {
                    goto endmov;
                }

            }

            else if (mPosX > wPosX)
            {

                if (moveLeft(walls))
                {
                    goto endmov;
                }

            }

            if (mPosY < wPosY)
            {

                if (moveDown(walls))
                {
                    goto endmov;
                }

            }

            else if (mPosY > wPosY)
            {

                if (moveUp(walls))
                {
                    goto endmov;
                }

            }

        }

        if ((mPosX == wPosX && mPosY < wPosY) || movXFlagEqYl == 1)
        {
            if (!moveDown(walls))
            {
                if (movXFlagEqYl2 == 1)
                {
                    goto Left;
                }
                if (!moveRight(walls))
                {
                Left:
                    moveLeft(walls);
                    movXFlagEqYl = 1;
                    movXFlagEqYl2 = 1;
                    goto endmov;
                }
                else
                {
                    movXFlagEqYl = 1;
                    goto endmov;
                }
            }
            else
            {
                movXFlagEqYl = 0;
                movXFlagEqYl2 = 0;
                goto endmov;
            }

        }
        else if ((mPosX == wPosX && mPosY > wPosY) || movXFlagEqYm == 1)
        {
            if (!moveUp(walls))
            {
                if (movXFlagEqYm2 == 1)
                {
                    goto Left2;
                }
                if (!moveRight(walls))
                {
                Left2:
                    moveLeft(walls);
                    movXFlagEqYm = 1;
                    movXFlagEqYm2 = 1;
                    goto endmov;
                }
                else
                {
                    movXFlagEqYm = 1;
                    goto endmov;
                }
            }
            else
            {
                movXFlagEqYm = 0;
                movXFlagEqYm2 = 0;
                goto endmov;
            }
        }

        if ((mPosX < wPosX && mPosY == wPosY) || movYFlagEqxXl == 1)
        {
            if (!moveRight(walls))
            {
                if (movYFlagEqxXl2 == 1)
                {
                    goto Down;
                }
                if (!moveUp(walls))
                {
                Down:
                    moveDown(walls);
                    movYFlagEqxXl = 1;
                    movYFlagEqxXl2 = 1;
                    goto endmov;
                }
                else
                {
                    movYFlagEqxXl = 1;
                    goto endmov;
                }
            }
            else
            {
                movYFlagEqxXl = 0;
                movYFlagEqxXl2 = 0;
                goto endmov;
            }
        }
        else if ((mPosX > wPosX && mPosY == wPosY) || movYFlagEqxXm == 1)
        {
            if (!moveLeft(walls))
            {
                if (movYFlagEqxXm2 == 1)
                {
                    goto Down2;
                }
                if (!moveUp(walls))
                {
                Down2:
                    moveDown(walls);
                    movYFlagEqxXm = 1;
                    movYFlagEqxXm2 = 1;
                    goto endmov;
                }
                else
                {
                    movYFlagEqxXm = 1;
                    goto endmov;
                }
            }
            else
            {
                movYFlagEqxXm = 0;
                movYFlagEqxXm2 = 0;
                goto endmov;
            }
        }

        if ((mPosX < wPosX && mPosY < wPosY) || movXFlaglYl == 1)
        {
            if (movXFlaglYl != 1)
            {
                if (!moveRight(walls))
                {
                    movXFlaglYl = 1;
                    goto endmov;
                }
                else
                {
                    movXFlaglYl = 0;
                    goto endmov;
                }
            }

            if (!moveDown(walls))
            {
                moveLeft(walls);
                movXFlaglYl = 1;
                goto endmov;
            }
            else
            {
                movXFlaglYl = 0;
                goto endmov;
            }
        }
        else if ((mPosX < wPosX && mPosY > wPosY) || movXFlaglYm == 1)
        {
            if (movXFlaglYm != 1)
            {
                if (!moveRight(walls))
                {
                    movXFlaglYm = 1;
                    goto endmov;
                }
                else
                {
                    movXFlaglYm = 0;
                    goto endmov;
                }
            }

            if (!moveUp(walls))
            {
                moveLeft(walls);
                movXFlaglYm = 1;
                goto endmov;
            }
            else
            {
                movXFlaglYm = 0;
                goto endmov;
            }
        }

        if ((mPosX > wPosX && mPosY < wPosY) || movXFlagmYl == 1)
        {
            if (movXFlagmYl != 1)
            {
                if (!moveLeft(walls))
                {
                    movXFlagmYl = 1;
                    goto endmov;
                }
                else
                {
                    movXFlagmYl = 0;
                    goto endmov;
                }
            }

            if (!moveDown(walls))
            {
                moveRight(walls);
                movXFlagmYl = 1;
                goto endmov;
            }
            else
            {
                movXFlagmYl = 0;
                goto endmov;
            }
        }
        else if ((mPosX > wPosX && mPosY > wPosY) || movXFlagmYm == 1)
        {
            if (movXFlagmYm != 1)
            {
                if (!moveLeft(walls))
                {
                    movXFlagmYm = 1;
                    goto endmov;
                }
                else
                {
                    movXFlagmYm = 0;
                    goto endmov;
                }
            }

            if (!moveUp(walls))
            {
                moveRight(walls);
                movXFlagmYm = 1;
                goto endmov;
            }
            else
            {
                movXFlagmYm = 0;
                goto endmov;
            }
        }
    }

endmov:
    if (((mPosX >= wPosX - 16) || (mPosX <= wPosX + 16)) && mPosY == wPosY)
    {
        if (moved == false)
        {
            moved = true;
        }
        else
        {
            moved = false;
        }
    }
    return;

}


void Ghost::move(Wall& walls)
{

    mPosX += mVelX;
    mBox.x = mPosX;
    mPosY += mVelY;
    mBox.y = mPosY;

    boundsCollision();

    if (walls.touchesWall(mBox))
    {

        mPosX -= mVelX;
        mBox.x = mPosX;
        mPosY -= mVelY;
        mBox.y = mPosY;

    }

}

void Ghost::AnimMov(AppInit& app)
{

    setCurrentClip();

    render(app);
    ++frame;

    if (frame / 4 >= MOVFRAMES)
    {
        frame = 0;
    }

}

void Ghost::render(AppInit& app)
{
    gGhostTex->render(mPosX, mPosY, app, currentClip);
}

void Ghost::setGSprites(Uint8 color)
{

    switch (color)
    {
    case Red:
    {
        gGhostMov[Red][rMov][0].x = 1;
        gGhostMov[Red][rMov][0].y = 1;
        gGhostMov[Red][rMov][0].w = 16;
        gGhostMov[Red][rMov][0].h = 16;

        gGhostMov[Red][rMov][1].x = 18;
        gGhostMov[Red][rMov][1].y = 1;
        gGhostMov[Red][rMov][1].w = 16;
        gGhostMov[Red][rMov][1].h = 16;

        gGhostMov[Red][dMov][0].x = 35;
        gGhostMov[Red][dMov][0].y = 1;
        gGhostMov[Red][dMov][0].w = 16;
        gGhostMov[Red][dMov][0].h = 16;

        gGhostMov[Red][dMov][1].x = 52;
        gGhostMov[Red][dMov][1].y = 1;
        gGhostMov[Red][dMov][1].w = 16;
        gGhostMov[Red][dMov][1].h = 16;

        gGhostMov[Red][lMov][0].x = 69;
        gGhostMov[Red][lMov][0].y = 1;
        gGhostMov[Red][lMov][0].w = 16;
        gGhostMov[Red][lMov][0].h = 16;

        gGhostMov[Red][lMov][1].x = 86;
        gGhostMov[Red][lMov][1].y = 1;
        gGhostMov[Red][lMov][1].w = 16;
        gGhostMov[Red][lMov][1].h = 16;

        gGhostMov[Red][uMov][0].x = 103;
        gGhostMov[Red][uMov][0].y = 1;
        gGhostMov[Red][uMov][0].w = 16;
        gGhostMov[Red][uMov][0].h = 16;

        gGhostMov[Red][uMov][1].x = 120;
        gGhostMov[Red][uMov][1].y = 1;
        gGhostMov[Red][uMov][1].w = 16;
        gGhostMov[Red][uMov][1].h = 16;

        break;
    }
    case Blue:
    {
        gGhostMov[Blue][rMov][0].x = 1;
        gGhostMov[Blue][rMov][0].y = 18;
        gGhostMov[Blue][rMov][0].w = 16;
        gGhostMov[Blue][rMov][0].h = 16;

        gGhostMov[Blue][rMov][1].x = 18;
        gGhostMov[Blue][rMov][1].y = 18;
        gGhostMov[Blue][rMov][1].w = 16;
        gGhostMov[Blue][rMov][1].h = 16;

        gGhostMov[Blue][dMov][0].x = 35;
        gGhostMov[Blue][dMov][0].y = 18;
        gGhostMov[Blue][dMov][0].w = 16;
        gGhostMov[Blue][dMov][0].h = 16;

        gGhostMov[Blue][dMov][1].x = 52;
        gGhostMov[Blue][dMov][1].y = 18;
        gGhostMov[Blue][dMov][1].w = 16;
        gGhostMov[Blue][dMov][1].h = 16;

        gGhostMov[Blue][lMov][0].x = 69;
        gGhostMov[Blue][lMov][0].y = 18;
        gGhostMov[Blue][lMov][0].w = 16;
        gGhostMov[Blue][lMov][0].h = 16;

        gGhostMov[Blue][lMov][1].x = 86;
        gGhostMov[Blue][lMov][1].y = 18;
        gGhostMov[Blue][lMov][1].w = 16;
        gGhostMov[Blue][lMov][1].h = 16;

        gGhostMov[Blue][uMov][0].x = 103;
        gGhostMov[Blue][uMov][0].y = 18;
        gGhostMov[Blue][uMov][0].w = 16;
        gGhostMov[Blue][uMov][0].h = 16;

        gGhostMov[Blue][uMov][1].x = 120;
        gGhostMov[Blue][uMov][1].y = 18;
        gGhostMov[Blue][uMov][1].w = 16;
        gGhostMov[Blue][uMov][1].h = 16;

        break;
    }
    case Yellow:
    {
        gGhostMov[Yellow][rMov][0].x = 1;
        gGhostMov[Yellow][rMov][0].y = 35;
        gGhostMov[Yellow][rMov][0].w = 16;
        gGhostMov[Yellow][rMov][0].h = 16;

        gGhostMov[Yellow][rMov][1].x = 18;
        gGhostMov[Yellow][rMov][1].y = 35;
        gGhostMov[Yellow][rMov][1].w = 16;
        gGhostMov[Yellow][rMov][1].h = 16;

        gGhostMov[Yellow][dMov][0].x = 35;
        gGhostMov[Yellow][dMov][0].y = 35;
        gGhostMov[Yellow][dMov][0].w = 16;
        gGhostMov[Yellow][dMov][0].h = 16;

        gGhostMov[Yellow][dMov][1].x = 52;
        gGhostMov[Yellow][dMov][1].y = 35;
        gGhostMov[Yellow][dMov][1].w = 16;
        gGhostMov[Yellow][dMov][1].h = 16;

        gGhostMov[Yellow][lMov][0].x = 69;
        gGhostMov[Yellow][lMov][0].y = 35;
        gGhostMov[Yellow][lMov][0].w = 16;
        gGhostMov[Yellow][lMov][0].h = 16;

        gGhostMov[Yellow][lMov][1].x = 86;
        gGhostMov[Yellow][lMov][1].y = 35;
        gGhostMov[Yellow][lMov][1].w = 16;
        gGhostMov[Yellow][lMov][1].h = 16;

        gGhostMov[Yellow][uMov][0].x = 103;
        gGhostMov[Yellow][uMov][0].y = 35;
        gGhostMov[Yellow][uMov][0].w = 16;
        gGhostMov[Yellow][uMov][0].h = 16;

        gGhostMov[Yellow][uMov][1].x = 120;
        gGhostMov[Yellow][uMov][1].y = 35;
        gGhostMov[Yellow][uMov][1].w = 16;
        gGhostMov[Yellow][uMov][1].h = 16;

        break;
    }
    case Pink:
    {
        gGhostMov[Pink][rMov][0].x = 1;
        gGhostMov[Pink][rMov][0].y = 52;
        gGhostMov[Pink][rMov][0].w = 16;
        gGhostMov[Pink][rMov][0].h = 16;

        gGhostMov[Pink][rMov][1].x = 18;
        gGhostMov[Pink][rMov][1].y = 52;
        gGhostMov[Pink][rMov][1].w = 16;
        gGhostMov[Pink][rMov][1].h = 16;

        gGhostMov[Pink][dMov][0].x = 35;
        gGhostMov[Pink][dMov][0].y = 52;
        gGhostMov[Pink][dMov][0].w = 16;
        gGhostMov[Pink][dMov][0].h = 16;

        gGhostMov[Pink][dMov][1].x = 52;
        gGhostMov[Pink][dMov][1].y = 52;
        gGhostMov[Pink][dMov][1].w = 16;
        gGhostMov[Pink][dMov][1].h = 16;

        gGhostMov[Pink][lMov][0].x = 69;
        gGhostMov[Pink][lMov][0].y = 52;
        gGhostMov[Pink][lMov][0].w = 16;
        gGhostMov[Pink][lMov][0].h = 16;

        gGhostMov[Pink][lMov][1].x = 86;
        gGhostMov[Pink][lMov][1].y = 52;
        gGhostMov[Pink][lMov][1].w = 16;
        gGhostMov[Pink][lMov][1].h = 16;

        gGhostMov[Pink][uMov][0].x = 103;
        gGhostMov[Pink][uMov][0].y = 52;
        gGhostMov[Pink][uMov][0].w = 16;
        gGhostMov[Pink][uMov][0].h = 16;

        gGhostMov[Pink][uMov][1].x = 120;
        gGhostMov[Pink][uMov][1].y = 52;
        gGhostMov[Pink][uMov][1].w = 16;
        gGhostMov[Pink][uMov][1].h = 16;

        break;
    }
    }

    gGhostMov[Dead][rMov][0].x = 1;
    gGhostMov[Dead][rMov][0].y = 69;
    gGhostMov[Dead][rMov][0].w = 16;
    gGhostMov[Dead][rMov][0].h = 16;

    gGhostMov[Dead][rMov][1].x = 18;
    gGhostMov[Dead][rMov][1].y = 69;
    gGhostMov[Dead][rMov][1].w = 16;
    gGhostMov[Dead][rMov][1].h = 16;

    gGhostMov[Dead][dMov][0].x = 35;
    gGhostMov[Dead][dMov][0].y = 69;
    gGhostMov[Dead][dMov][0].w = 16;
    gGhostMov[Dead][dMov][0].h = 16;

    gGhostMov[Dead][dMov][1].x = 52;
    gGhostMov[Dead][dMov][1].y = 69;
    gGhostMov[Dead][dMov][1].w = 16;
    gGhostMov[Dead][dMov][1].h = 16;

    gGhostMov[Dead][lMov][0].x = 69;
    gGhostMov[Dead][lMov][0].y = 69;
    gGhostMov[Dead][lMov][0].w = 16;
    gGhostMov[Dead][lMov][0].h = 16;

    gGhostMov[Dead][lMov][1].x = 86;
    gGhostMov[Dead][lMov][1].y = 69;
    gGhostMov[Dead][lMov][1].w = 16;
    gGhostMov[Dead][lMov][1].h = 16;

    gGhostMov[Dead][uMov][0].x = 103;
    gGhostMov[Dead][uMov][0].y = 69;
    gGhostMov[Dead][uMov][0].w = 16;
    gGhostMov[Dead][uMov][0].h = 16;

    gGhostMov[Dead][uMov][1].x = 120;
    gGhostMov[Dead][uMov][1].y = 69;
    gGhostMov[Dead][uMov][1].w = 16;
    gGhostMov[Dead][uMov][1].h = 16;


    gGhostMov[Vuln][rMov][0].x = 1;
    gGhostMov[Vuln][rMov][0].y = 86;
    gGhostMov[Vuln][rMov][0].w = 16;
    gGhostMov[Vuln][rMov][0].h = 16;

    gGhostMov[Vuln][rMov][1].x = 18;
    gGhostMov[Vuln][rMov][1].y = 86;
    gGhostMov[Vuln][rMov][1].w = 16;
    gGhostMov[Vuln][rMov][1].h = 16;

    gGhostMov[Vuln][dMov][0].x = 35;
    gGhostMov[Vuln][dMov][0].y = 86;
    gGhostMov[Vuln][dMov][0].w = 16;
    gGhostMov[Vuln][dMov][0].h = 16;

    gGhostMov[Vuln][dMov][1].x = 52;
    gGhostMov[Vuln][dMov][1].y = 86;
    gGhostMov[Vuln][dMov][1].w = 16;
    gGhostMov[Vuln][dMov][1].h = 16;

    gGhostMov[Vuln][lMov][0].x = 69;
    gGhostMov[Vuln][lMov][0].y = 86;
    gGhostMov[Vuln][lMov][0].w = 16;
    gGhostMov[Vuln][lMov][0].h = 16;

    gGhostMov[Vuln][lMov][1].x = 86;
    gGhostMov[Vuln][lMov][1].y = 86;
    gGhostMov[Vuln][lMov][1].w = 16;
    gGhostMov[Vuln][lMov][1].h = 16;

    gGhostMov[Vuln][uMov][0].x = 103;
    gGhostMov[Vuln][uMov][0].y = 86;
    gGhostMov[Vuln][uMov][0].w = 16;
    gGhostMov[Vuln][uMov][0].h = 16;

    gGhostMov[Vuln][uMov][1].x = 120;
    gGhostMov[Vuln][uMov][1].y = 86;
    gGhostMov[Vuln][uMov][1].w = 16;
    gGhostMov[Vuln][uMov][1].h = 16;

}