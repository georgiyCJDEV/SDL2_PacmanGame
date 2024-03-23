#pragma once
#include "SDL2_mixer/include/SDL_mixer.h"
#include "SDL2_ttf/include/SDL_ttf.h"

class AppInit
{

private:
	TTF_Font* gFont6pt;
	TTF_Font* gFont7pt;
	TTF_Font* gFont8pt;
	TTF_Font* gFont9pt;
	TTF_Font* gFont10pt;
	TTF_Font* gFont14pt;

	Mix_Music* wakaWaka;
	Mix_Music* startRound;
	Mix_Music* playerDeath;

	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;

protected:
	static const Uint8 TOTALFONTS = 6;
	TTF_Font* fonts[TOTALFONTS]{ nullptr };
	static const Uint8 TOTALSOUNDS = 3;
	Mix_Music* sounds[TOTALSOUNDS]{ nullptr };

	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;

	static const int LEVEL_WIDTH = 272;
	static const int LEVEL_HEIGHT = 360;

	static const int BOUNDS_X = (((SCREEN_WIDTH) / 2) / 2);
	static const int BOUNDS_Y = ((((SCREEN_HEIGHT) / 2) / 2) / 2);
	static const int BOUNDS_WIDTH = ((((SCREEN_WIDTH) / 2) / 2) + LEVEL_WIDTH);
	static const int BOUNDS_HEIGHT = (((((SCREEN_HEIGHT) / 2) / 2) / 2) + LEVEL_HEIGHT);

	enum Fonts
	{
		PT6=0,
		PT7=1,
		PT8=2,
		PT9=3,
		PT10=4,
		PT14=5
	};

	enum Sounds
	{
		MOVE=0,
		START=1,
		DEATH=2
	};

public:
	AppInit();
	~AppInit();
	void Init();
	void setFonts();
	void setSounds();
	SDL_Renderer* getRenderer();
	TTF_Font** getFonts();
	Mix_Music** getSounds();
	int getBounds_x();
	int getBounds_y();
	void close();
};
