#pragma once
#include "SDL2/include/SDL.h"
#include "init.h"
#include "texture.h"

class Entity:public LTexture
{

protected:
	int mPosX, mPosY;
	int mVelX, mVelY;
	static const int ENT_VEL = 1;

	static const int MOVFRAMES = 2;
	SDL_Rect* currentClip;
	Uint8 side;
	Uint8 frame;

	bool isColliding;
	SDL_Rect mBox;

	enum ObjType
	{
		MAIN = 0,
		SUB = 1,
		UNDEFINED = 2
	};
	Uint8 objType;

public:
	Entity();
	virtual void render(AppInit&) = 0;
	void setPos(int, int);
	void setVel(int, int);
	int getPosX();
	int getPosY();
	SDL_Rect& getBox();
	bool getIsColliding();
	bool checkCollision(SDL_Rect,SDL_Rect);
	void boundsCollision();
	virtual void remove_objects() = 0;

};
