#pragma once
#include "file.h"
#include "button.h"

class Menu:public File, public Button
{

private:
    TTF_Font* Fonts[TOTALFONTS];

    LTexture* gLogoTex;
    LTexture* gPButtonTextTex;
    LTexture* gLeaderTextTex;
    LTexture* gInfoTextTex;
    LTexture* gExitTextTex;
    LTexture* gClearScoresTextTex;
    LTexture* informTextTex;
    LTexture* gInputTextTex;
    LTexture* gEnterNameTextTex;
    LTexture* gBackTextTex;
    LTexture* gContTextTex;
    LTexture* gWarnSignTextTex;
    LTexture* gLBoardListTextTex;

    std::stringstream* lBNodeText;

protected:
    Uint8 menuState;
    std::string inputName;
    Button *gButtons = new Button[4]();
    Button *gBack = new Button();

public:
    Menu(AppInit&);
    ~Menu();
	void mainMenu(SDL_Event&, AppInit&);
    void setState(Uint8);
    Uint8 getState();
    std::string getName();
	void plname(SDL_Event&, AppInit&, bool&);
	void leaderboard(SDL_Event&, AppInit&, struct list*&, bool&, int);
    void inform(SDL_Event&, AppInit&, bool&);
    void loadMedia(AppInit&app);
    enum MenuState
    {
        Main=0,
        Play=1,
        Leaderboard=2,
        Info=3,
        Exit=4
    };

};
