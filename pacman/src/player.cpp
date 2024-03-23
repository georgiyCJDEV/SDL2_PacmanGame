#include "player.h"
#include <iostream>
#include <sstream>

Player::Player(AppInit& app)
{
    for (int i = 0; i < TOTALFONTS; i++)
    {
        Fonts[i] = app.getFonts()[i];
    }

    for (int i = 0; i < TOTALSOUNDS; i++)
    {
        Sounds[i] = app.getSounds()[i];
    }

    loadMedia(app);
    setPacSprites();
    setGhostPointsSprites();

    this->mPosX = (BOUNDS_X + (LEVEL_WIDTH / 2)) - 8;
    this->mPosY = (BOUNDS_Y + (LEVEL_HEIGHT / 2)) + 92;

    this->mVelX = 0;
    this->mVelY = 0;

    mBox.w = 16;
    mBox.h = 16;

    this->side = 0;
    this->frame = 0;
    this->currentClip = &gPlayerMov[0][0];

    this->lives = 3;
    this->score = 0;

    this->killcount = 0;

    this->splitted = false;

    this->PacState = NotSpawned;
}

Player::~Player()
{
    std::cout << "\nPlayer destructor called";
    gPausedTextTex->~LTexture();
    delete gPausedTextTex;
    gPausedTextTex = nullptr;
    gLCounterTextTex->~LTexture();
    delete gLCounterTextTex;
    gLCounterTextTex = nullptr;
    gPlayerTitleTextTex->~LTexture();
    delete gPlayerTitleTextTex;
    gPlayerTitleTextTex = nullptr;
    gScoreTitleTextTex->~LTexture();
    delete gScoreTitleTextTex;
    gScoreTitleTextTex = nullptr;
    gHiScoreTitleTextTex->~LTexture();
    delete gHiScoreTitleTextTex;
    gHiScoreTitleTextTex = nullptr;
    gScoreTextTex->~LTexture();
    delete gScoreTextTex;
    gScoreTextTex = nullptr;
    gHiScoreTextTex->~LTexture();
    delete gHiScoreTextTex;
    gHiScoreTextTex = nullptr;
    gReadyTextTex->~LTexture();
    delete gReadyTextTex;
    gReadyTextTex = nullptr;
    gPlayerTex->~LTexture();
    delete gPlayerTex;
    gPlayerTex = nullptr;
    gGameOverTextTex->~LTexture();
    delete gGameOverTextTex;
    gGameOverTextTex = nullptr;
    gResultTextTex->~LTexture();
    delete gResultTextTex;
    gResultTextTex = nullptr;
    gReturnTextTex->~LTexture();
    delete gReturnTextTex;
    gReturnTextTex = nullptr;
    gGPointsTex->~LTexture();
    delete gGPointsTex;
    gGPointsTex = nullptr;
    gNameTextTex->~LTexture();
    delete gNameTextTex;
    gNameTextTex = nullptr;
    gNameText2Tex->~LTexture();
    delete gNameText2Tex;
    gNameText2Tex = nullptr;
    std::cout << "\nPlayer destructor worked";
}

void Player::loadMedia(AppInit& app)
{
    gPlayerTex->loadFromFile("res/sprites/pacman.png", app);
    gGPointsTex->loadFromFile("res/sprites/ghost_points.png", app);
    gReadyTextTex->loadFromRenderedText("Ready!", { 255, 255, 0, 255 }, *Fonts[PT8], app);
    gLCounterTextTex->loadFromRenderedText("Lives: ", { 255,255,255,255 }, *Fonts[PT10], app);
    gPlayerTitleTextTex->loadFromRenderedText("Player:", { 255,255,255,255 }, *Fonts[PT10], app);
    gScoreTitleTextTex->loadFromRenderedText("Score:", { 255,255,255,255 }, *Fonts[PT10], app);
    gHiScoreTitleTextTex->loadFromRenderedText("High Score:", { 255,255,255,255 }, *Fonts[PT10], app);
    gPausedTextTex->loadFromRenderedText("Game is paused. Press 's' to unpause", { 255,255,255,255 }, *Fonts[PT9], app);
}

void Player::setGhostPointsSprites()
{
    for (int i = 0; i < 4; i++)
    {
        if (i == 0)
        {
            gKillPoints[i].x = 1;
            gKillPoints[i].y = 1;
        }
        else
        {
            gKillPoints[i].x = gKillPoints[i - 1].x + 17;
            gKillPoints[i].y = 1;
        }
        gKillPoints[i].w = 16;
        gKillPoints[i].h = 16;
    }
}
void Player::setPacSprites()
{
    for (int i = 0; i < 17; i++)
    {
        if (i < 5)
        {
            for (int j = 0; j < 2; j++)
            {
                if (i == 0)
                {
                    gPlayerMov[i][j].x = 1;
                    gPlayerMov[i][j].y = 1;
                }
                else if ((i != 0) && (gPlayerMov[i][j - 1].x + 17 != gPlayerTex->getWidth()))
                {
                    gPlayerMov[i][j].x = 17 + gPlayerMov[i][j - 1].x;
                    gPlayerMov[i][j].y = gPlayerMov[i][j - 1].y;
                }
                else if ((i != 0) && (gPlayerMov[i][j - 1].x + 17 == gPlayerTex->getWidth()))
                {
                    gPlayerMov[i][j].x = 1;
                    gPlayerMov[i][j].y = gPlayerMov[i][j - 1].y + 17;
                }

                gPlayerMov[i][j].w = 16;
                gPlayerMov[i][j].h = 16;

            }
        }
        else if (i >= 5)
        {
            int j = i - 5;
            if (i == 5)
            {
                gPlayerDeath[j].x = gPlayerMov[4][1].x + 17;
                gPlayerDeath[j].y = gPlayerMov[4][1].y;
            }
            else if ((i > 5) && (gPlayerDeath[j - 1].x + 17 != gPlayerTex->getWidth()))
            {
                gPlayerDeath[j].x = 17 + gPlayerDeath[j - 1].x;
                gPlayerDeath[j].y = gPlayerDeath[j - 1].y;
            }
            else if ((i > 5) && (gPlayerDeath[j - 1].x + 17 == gPlayerTex->getWidth()))
            {
                gPlayerDeath[j].x = 1;
                gPlayerDeath[j].y = gPlayerDeath[j - 1].y + 17;
            }
            gPlayerDeath[j].w = 16;
            gPlayerDeath[j].h = 16;
        }
    }
}


void Player::setPacState(Uint8 PacState)
{
    this->PacState = PacState;
}

Uint8 Player::getPacState()
{
    return this->PacState;
}

void Player::setKillCount(int kcountval)
{
    killcount = kcountval;
}

void Player::setSide(int sidevalue)
{
    this->side = sidevalue;
}

void Player::setCurClip()
{
    currentClip = &gPlayerMov[side][frame / 4];
}

void Player::setDeathClip()
{
    currentClip = &gPlayerDeath[frame / 8];
}

void Player::pausedRender(AppInit& app)
{
    gPausedTextTex->render((SCREEN_WIDTH - gPausedTextTex->getWidth()) / 2, (SCREEN_HEIGHT - gPausedTextTex->getHeight()) / 2, app);
}

void Player::spawn(AppInit& app)
{

    lives--;

    Mix_PlayMusic(Sounds[START], 1);
    setPos((BOUNDS_X + (LEVEL_WIDTH / 2) - 8), (BOUNDS_Y + (LEVEL_HEIGHT / 2)) + 92);

    setSide(0);
    frame = 0;
    setCurClip();

    while (Mix_PlayingMusic() != 0)
    {
        gReadyTextTex->render((BOUNDS_X + (LEVEL_WIDTH / 2)) - (gReadyTextTex->getWidth() / 2), (int)(((BOUNDS_Y + (LEVEL_HEIGHT / 1.65)) - (gReadyTextTex->getHeight() / 1.5))), app);
        render(app);

        SDL_RenderPresent(app.getRenderer());
    }
    setPacState(Alive);
}

void Player::death()
{
    Ghost ghost;
    setPacState(Dead);

    mVelX = 0;
    mVelY = 0;

    for (int i = 0; i < 4; i++)
    {
        count[i] = 0;
    }

    frame = 5;
    setDeathClip();


    Mix_PauseMusic();
    Mix_PlayMusic(Sounds[DEATH], 1);
}

int Player::getLives()
{
    return lives;
}

int Player::getScore()
{
    return score;
}

void Player::handleEvent(SDL_Event& e, Wall& walls, bool& ispaused)
{
    int mVelX2 = 0, mVelY2 = 0;

    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {

        case SDLK_UP:

            isColliding = false;

            count[3]++;

            if (count[3] == 1)
            {
                mVelY2 -= ENT_VEL;

                mPosX += mVelX2;
                mBox.x = mPosX;
                mPosY += mVelY2;
                mBox.y = mPosY;

                if (walls.touchesWall(mBox))
                {
                    mPosX -= mVelX2;
                    mBox.x = mPosX;
                    mPosY -= mVelY2;
                    mBox.y = mPosY;

                    count[3] = 0;

                    return;
                }

                else
                {
                    mPosX -= mVelX2;
                    mBox.x = mPosX;
                    mPosY -= mVelY2;
                    mBox.y = mPosY;

                    setSide(UP);

                    if (count[0] >= 1)
                    {
                        mVelX -= ENT_VEL;
                        count[0] = 0;
                    }

                    if (count[1] >= 1)
                    {
                        count[1] = 0;
                        mVelY -= ENT_VEL;
                    }

                    if (count[2] >= 1)
                    {
                        count[2] = 0;
                        mVelX += ENT_VEL;
                    }

                    mVelY -= ENT_VEL;

                    SoundMov();
                }
            }

            break;

        case SDLK_DOWN:

            isColliding = false;

            count[1]++;

            if (count[1] == 1)
            {
                mVelY2 += ENT_VEL;

                mPosX += mVelX2;
                mBox.x = mPosX;
                mPosY += mVelY2;
                mBox.y = mPosY;

                if (walls.touchesWall(mBox))
                {
                    mPosX -= mVelX2;
                    mBox.x = mPosX;
                    mPosY -= mVelY2;
                    mBox.y = mPosY;

                    count[1] = 0;

                    return;
                }

                else
                {
                    mPosX -= mVelX2;
                    mBox.x = mPosX;
                    mPosY -= mVelY2;
                    mBox.y = mPosY;

                    setSide(DOWN);

                    if (count[0] >= 1)
                    {
                        mVelX -= ENT_VEL;
                        count[0] = 0;
                    }

                    if (count[2] >= 1)
                    {
                        count[2] = 0;
                        mVelX += ENT_VEL;
                    }

                    if (count[3] >= 1)
                    {
                        count[3] = 0;
                        mVelY += ENT_VEL;
                    }

                    mVelY += ENT_VEL;
                    SoundMov();
                }
            }

            break;

        case SDLK_LEFT:

            isColliding = false;

            count[2]++;

            if (count[2] == 1)
            {
                mVelX2 -= ENT_VEL;

                mPosX += mVelX2;
                mBox.x = mPosX;
                mPosY += mVelY2;
                mBox.y = mPosY;

                if (walls.touchesWall(mBox))
                {
                    mPosX -= mVelX2;
                    mBox.x = mPosX;
                    mPosY -= mVelY2;
                    mBox.y = mPosY;

                    count[2] = 0;

                    return;
                }

                else
                {
                    mPosX -= mVelX2;
                    mBox.x = mPosX;
                    mPosY -= mVelY2;
                    mBox.y = mPosY;

                    setSide(LEFT);

                    if (count[0] >= 1)
                    {
                        count[0] = 0;
                        mVelX -= ENT_VEL;
                    }

                    if (count[1] >= 1)
                    {
                        count[1] = 0;
                        mVelY -= ENT_VEL;
                    }

                    if (count[3] >= 1)
                    {
                        count[3] = 0;
                        mVelY += ENT_VEL;
                    }

                    mVelX -= ENT_VEL;
                    SoundMov();
                }
            }

            break;

        case SDLK_RIGHT:

            isColliding = false;

            count[0]++;

            if (count[0] == 1)
            {
                mVelX2 += ENT_VEL;

                mPosX += mVelX2;
                mBox.x = mPosX;
                mPosY += mVelY2;
                mBox.y = mPosY;

                if (walls.touchesWall(mBox))
                {
                    mPosX -= mVelX2;
                    mBox.x = mPosX;
                    mPosY -= mVelY2;
                    mBox.y = mPosY;

                    count[0] = 0;

                    return;
                }

                else
                {
                    mPosX -= mVelX2;
                    mBox.x = mPosX;
                    mPosY -= mVelY2;
                    mBox.y = mPosY;

                    setSide(RIGHT);

                    if (count[1] >= 1)
                    {
                        count[1] = 0;
                        mVelY -= ENT_VEL;
                    }

                    if (count[2] >= 1)
                    {
                        count[2] = 0;
                        mVelX += ENT_VEL;
                    }

                    if (count[3] >= 1)
                    {
                        count[3] = 0;
                        mVelY += ENT_VEL;
                    }

                    mVelX += ENT_VEL;
                    SoundMov();
                }

            }

            break;

        case SDLK_p:
            ispaused = true;
            break;

        case SDLK_s:
            ispaused = false;
            break;
        }

    }
}

void Player::move(AppInit& app, Wall& walls, Points& points, Ghost& ghosts, LTimer& timer)
{
    LTimer killtime;
    mPosX += mVelX;
    mBox.x = mPosX;
    mPosY += mVelY;
    mBox.y = mPosY;

    if (checkCollision(mBox, ghosts.getGhosts()[ghosts.Red]->getBox()))
    {
        if (ghosts.getGhosts()[ghosts.Red]->getColor()==ghosts.Red)
        {
            isColliding = true;
            death();
        }
        else if (ghosts.getGhosts()[ghosts.Red]->getColor() == ghosts.Vuln)
        {
            score += int(pow(2, killcount) * 200);
            killcount += 1;
            killtime.start();

            timer.pause();
            while (killtime.getTicks() < 500)
            {
                gGPointsTex->render(ghosts.getGhosts()[ghosts.Red]->getBox().x, ghosts.getGhosts()[ghosts.Red]->getBox().y, app, &gKillPoints[killcount - 1]);
                ghosts.getGhosts()[ghosts.Red]->getColor() = ghosts.Dead;
                SDL_RenderPresent(app.getRenderer());
            }
            timer.unpause();
        }
    }

    if (checkCollision(mBox, ghosts.getGhosts()[ghosts.Blue]->getBox()))
    {
        if (ghosts.getGhosts()[ghosts.Blue]->getColor()==ghosts.Blue)
        {
            isColliding = true;
            death();
        }
        else if (ghosts.getGhosts()[ghosts.Blue]->getColor() == ghosts.Vuln)
        {
            score += int(pow(2, killcount) * 200);
            killcount += 1;
            killtime.start();

            timer.pause();
            while (killtime.getTicks() < 500)
            {
                gGPointsTex->render(ghosts.getGhosts()[ghosts.Blue]->getBox().x, ghosts.getGhosts()[ghosts.Blue]->getBox().y, app, &gKillPoints[killcount - 1]);
                ghosts.getGhosts()[ghosts.Blue]->getColor() = ghosts.Dead;
                SDL_RenderPresent(app.getRenderer());
            }
            timer.unpause();
        }
    }

    if (checkCollision(mBox, ghosts.getGhosts()[ghosts.Yellow]->getBox()))
    {
        if (ghosts.getGhosts()[ghosts.Yellow]->getColor()==ghosts.Yellow)
        {
            isColliding = true;
            death();
        }
        else if (ghosts.getGhosts()[ghosts.Yellow]->getColor() == ghosts.Vuln)
        {
            score += int(pow(2, killcount) * 200);
            killcount += 1;
            killtime.start();

            timer.pause();
            while (killtime.getTicks() < 500)
            {
                gGPointsTex->render(ghosts.getGhosts()[ghosts.Yellow]->getBox().x, ghosts.getGhosts()[ghosts.Yellow]->getBox().y, app, &gKillPoints[killcount - 1]);
                ghosts.getGhosts()[ghosts.Yellow]->getColor() = ghosts.Dead;
                SDL_RenderPresent(app.getRenderer());
            }
            timer.unpause();
        }
    }

    if (checkCollision(mBox, ghosts.getGhosts()[ghosts.Pink]->getBox()))
    {
        if (ghosts.getGhosts()[ghosts.Pink]->getColor() == ghosts.Pink)
        {
            isColliding = true;
            death();
        }
        else if (ghosts.getGhosts()[ghosts.Pink]->getColor() == ghosts.Vuln)
        {
            score += int(pow(2, killcount) * 200);
            killcount += 1;
            killtime.start();

            timer.pause();
            while (killtime.getTicks() < 500)
            {
                gGPointsTex->render(ghosts.getGhosts()[ghosts.Yellow]->getBox().x, ghosts.getGhosts()[ghosts.Yellow]->getBox().y, app, &gKillPoints[killcount - 1]);
                ghosts.getGhosts()[ghosts.Pink]->getColor() = ghosts.Dead;
                SDL_RenderPresent(app.getRenderer());
            }
            timer.unpause();
        }
    }

    points.touchesPoint(mBox, score);

    points.touchesPoint2(mBox, score, ghosts, timer);

    boundsCollision();

    if (walls.touchesWall(mBox))
    {
        isColliding = true;

        mPosX -= mVelX;
        mBox.x = mPosX;
        mPosY -= mVelY;
        mBox.y = mPosY;

    }
}

bool Player::AnimMov(AppInit& app)
{
    bool isOver = false;
    if (getPacState() == NotSpawned)
    {
        spawn(app);
    }
    else if (getPacState() == Alive && getIsColliding() == false)
    {

        setCurClip();

        render(app);
        ++frame;

        if (frame / 4 >= MOVFRAMES)
        {
            frame = 0;
        }

    }
    else if (getPacState() == Alive && getIsColliding() == true)
    {
        frame = 0;
        setCurClip();
        render(app);
        Mix_PauseMusic();
    }
    else if (getPacState() == Dead)
    {
        setDeathClip();

        render(app);
        ++frame;

        if (frame / 8 >= 12)
        {

            frame = 0;
            side = 0;
            setCurClip();

            if (getLives() > 0)
            {
                spawn(app);
            }

            else
            {
                isOver = true;
            }

        }

    }
    return isOver;
}

void Player::showInterf(std::string playerName, int highScore, AppInit& app)
{
    gPlayerTitleTextTex->render(BOUNDS_X, BOUNDS_Y - gPlayerTitleTextTex->getHeight(), app);
    gScoreTitleTextTex->render(BOUNDS_X + gPlayerTitleTextTex->getWidth() + 16, BOUNDS_Y - gScoreTitleTextTex->getHeight(), app);
    gHiScoreTitleTextTex->render(BOUNDS_X + (gPlayerTitleTextTex->getWidth() + gScoreTitleTextTex->getWidth()) + 32, BOUNDS_Y - gHiScoreTitleTextTex->getHeight(), app);

    gLCounterTextTex->render(BOUNDS_X, BOUNDS_HEIGHT, app);
    for (int i = 0; i < lives; i++)
    {
        gPlayerTex->render(BOUNDS_X + (gLCounterTextTex->getWidth() + i * 16), BOUNDS_HEIGHT, app, &gPlayerMov[3][0]);
    }
    SDL_Color textColor = { 255,255,255,255 };
    std::stringstream scoretext;
    std::stringstream hiScoretext;
    scoretext << score;
    hiScoretext << highScore;

    gScoreTextTex->loadFromRenderedText(scoretext.str().c_str(), textColor, *Fonts[PT9], app);
    gHiScoreTextTex->loadFromRenderedText(hiScoretext.str().c_str(), textColor, *Fonts[PT9], app);

    if (!splitted)
    {
        gNameTextTex->loadFromRenderedText(playerName.c_str(), textColor, *Fonts[PT9], app);

        if (gNameTextTex->getWidth() >= (gPlayerTitleTextTex->getWidth() + 16))
        {
            char splname[20] = "\0", splname2[20] = "\0";
            for (Uint32 i = 0; i <= (playerName.length() / 2); i++)
            {
                splname[i] = playerName[i];
                splname[i + 1] = '\0';
            }
            for (Uint32 i = 0, j = (playerName.length() / 2) + 1; j <= playerName.length(); i++, j++)
            {
                splname2[i] = playerName[j];
                splname2[i + 1] = '\0';
            }
            gNameTextTex->~LTexture();
            gNameTextTex->loadFromRenderedText(splname, textColor, *Fonts[PT9], app);
            gNameText2Tex->loadFromRenderedText(splname2, textColor, *Fonts[PT9], app);
            splitted = true;
        }
    }

    if (!splitted)
    {
        gNameTextTex->render(BOUNDS_X, BOUNDS_Y, app);
    }
    else
    {
        gNameTextTex->render(BOUNDS_X, BOUNDS_Y - gPlayerTitleTextTex->getHeight() + gNameTextTex->getHeight(), app);
        gNameText2Tex->render(BOUNDS_X, BOUNDS_Y + gNameText2Tex->getHeight(), app);
    }
    gScoreTextTex->render(BOUNDS_X + gPlayerTitleTextTex->getWidth() + 16, BOUNDS_Y, app);
    gHiScoreTextTex->render(BOUNDS_X + gPlayerTitleTextTex->getWidth() + gScoreTitleTextTex->getWidth() + 32, BOUNDS_Y, app);
}

void Player::ShowGameOver(bool& quit, AppInit& app)
{
    while (!quit)
    {

        SDL_SetRenderDrawColor(app.getRenderer(), 0, 0, 0, 0);
        SDL_RenderClear(app.getRenderer());

        SDL_Color textColor = { 153,0,0,0 }, textColor2 = { 255,255,255,255 }, textColor3 = { 255, 255, 0, 255 };
        std::string gameOver = "Game Over";
        std::string gameOverReturnMenu = "Press 'Enter' to return to menu";

        std::stringstream gameResult;
        gameResult << "You scored " << score << " points!";

        gGameOverTextTex->loadFromRenderedText(gameOver.c_str(), textColor, *Fonts[PT14], app);
        gResultTextTex->loadFromRenderedText(gameResult.str().c_str(), textColor3, *Fonts[PT10], app);
        gReturnTextTex->loadFromRenderedText(gameOverReturnMenu.c_str(), textColor2, *Fonts[PT8], app);

        gGameOverTextTex->render((SCREEN_WIDTH - gGameOverTextTex->getWidth()) / 2, SCREEN_HEIGHT / 4, app);
        gResultTextTex->render((SCREEN_WIDTH - gResultTextTex->getWidth()) / 2, SCREEN_HEIGHT / 2, app);
        gReturnTextTex->render((SCREEN_WIDTH - gReturnTextTex->getWidth()) / 2, SCREEN_HEIGHT - gReturnTextTex->getHeight(), app);

        SDL_RenderPresent(app.getRenderer());

    }

}

void Player::gameOver(SDL_Event& e, bool& quit, int& gameState)
{
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
                return;
            }

            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_RETURN)
                {
                    quit = true;
                    gameState = 1;
                }
            }
        }
    }
}

void Player::SoundMov()
{
    if (Mix_PlayingMusic() == 0 && getIsColliding() == false)
    {
        Mix_PlayMusic(Sounds[MOVE], -1);
    }

    else if (Mix_PlayingMusic() != 0 && getIsColliding() == false)
    {
        Mix_PauseMusic();
        Mix_PlayMusic(Sounds[MOVE], -1);
    }
}

void Player::render(AppInit& app)
{
    gPlayerTex->render(mPosX, mPosY, app, currentClip);
}
