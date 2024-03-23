#pragma once
#include "texture.h"
#include "init.h"
#include "points.h"
#include <string>

class Player :public Ghost
{

private:
    TTF_Font* Fonts[TOTALFONTS];
    Mix_Music* Sounds[TOTALSOUNDS];

    LTexture *gPausedTextTex=new LTexture();
    LTexture *gLCounterTextTex = new LTexture();
    LTexture *gPlayerTitleTextTex = new LTexture();
    LTexture *gScoreTitleTextTex = new LTexture();
    LTexture *gHiScoreTitleTextTex = new LTexture();
    LTexture *gScoreTextTex = new LTexture();
    LTexture *gHiScoreTextTex = new LTexture();
    LTexture *gReadyTextTex = new LTexture();
    LTexture *gPlayerTex = new LTexture();
    LTexture *gGameOverTextTex = new LTexture();
    LTexture *gResultTextTex = new LTexture();
    LTexture *gReturnTextTex = new LTexture();
    LTexture *gGPointsTex = new LTexture();
    LTexture *gNameTextTex = new LTexture();
    LTexture *gNameText2Tex = new LTexture();

    SDL_Rect gPlayerDeath[12];
    SDL_Rect gKillPoints[4];
    SDL_Rect gPlayerMov[5][MOVFRAMES];

    Uint8 PacState;

protected:
    int lives;
    int score;
    int killcount;
    int count[4] = { 0,0,0,0 };
    bool splitted;

public:
    Player(AppInit&);
    ~Player();
    void setPacState(Uint8);
    Uint8 getPacState();
    void spawn(AppInit&);
    void death();
    void setSide(int);
    void setCurClip();
    void setKillCount(int);
    bool AnimMov(AppInit&);
    int getLives();
    int getScore();
    void setDeathClip();
    void SoundMov();
    void handleEvent(SDL_Event& e, Wall& walls, bool&);
    void move(AppInit&,Wall&, Points&, Ghost&, LTimer&);
    void gameOver(SDL_Event&, bool&, int&);
    void ShowGameOver(bool&, AppInit&);
    void showInterf(std::string, int, AppInit&);
    void render(AppInit&) override;
    void pausedRender(AppInit&);
    void setPacSprites();
    void setGhostPointsSprites();
    void loadMedia(AppInit&);
    enum sideSprite
    {
        RIGHT = 1,
        DOWN = 2,
        LEFT = 3,
        UP = 4,
    };
    enum Pacstate
    {
        NotSpawned = 0,
        Alive = 1,
        Dead = 2
    };
};
