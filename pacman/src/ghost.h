#pragma once
#include "wall.h"

class Ghost: public Entity
{

private:
    static const Uint8 TOTAL_GHOSTS = 4;
    Uint8 ghostType;
    Ghost** ghosts;

    LTexture *gGhostTex;
    SDL_Rect gGhostMov[6][4][MOVFRAMES]{ 0,0,0,0 };

protected:
    int movXFlagEqYl;
    int movXFlagEqYl2;
    int movXFlagEqYm;
    int movXFlagEqYm2;
    int movYFlagEqxXl;
    int movYFlagEqxXl2;
    int movYFlagEqxXm;
    int movYFlagEqxXm2;
    int movXFlaglYl;
    int movXFlaglYm;
    int movXFlagmYl;
    int movXFlagmYm;

    Uint8 color;

public:
    Ghost();
    Ghost(AppInit&);
    Ghost(Uint16, Uint16, Uint8, LTexture*);
    ~Ghost();
    Ghost** getGhosts();
    void setGhosts();
    void remove_objects() override;
    void renderGhosts(AppInit&);
    void moveTo(int wPosX, int wPosY, Wall& walls, bool&);
	void move(Wall& walls);
    void setColor(int);
    Uint8& getColor();
    void setMSide(int);
    void setFlags(int, int, int, int, int, int, int, int, int, int, int, int);
    void setCurrentClip();
    void AnimMov(AppInit&);
    void render(AppInit&) override;
    bool moveLeft(Wall& walls);
    bool moveRight(Wall& walls);
    bool moveDown(Wall& walls);
    bool moveUp(Wall& walls);
    void setBox(int, int);
    void loadMedia(AppInit&);
    void setGSprites(Uint8 color);

    enum Color
    {
        Red = 0,
        Blue = 1,
        Yellow = 2,
        Pink = 3,
        Dead = 4,
        Vuln = 5
    };

    enum sideMov
    {
        rMov = 0,
        dMov = 1,
        lMov = 2,
        uMov = 3
    };

};
