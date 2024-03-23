#include "wall.h"
#include <fstream>

Wall::Wall()
{
    this->objType = UNDEFINED;
}

Wall::Wall(AppInit& app)
{
    loadMedia(app);

    walls = new Wall * [TOTAL_WALLS];
    setWalls();

    this->objType = MAIN;
}

Wall::Wall(int x, int y, int wallType, LTexture* gWallTex, SDL_Rect* gWall)
{
    this->gWallTex = gWallTex;
    for (int i = 0; i < TOTAL_WALL_SPRITES; i++)
    {
        this->gWall[i] = gWall[i];
    }

    this->mBox.x = x;
    this->mBox.y = y;

    this->mBox.w = WALL_WIDTH;
    this->mBox.h = WALL_HEIGHT;

    this->mType = wallType;
    this->objType = SUB;
}

Wall::~Wall()
{
    if (objType == MAIN && gWallTex != nullptr)
    {
        gWallTex->~LTexture();
        delete gWallTex;
        gWallTex = nullptr;
    }
}

void Wall::renderWalls(AppInit& app)
{
    for (int i = 0; i < TOTAL_WALLS; i++)
    {
        walls[i]->render(app);
    }
}

void Wall::remove_objects()
{
    for (int i = 0; i < TOTAL_WALLS; i++)
    {
        if (walls != nullptr)
        {
            if (walls[i] != nullptr)
            {
                walls[i]->~Wall();
                delete walls[i];
                walls[i] = nullptr;
            }
        }
    }
    delete[] walls;
    walls = nullptr;
}

void Wall::loadMedia(AppInit& app)
{
    gWallTex = new LTexture();
    gWallTex->loadFromFile("res/sprites/wall.png", app);
}

void Wall::render(AppInit& app)
{
    gWallTex->render(mBox.x, mBox.y, app, &gWall[mType]);
}

int Wall::getType()
{
    return mType;
}

int Wall::getBoxX()
{
    return mBox.x;
}

int Wall::getBoxY()
{
    return mBox.y;
}

void Wall::setWalls()
{
    gWall[TOPLEFT].x = 1;
    gWall[TOPLEFT].y = 1;
    gWall[TOPLEFT].w = WALL_WIDTH;
    gWall[TOPLEFT].h = WALL_HEIGHT;

    gWall[TOPMID].x = 10;
    gWall[TOPMID].y = 1;
    gWall[TOPMID].w = WALL_WIDTH;
    gWall[TOPMID].h = WALL_HEIGHT;

    gWall[TOPRIGHT].x = 19;
    gWall[TOPRIGHT].y = 1;
    gWall[TOPRIGHT].w = WALL_WIDTH;
    gWall[TOPRIGHT].h = WALL_HEIGHT;

    gWall[MIDLEFT].x = 1;
    gWall[MIDLEFT].y = 10;
    gWall[MIDLEFT].w = WALL_WIDTH;
    gWall[MIDLEFT].h = WALL_HEIGHT;

    gWall[MIDRIGHT].x = 19;
    gWall[MIDRIGHT].y = 10;
    gWall[MIDRIGHT].w = WALL_WIDTH;
    gWall[MIDRIGHT].h = WALL_HEIGHT;

    gWall[LOWLEFT].x = 1;
    gWall[LOWLEFT].y = 19;
    gWall[LOWLEFT].w = WALL_WIDTH;
    gWall[LOWLEFT].h = WALL_HEIGHT;

    gWall[LOWMID].x = 10;
    gWall[LOWMID].y = 19;
    gWall[LOWMID].w = WALL_WIDTH;
    gWall[LOWMID].h = WALL_HEIGHT;

    gWall[LOWRIGHT].x = 19;
    gWall[LOWRIGHT].y = 19;
    gWall[LOWRIGHT].w = WALL_WIDTH;
    gWall[LOWRIGHT].h = WALL_HEIGHT;

    gWall[VOIDMIDM].x = 37;
    gWall[VOIDMIDM].y = 10;
    gWall[VOIDMIDM].w = WALL_WIDTH;
    gWall[VOIDMIDM].h = WALL_HEIGHT;

    gWall[LEFTDOWN_CORNER].x = 28;
    gWall[LEFTDOWN_CORNER].y = 28;
    gWall[LEFTDOWN_CORNER].w = WALL_WIDTH;
    gWall[LEFTDOWN_CORNER].h = WALL_HEIGHT;

    gWall[RIGHTDOWN_CORNER].x = 37;
    gWall[RIGHTDOWN_CORNER].y = 28;
    gWall[RIGHTDOWN_CORNER].w = WALL_WIDTH;
    gWall[RIGHTDOWN_CORNER].h = WALL_HEIGHT;

    gWall[LEFTDOWN_UPCORNER].x = 28;
    gWall[LEFTDOWN_UPCORNER].y = 37;
    gWall[LEFTDOWN_UPCORNER].w = WALL_WIDTH;
    gWall[LEFTDOWN_UPCORNER].h = WALL_HEIGHT;

    gWall[RIGHTDOWN_UPCORNER].x = 37;
    gWall[RIGHTDOWN_UPCORNER].y = 37;
    gWall[RIGHTDOWN_UPCORNER].w = WALL_WIDTH;
    gWall[RIGHTDOWN_UPCORNER].h = WALL_HEIGHT;

    int x = BOUNDS_X, y = BOUNDS_Y;

    std::ifstream map("res/map/map.txt");

    for (int i = 0; i < TOTAL_WALLS; ++i)
    {
        int wallType = -1;

        map >> wallType;
        walls[i] = new Wall(x, y, wallType, gWallTex, gWall);

        x += WALL_WIDTH;

        if (x >= BOUNDS_WIDTH)
        {
            x = BOUNDS_X;

            y += WALL_HEIGHT;
        }
    }

    map.close();
}

bool Wall::touchesWall(SDL_Rect box)
{
    for (int i = 0; i < TOTAL_WALLS; ++i)
    {
        if (walls[i]->getType() != VOIDMIDM)
        {
            if (checkCollision(box, walls[i]->getBox()))
            {
                return true;
            }
        }
    }

    return false;
}