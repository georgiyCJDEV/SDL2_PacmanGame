#pragma once
#include "timer.h"
#include "ghost.h"

class Points: public Wall
{

private:
    static const int POINTS_WIDTH = 16;
    static const int POINTS_HEIGHT = 16;
    static const int TOTAL_POINTS = 1530;
    static const int TOTAL_POINTS_SPRITES = 3;
    Points** points;

    LTexture *gPointsTex;
    SDL_Rect gPoints[TOTAL_POINTS_SPRITES]{ 0,0,0,0 }; 

    enum POINTSTYPE
    {
        pointS = 0,
        pointL = 1,
        pointVOID = 2,
    };

public:
    Points();
    Points(AppInit&);
    Points(int, int, int,LTexture*,SDL_Rect*);
    ~Points();
    void remove_objects() override;
	void render(AppInit&) override;
    void setType(int);
	int getType() override;
    bool touchesPoint(SDL_Rect, int&);
    bool touchesPoint2(SDL_Rect, int&, Ghost&, LTimer&);
    void setPoints();
    void loadMedia(AppInit&);
    void renderPoints(AppInit&);

};
