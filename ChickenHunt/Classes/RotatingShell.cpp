//
//  RotatingShell.cpp
//  ChickenHunt
//
//  Created by Gerald Quick on 12/15/13.
//
//

#include "RotatingShell.h"
USING_NS_CC;

RotatingShell::RotatingShell()
{
    _currenTime = 0.0f;
    _velocity = 15.0f;
    
    cocos2d::CCSpriteFrame * frame;
    cocos2d::CCAnimation * animation;
    animation = cocos2d::CCAnimation::create();
    cocos2d::CCString * name;
    for(int i = 0; i <= 20; i++) {
        name = cocos2d::CCString::createWithFormat("shell%i.png", i);
        frame = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animation->addSpriteFrame(frame);
    }
    
    animation->setDelayPerUnit(.35 / 21.0f);
    animation->setRestoreOriginalFrame(false);
    animation->setLoops(1);
    _rotate = cocos2d::CCSequence::create(
                                       cocos2d::CCAnimate::create(animation),
                                       CCCallFuncN::create(this, callfuncN_selector(RotatingShell::shellAnimationDone)),
                                       NULL);
    _rotate->retain();
    this->
    isVisible = false;
    //_shell->runAction(_rotate);
}

RotatingShell::~RotatingShell()
{
    
}

void RotatingShell::update(float dt)
{
    
    if(_shell->numberOfRunningActions() <= 0)
    {
        _shell->runAction(_rotate);
    }
    _currenTime += dt;
    _posX = _shell->getPositionX();
    _posX += 1.0f;
    _posY = _shell->getPositionY();
    //_posX *= .1;
    //if (_currenTime <=0)
    //{
        //_posX = _posX /4;
        _posY = _posY + _velocity * _currenTime -18.8f * _currenTime * _currenTime;
        //_posY *= .1f;
        CCLOG("PositionY: %f",_posY);
        //_posY += _shell->getPositionY();
        _shell->setPosition(ccp(_posX,_posY));
        //_currenTime = 1.0f;
    //}
    if(_posY < 0)
    {
        _shell->setVisible(false);
        this->isVisible = false;
        _currenTime = 0.0f;
    }
    
}

void RotatingShell::shellAnimationDone(CCNode * pSender)
{
    if(_shell->numberOfRunningActions() <= 0)
    {
        _shell->runAction(_rotate);
    }
}