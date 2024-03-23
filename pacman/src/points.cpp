#include "points.h"
#include <fstream>

Points::Points()
{
    this->objType = UNDEFINED;
}

Points::Points(AppInit& app)
{
    loadMedia(app);

    points = new Points * [TOTAL_POINTS];
    setPoints();

    this->objType = MAIN;
}

Points::Points(int x, int y, int pointsType, LTexture* gPointsTex, SDL_Rect* gPoints)
{
    this->gPointsTex = gPointsTex;
    for (int i = 0; i < TOTAL_POINTS_SPRITES; i++)
    {
        this->gPoints[i] = gPoints[i];
    }

    mPosX = x;
    mPosY = y;

    mBox.x = mPosX - 8;
    mBox.y = mPosY - 8;

    mBox.w = 16;
    mBox.h = 16;

    mType = pointsType;
    this->objType = SUB;
}

Points::~Points()
{
    if (objType == MAIN && gPointsTex != nullptr)
    {
        gPointsTex->~LTexture();
        delete gPointsTex;
        gPointsTex = nullptr;
    }
}

void Points::renderPoints(AppInit& app)
{
    for (int i = 0; i < TOTAL_POINTS; i++)
    {
        points[i]->render(app);
    }
}

void Points::remove_objects()
{
    for (int i = 0; i < TOTAL_POINTS; i++)
    {
        if (points != nullptr)
        {
            if (points[i] != nullptr)
            {
                points[i]->~Points();
                delete points[i];
                points[i] = nullptr;
            }
        }
    }
    delete[] points;
    points = nullptr;
}

void Points::loadMedia(AppInit& app)
{
    gPointsTex = new LTexture();
    gPointsTex->loadFromFile("res/sprites/points.png", app);
}

void Points::render(AppInit& app)
{
    gPointsTex->render(mPosX, mPosY, app, &gPoints[mType]);
}

int Points::getType()
{
    return mType;
}

void Points::setType(int typevalue)
{
    mType = typevalue;
}

void Points::setPoints()
{
    gPoints[pointS].x = 1;
    gPoints[pointS].y = 1;
    gPoints[pointS].w = POINTS_WIDTH;
    gPoints[pointS].h = POINTS_HEIGHT;

    gPoints[pointL].x = 18;
    gPoints[pointL].y = 1;
    gPoints[pointL].w = POINTS_WIDTH;
    gPoints[pointL].h = POINTS_HEIGHT;

    gPoints[pointVOID].x = 35;
    gPoints[pointVOID].y = 1;
    gPoints[pointVOID].w = POINTS_WIDTH;
    gPoints[pointVOID].h = POINTS_HEIGHT;

    int x = BOUNDS_X, y = BOUNDS_Y;

    std::ifstream map("res/map/map_p.txt");

    for (int i = 0; i < TOTAL_POINTS; ++i)
    {
        int pointsType = -1;

        map >> pointsType;

        points[i] = new Points(x, y, pointsType, gPointsTex, gPoints);

        x += 8;

        if (x >= BOUNDS_WIDTH)
        {
            x = BOUNDS_X;

            y += 8;
        }

    }

    map.close();

}

bool Points::touchesPoint(SDL_Rect box, int& score)
{
    for (int i = 0; i < TOTAL_POINTS; ++i)
    {
        if (checkCollision(box, points[i]->getBox()))
        {
            if (points[i]->getType() == pointS)
            {
                score += 10;
                points[i]->setType(pointVOID);
            }

            return true;
        }
    }
    return false;
}

bool Points::touchesPoint2(SDL_Rect box, int& score, Ghost& ghosts, LTimer& timer)
{
    for (int i = 0; i < TOTAL_POINTS; ++i)
    {
        if (checkCollision(box, points[i]->getBox()))
        {
            if (points[i]->getType() == pointL)
            {
                score += 50;
                points[i]->setType(pointVOID);
                ghosts.getGhosts()[ghosts.Red]->getColor() = 5;
                ghosts.getGhosts()[ghosts.Blue]->getColor() = 5;
                ghosts.getGhosts()[ghosts.Yellow]->getColor() = 5;
                ghosts.getGhosts()[ghosts.Pink]->getColor() = 5;
                timer.start();
            }

            return true;
        }
    }
    return false;
}