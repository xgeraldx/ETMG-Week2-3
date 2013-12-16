//
//  GameLogic.h
//  ChickenHunt
//
//  Created by Gerald Quick on 12/14/13.
//
//

#ifndef __ChickenHunt__GameLogic__
#define __ChickenHunt__GameLogic__

#include "cocos2d.h"

enum GAMESTATE {READY,RUNNING, GAMEOVER};
const float DEFALUT_TIMER_VALUE = 60.0f;

class GameLogic
{
private:
    float _currentTime;
    
public:
    cocos2d::CCLabelBMFont * _scoreDisplay;
    GAMESTATE state;
    GameLogic(void);
    ~GameLogic(void);
    void initTimer(float value, cocos2d::CCSize size);
    void update(float dt);
    void updateTimer(float dt);
    int getTime();
    cocos2d::CCLabelBMFont * timerValue;
    cocos2d::CCSprite * timerGUI;
    void setTimerPosition(float x, float y);
    void updateScore(int value);
};

#endif /* defined(__ChickenHunt__GameLogic__) */
