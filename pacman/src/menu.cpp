#include "menu.h"
#include <iostream>
#include <sstream>
#include <string>

Menu::Menu(AppInit& app)
{
    for (int i = 0; i < TOTALFONTS; i++)
    {
        Fonts[i] = app.getFonts()[i];
    }

    loadMedia(app);
    this->menuState = Main;

    gButtons[0].setWidth(gPButtonTextTex->getWidth());
    gButtons[0].setHeight(gPButtonTextTex->getHeight());
    gButtons[0].setPosition((SCREEN_WIDTH - gPButtonTextTex->getWidth()) / 2, (int)((SCREEN_HEIGHT - gPButtonTextTex->getHeight()) / 1.6));

    gButtons[1].setWidth(gLeaderTextTex->getWidth());
    gButtons[1].setHeight(gLeaderTextTex->getHeight());
    gButtons[1].setPosition((SCREEN_WIDTH - gLeaderTextTex->getWidth()) / 2, (int)((SCREEN_HEIGHT - gLeaderTextTex->getHeight()) / 1.45));

    gButtons[2].setWidth(gInfoTextTex->getWidth());
    gButtons[2].setHeight(gInfoTextTex->getHeight());
    gButtons[2].setPosition((SCREEN_WIDTH - gLeaderTextTex->getWidth()) / 2, (int)((SCREEN_HEIGHT - gInfoTextTex->getHeight()) / 1.3));

    gButtons[3].setWidth(gExitTextTex->getWidth());
    gButtons[3].setHeight(gExitTextTex->getHeight());
    gButtons[3].setPosition((SCREEN_WIDTH - gExitTextTex->getWidth()) / 2, (int)((SCREEN_HEIGHT - gExitTextTex->getHeight()) / 1.15));

    this->inputName = "Player";
}

Menu::~Menu()
{
    std::cout << "Menu destructor called" << std::endl;

    delete[] gButtons;
    gButtons = nullptr;

    delete gBack;
    gBack = nullptr;

    gLogoTex->~LTexture();
    delete gLogoTex;
    gLogoTex = nullptr;
    gPButtonTextTex->~LTexture();
    delete gPButtonTextTex;
    gPButtonTextTex = nullptr;
    gLeaderTextTex->~LTexture();
    delete gLeaderTextTex;
    gLeaderTextTex = nullptr;
    gInfoTextTex->~LTexture();
    delete gInfoTextTex;
    gInfoTextTex = nullptr;
    gExitTextTex->~LTexture();
    delete gExitTextTex;
    gExitTextTex = nullptr;
    gClearScoresTextTex->~LTexture();
    delete gClearScoresTextTex;
    gClearScoresTextTex = nullptr;
    gInputTextTex->~LTexture();
    delete gInputTextTex;
    gInputTextTex = nullptr;
    gEnterNameTextTex->~LTexture();
    delete gEnterNameTextTex;
    gEnterNameTextTex = nullptr;
    gBackTextTex->~LTexture();
    delete gBackTextTex;
    gBackTextTex = nullptr;
    gContTextTex->~LTexture();
    delete gContTextTex;
    gContTextTex = nullptr;
    gWarnSignTextTex->~LTexture();
    delete gWarnSignTextTex;
    gWarnSignTextTex = nullptr;
    gLBoardListTextTex->~LTexture();
    delete[] gLBoardListTextTex;
    gLBoardListTextTex = nullptr;
    informTextTex->~LTexture();
    delete[] informTextTex;
    informTextTex = nullptr;

    delete[] lBNodeText;

    std::cout << "Menu destructor worked\n" << std::endl;
}

void Menu::loadMedia(AppInit& app)
{
    gLogoTex = new LTexture();
    gPButtonTextTex = new LTexture();
    gLeaderTextTex = new LTexture();
    gInfoTextTex = new LTexture();
    gExitTextTex = new LTexture();
    gClearScoresTextTex = new LTexture();
    informTextTex = new LTexture[12]();
    gInputTextTex = new LTexture();
    gEnterNameTextTex = new LTexture();
    gBackTextTex = new LTexture();
    gContTextTex = new LTexture();
    gWarnSignTextTex = new LTexture();
    gLBoardListTextTex = new LTexture[11]();

    lBNodeText = new std::stringstream[11];

    gLogoTex->loadFromFile("res/sprites/logo.png", app);
    gPButtonTextTex->loadFromRenderedText("Play", { 255,255,255,255 }, *Fonts[PT7], app);
    gLeaderTextTex->loadFromRenderedText("Leaderboard", { 255,255,255,255 }, *Fonts[PT7], app);
    gInfoTextTex->loadFromRenderedText("How to play?", { 255,255,255,255 }, *Fonts[PT7], app);
    gExitTextTex->loadFromRenderedText("Exit", { 255,255,255,255 }, *Fonts[PT7], app);
    gContTextTex->loadFromRenderedText("Press 'Enter' to continue", { 255,255,255,255 }, *Fonts[PT10], app);
    gBackTextTex->loadFromRenderedText("Return to menu", { 255,255,255,255 }, *Fonts[PT10], app);
    gEnterNameTextTex->loadFromRenderedText("Enter your name:", { 255,255,255,255 }, *Fonts[PT10], app);
    gWarnSignTextTex->loadFromRenderedText("Name can't contain more than 20 characters!", { 153,0,0,0 }, *Fonts[PT8], app);
    informTextTex[0].loadFromRenderedText("How to play?", { 255,255,255,255 }, *Fonts[PT10], app);
    informTextTex[1].loadFromRenderedText("1. Use arrow keys to handle", { 255,255,255,255 }, *Fonts[PT8], app);
    informTextTex[2].loadFromRenderedText("pacman movement.", { 255,255,255,255 }, *Fonts[PT8], app);
    informTextTex[3].loadFromRenderedText("2. Avoid hitting the ghosts.", { 255,255,255,255 }, *Fonts[PT8], app);
    informTextTex[4].loadFromRenderedText("3. Collect as much points", { 255,255,255,255 }, *Fonts[PT8], app);
    informTextTex[5].loadFromRenderedText("as you can.", { 255,255,255,255 }, *Fonts[PT8], app);
    informTextTex[6].loadFromRenderedText("4. Collecting big point", { 255,255,255,255 }, *Fonts[PT8], app);
    informTextTex[7].loadFromRenderedText("allows you to eat ghosts for 7s.", { 255,255,255,255 }, *Fonts[PT8], app);
    informTextTex[8].loadFromRenderedText("5. If you eat ghost you'll", { 255,255,255,255 }, *Fonts[PT8], app);
    informTextTex[9].loadFromRenderedText("receive some points.", { 255,255,255,255 }, *Fonts[PT8], app);
    informTextTex[10].loadFromRenderedText("6. If you'll lose all 3 lives", { 255,255,255,255 }, *Fonts[PT8], app);
    informTextTex[11].loadFromRenderedText("the game will end.", { 255,255,255,255 }, *Fonts[PT8], app);
}

std::string Menu::getName()
{
    return inputName;
}

Uint8 Menu::getState()
{
    return menuState;
}

void Menu::setState(Uint8 menuState)
{
    this->menuState = menuState;
}

void Menu::mainMenu(SDL_Event& e, AppInit& app)
{
    int menuState;
    SDL_SetRenderDrawColor(app.getRenderer(), 0, 0, 0, 0);
    SDL_RenderClear(app.getRenderer());

    for (int i = 0; i < 4; i++)
    {
        menuState = gButtons[i].handleEvent(e, app, i);
        switch (menuState)
        {
        case -1:
            break;
        case 0:
            this->menuState = Play;
            break;
        case 1:
            this->menuState = Leaderboard;
            break;
        case 2:
            this->menuState = Info;
            break;
        case 3:
            this->menuState = Exit;
            break;
        }
    }

    gLogoTex->render((SCREEN_WIDTH - gLogoTex->getWidth()) / 2, int(SCREEN_HEIGHT - gLogoTex->getHeight()) / 4, app);
    gPButtonTextTex->render((SCREEN_WIDTH - gPButtonTextTex->getWidth()) / 2, int((SCREEN_HEIGHT - gPButtonTextTex->getHeight()) / 1.6), app);
    gLeaderTextTex->render((SCREEN_WIDTH - gLeaderTextTex->getWidth()) / 2, (int)((SCREEN_HEIGHT - gLeaderTextTex->getHeight()) / 1.45), app);
    gInfoTextTex->render((SCREEN_WIDTH - gLeaderTextTex->getWidth()) / 2, (int)((SCREEN_HEIGHT - gInfoTextTex->getHeight()) / 1.3), app);
    gExitTextTex->render((SCREEN_WIDTH - gExitTextTex->getWidth()) / 2, (int)((SCREEN_HEIGHT - gExitTextTex->getHeight()) / 1.15), app);

    SDL_RenderPresent(app.getRenderer());
}



void Menu::plname(SDL_Event& e, AppInit& app, bool& quit)
{
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF, 0xFF };

    gInputTextTex->loadFromRenderedText(inputName.c_str(), textColor, *Fonts[PT10], app);

    gBack->setWidth(gBackTextTex->getWidth());
    gBack->setHeight(gBackTextTex->getHeight());
    gBack->setPosition((SCREEN_WIDTH - gBackTextTex->getWidth()) / 2, SCREEN_HEIGHT - (gBackTextTex->getHeight() * 2));

    SDL_StartTextInput();

    while (!quit)
    {

        bool renderText = false;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                setState(Exit);
                quit = true;
            }

            if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
            {

                int x, y;
                SDL_GetMouseState(&x, &y);

                bool inside = true;

                if (x < gBack->getPosition().x)
                {
                    inside = false;
                }

                else if (x > gBack->getPosition().x + gBack->getWidth())
                {
                    inside = false;
                }

                else if (y < gBack->getPosition().y)
                {
                    inside = false;
                }

                else if (y > gBack->getPosition().y + gBack->getHeight())
                {
                    inside = false;
                }

                if (inside)
                {

                    switch (e.type)
                    {

                    case SDL_MOUSEBUTTONDOWN:
                        setState(Main);
                        return;

                    }

                }

            }

            else if (e.type == SDL_KEYDOWN)
            {

                if (e.key.keysym.sym == SDLK_BACKSPACE && inputName.length() > 0)
                {
                    inputName.pop_back();
                    renderText = true;
                }

                else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
                {
                    SDL_SetClipboardText(inputName.c_str());
                }

                else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
                {
                    inputName = SDL_GetClipboardText();
                    renderText = true;
                }

                else if (e.key.keysym.sym == SDLK_RETURN)
                {
                    if (inputName.length() <= 20)
                    {
                        quit = true;
                    }
                }

            }

            else if (e.type == SDL_TEXTINPUT)
            {

                if (!(SDL_GetModState() & KMOD_CTRL && (e.text.text[0] == 'c' || e.text.text[0] == 'C' || e.text.text[0] == 'v' || e.text.text[0] == 'V')))
                {
                    inputName += e.text.text;
                    renderText = true;
                }

            }

        }

        if (renderText)
        {
            if (inputName != "")
            {
                gInputTextTex->loadFromRenderedText(inputName.c_str(), textColor, *Fonts[PT10], app);
            }
            else
            {
                gInputTextTex->loadFromRenderedText(" ", textColor, *Fonts[PT10], app);
            }

        }

        SDL_SetRenderDrawColor(app.getRenderer(), 0, 0, 0, 0);
        SDL_RenderClear(app.getRenderer());

        gEnterNameTextTex->render((SCREEN_WIDTH - gEnterNameTextTex->getWidth()) / 2, gEnterNameTextTex->getHeight(), app);
        gInputTextTex->render((SCREEN_WIDTH - gInputTextTex->getWidth()) / 2, gEnterNameTextTex->getHeight() + gInputTextTex->getHeight() + 16, app);

        gWarnSignTextTex->render((SCREEN_WIDTH - gWarnSignTextTex->getWidth()) / 2, gInputTextTex->getHeight() + gEnterNameTextTex->getHeight() + 64, app);

        gContTextTex->render((SCREEN_WIDTH - gContTextTex->getWidth()) / 2, SCREEN_HEIGHT - (gContTextTex->getHeight() * 2 + gInputTextTex->getHeight() * 2), app);

        gBackTextTex->render((SCREEN_WIDTH - gBackTextTex->getWidth()) / 2, SCREEN_HEIGHT - (gBackTextTex->getHeight() * 2), app);

        SDL_RenderPresent(app.getRenderer());

    }

    SDL_StopTextInput();

}

void Menu::leaderboard(SDL_Event& e, AppInit& app, struct list*& player, bool& quit, int ncount)
{

    lBNodeText[0].str("Leaderboard");
    gLBoardListTextTex[0].loadFromRenderedText(lBNodeText[0].str(), { 255, 255, 0, 255 }, *Fonts[PT10], app);
    gClearScoresTextTex->loadFromRenderedText("Press 'c' to clear leaderboard.", { 0xFF, 0xFF, 0xFF, 0xFF }, *Fonts[PT8], app);

    gBack->setWidth(gBackTextTex->getWidth());
    gBack->setHeight(gBackTextTex->getHeight());
    gBack->setPosition((SCREEN_WIDTH - gBackTextTex->getWidth()) / 2, SCREEN_HEIGHT - (gBackTextTex->getHeight() * 2));

    if (player != nullptr)
    {
        for (int i = 1; i < 11; i++)
        {
            if (i <= ncount)
            {
                lBNodeText[i] << i << ". " << player->data.name << " " << player->data.score;
                gLBoardListTextTex[i].loadFromRenderedText(lBNodeText[i].str(), { 0xFF, 0xFF, 0xFF, 0xFF }, *Fonts[PT8], app);
                player = player->next;
            }
        }
    }

    while (!quit)
    {

        bool renderText = false;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                setState(Exit);
                quit = true;
            }

            else if (e.type == SDL_KEYDOWN)
            {

                if (e.key.keysym.sym == SDLK_c)
                {
                    for (int i = 1; i < 11; i++)
                    {
                        lBNodeText[i].str(" ");
                        gLBoardListTextTex[i].loadFromRenderedText(lBNodeText[i].str(), { 0xFF, 0xFF, 0xFF, 0xFF }, *Fonts[PT8], app);
                    }
                    delete_list(player);
                    remove("leaderboard/leaderboard");

                }

            }

            else if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
            {

                int x, y;
                SDL_GetMouseState(&x, &y);

                bool inside = true;

                if (x < gBack->getPosition().x)
                {
                    inside = false;
                }

                else if (x > gBack->getPosition().x + gBack->getWidth())
                {
                    inside = false;
                }

                else if (y < gBack->getPosition().y)
                {
                    inside = false;
                }

                else if (y > gBack->getPosition().y + gBack->getHeight())
                {
                    inside = false;
                }

                if (inside)
                {

                    switch (e.type)
                    {

                    case SDL_MOUSEBUTTONDOWN:
                        setState(Main);
                        return;
                    }

                }

            }

        }

        SDL_SetRenderDrawColor(app.getRenderer(), 0, 0, 0, 0);
        SDL_RenderClear(app.getRenderer());

        gLBoardListTextTex[0].render((SCREEN_WIDTH - gLBoardListTextTex[0].getWidth()) / 2, 20, app);

        player = read_file();
        if (player)
        {
            for (int i = 1; i < 11; i++)
            {

                gLBoardListTextTex[i].render((SCREEN_WIDTH - gLBoardListTextTex[i].getWidth()) / 2, (gLBoardListTextTex[i].getHeight() + 20) + i * 20, app);

            }
        }

        gClearScoresTextTex->render((SCREEN_WIDTH - gClearScoresTextTex->getWidth()) / 2, int(SCREEN_HEIGHT / 1.2), app);
        gBackTextTex->render((SCREEN_WIDTH - gBackTextTex->getWidth()) / 2, SCREEN_HEIGHT - (gBackTextTex->getHeight() * 2), app);

        SDL_RenderPresent(app.getRenderer());
    }

}

void Menu::inform(SDL_Event& e, AppInit& app, bool& quit)
{

    gBack->setWidth(gBackTextTex->getWidth());
    gBack->setHeight(gBackTextTex->getHeight());
    gBack->setPosition((SCREEN_WIDTH - gBackTextTex->getWidth()) / 2, SCREEN_HEIGHT - (gBackTextTex->getHeight() * 2));

    while (!quit)
    {

        bool renderText = false;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                setState(Exit);
                quit = true;
            }

            if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
            {

                int x, y;
                SDL_GetMouseState(&x, &y);

                bool inside = true;

                if (x < gBack->getPosition().x)
                {
                    inside = false;
                }

                else if (x > gBack->getPosition().x + gBack->getWidth())
                {
                    inside = false;
                }

                else if (y < gBack->getPosition().y)
                {
                    inside = false;
                }

                else if (y > gBack->getPosition().y + gBack->getHeight())
                {
                    inside = false;
                }

                if (inside)
                {

                    switch (e.type)
                    {

                    case SDL_MOUSEBUTTONDOWN:
                        setState(Main);
                        return;
                    }

                }

            }

        }

        SDL_SetRenderDrawColor(app.getRenderer(), 0, 0, 0, 0);
        SDL_RenderClear(app.getRenderer());

        informTextTex[0].render((SCREEN_WIDTH - informTextTex[0].getWidth()) / 2, 0, app);


        for (int i = 1; i < 12; i++)
        {

            informTextTex[i].render((SCREEN_WIDTH - informTextTex[i].getWidth()) / 2, (informTextTex[i].getHeight() + 20) + i * 20, app);

        }


        gBackTextTex->render((SCREEN_WIDTH - gBackTextTex->getWidth()) / 2, SCREEN_HEIGHT - (gBackTextTex->getHeight() * 2), app);

        SDL_RenderPresent(app.getRenderer());
    }

}