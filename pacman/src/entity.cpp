#include "entity.h"

Entity::Entity()
{
	this->mPosX = 0;
	this->mPosY = 0;
	this->mVelX = 0;
	this->mVelY = 0;
	this->mBox.x = 0;
	this->mBox.y = 0;
	this->mBox.w = 16;
	this->mBox.h = 16;
	this->isColliding = false;
	this->currentClip = new SDL_Rect;
}

SDL_Rect& Entity::getBox()
{
	return mBox;
}

void Entity::setPos(int posXvalue, int posYvalue)
{
	mPosX = posXvalue;
	mPosY = posYvalue;
}

void Entity::setVel(int velXvalue, int velYvalue)
{
	mVelX = velXvalue;
	mVelY = velYvalue;
}

int Entity::getPosX()
{
	return mPosX;
}

int Entity::getPosY()
{
	return mPosY;
}


bool Entity::getIsColliding()
{
	return isColliding;
}

bool Entity::checkCollision(SDL_Rect a, SDL_Rect b)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}

void Entity::boundsCollision()
{
	if (mPosX + 16 > BOUNDS_WIDTH)
	{
		mPosX = BOUNDS_X;
		mBox.x = mPosX;
	}
	else if (mPosX < BOUNDS_X)
	{
		mPosX = BOUNDS_WIDTH - 16;
		mBox.x = mPosX;
	}

	if (mPosY + 16 > BOUNDS_HEIGHT)
	{
		mPosY = BOUNDS_Y + 16;
		mBox.y = mPosY;
	}
	else if (mPosY < BOUNDS_Y)
	{
		mPosY = BOUNDS_HEIGHT - 16;
		mBox.y = mPosY;
	}
}
