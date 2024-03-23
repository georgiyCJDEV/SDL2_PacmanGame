#pragma once
#include <iostream>

class LTimer
{

protected:
    uint32_t mStartTicks;
    uint32_t mPausedTicks;
    bool mPaused;
    bool mStarted;

public:
    LTimer();
    void start();
    void stop();
    void pause();
    void unpause();
    uint32_t getTicks();
    bool isStarted();
    bool isPaused();

};
