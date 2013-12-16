//
//  GameLogic.cpp
//  ChickenHunt
//
//  Created by Gerald Quick on 12/14/13.
//
//

#include "GameLogic.h"

USING_NS_CC;

GameLogic::GameLogic()
{
    state = READY;
    _currentTime = 60;
}

GameLogic::~GameLogic()
{}

void GameLogic::initTimer(float value, cocos2d::CCSize size)
{
    if (value != DEFALUT_TIMER_VALUE) {
        _currentTime = value;
    }
    auto int tmpValue = _currentTime;
    auto CCString * tValue = CCString::createWithFormat("%i",tmpValue);
    timerValue = CCLabelBMFont::create(tValue->getCString(), "fonts-ipadhd.fnt", size.width * 0.3f);
    timerValue->setAnchorPoint(ccp(0.5,0.5));
    timerValue->setPosition(ccp(size.width / 2, size.height - this->timerGUI->boundingBox().size.height/2-timerValue->getContentSize().height/3));
}

void GameLogic::update(float dt)
{
    switch (state) {
        case READY:
            state = RUNNING;
            break;
        case RUNNING:
            updateTimer(dt);
            
            break;
        case GAMEOVER:
            break;
            
        default:
            break;
    }
    
}
void GameLogic::updateTimer(float dt)
{
    _currentTime -= dt;
    auto int tmpValue = _currentTime;
    auto CCString * value = CCString::createWithFormat("%i",tmpValue);
    timerValue->setString(value->getCString());
    
    if (_currentTime <= 0.0f) {
        state = GAMEOVER;
    }
}
void GameLogic::setTimerPosition(float x, float y)
{
    timerGUI->setPosition(ccp(x,y));
}
void GameLogic::updateScore(int value)
{
    auto CCString * pValue = CCString::createWithFormat("Score:%i", value);
    _scoreDisplay->setString(pValue->getCString());
}