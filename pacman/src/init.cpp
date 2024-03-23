#include "init.h"
#include "SDL2/include/SDL.h"
#include "SDL2_image/include/SDL_image.h"

AppInit::AppInit()
{
	gWindow = nullptr;
	gRenderer = nullptr;

	gFont6pt = nullptr;
	gFont7pt = nullptr;
	gFont8pt = nullptr;
	gFont9pt = nullptr;
	gFont10pt = nullptr;
	gFont14pt = nullptr;

	wakaWaka = nullptr;
	startRound = nullptr;
	playerDeath = nullptr;
}

AppInit::~AppInit()
{
}

void AppInit::Init()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
	gWindow = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	//SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);

	setFonts();
	setSounds();
}

void AppInit::setFonts()
{
	TTF_Init();
	gFont6pt = TTF_OpenFont("res/fonts/emulogic.ttf", 6);
	gFont7pt = TTF_OpenFont("res/fonts/emulogic.ttf", 7);
	gFont8pt = TTF_OpenFont("res/fonts/emulogic.ttf", 8);
	gFont9pt = TTF_OpenFont("res/fonts/emulogic.ttf", 9);
	gFont10pt = TTF_OpenFont("res/fonts/emulogic.ttf", 10);
	gFont14pt = TTF_OpenFont("res/fonts/emulogic.ttf", 14);
}

void AppInit::setSounds()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	wakaWaka = Mix_LoadMUS("res/sounds/pacman_chomp.wav");
	startRound = Mix_LoadMUS("res/sounds/start.wav");
	playerDeath = Mix_LoadMUS("res/sounds/death.wav");
}

SDL_Renderer* AppInit::getRenderer()
{
	return gRenderer;
}

TTF_Font** AppInit::getFonts()
{
	fonts[0] = gFont6pt;
	fonts[1] = gFont7pt;
	fonts[2] = gFont8pt;
	fonts[3] = gFont9pt;
	fonts[4] = gFont10pt;
	fonts[5] = gFont14pt;

	return fonts;
}

Mix_Music** AppInit::getSounds()
{
	sounds[0] = wakaWaka;
	sounds[1] = startRound;
	sounds[2] = playerDeath;

	return sounds;
}

int AppInit::getBounds_x()
{
	return BOUNDS_X;
}

int AppInit::getBounds_y()
{
	return BOUNDS_Y;
}

void AppInit::close()
{

	TTF_CloseFont(gFont6pt);
	gFont6pt = nullptr;

	TTF_CloseFont(gFont7pt);
	gFont7pt = nullptr;

	TTF_CloseFont(gFont8pt);
	gFont8pt = nullptr;

	TTF_CloseFont(gFont9pt);
	gFont9pt = nullptr;

	TTF_CloseFont(gFont10pt);
	gFont10pt = nullptr;

	TTF_CloseFont(gFont14pt);
	gFont14pt = nullptr;

	Mix_FreeMusic(startRound);
	startRound = nullptr;

	Mix_FreeMusic(wakaWaka);
	wakaWaka = nullptr;

	Mix_FreeMusic(playerDeath);
	playerDeath = nullptr;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

}