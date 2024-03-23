#pragma once
#include "entity.h"
#include "texture.h"
#include "SDL2/include/SDL.h"

class Wall:public Entity
{

private:
    static const int WALL_WIDTH = 8;
    static const int WALL_HEIGHT = 8;
    static const int TOTAL_WALLS = 1530;
    static const int TOTAL_WALL_SPRITES = 25;
    Wall** walls;

    LTexture* gWallTex;
    SDL_Rect gWall[TOTAL_WALL_SPRITES]{ 0,0,0,0 };  

    enum WALLTYPE
    {
        TOPLEFT = 0,
        TOPMID = 1,
        TOPRIGHT = 2,
        MIDLEFT = 3,
        MIDRIGHT = 4,
        LOWLEFT = 5,
        LOWMID = 6,
        LOWRIGHT = 7,
        VOIDMIDM = 12,
        LEFTDOWN_CORNER = 21,
        RIGHTDOWN_CORNER = 22,
        LEFTDOWN_UPCORNER = 23,
        RIGHTDOWN_UPCORNER = 24
    };

protected:
	int mType;

public:
    Wall();
    Wall(AppInit&);
    Wall(int x, int y, int wallType, LTexture*,SDL_Rect*);
    ~Wall();
	void render(AppInit&) override;
	virtual int getType();
    int getBoxX();
    int getBoxY();
    bool touchesWall(SDL_Rect);
    void setWalls();
    void loadMedia(AppInit&);
    void renderWalls(AppInit&);
    void remove_objects() override;
};
