//
//  Chicken.cpp
//  ChickenHunt
//
//  Created by Gerald Quick on 12/12/13.
//
//

#include "Chicken.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Chicken::Chicken()
{
    
    _bDead = false;
    //_bFlying = false;
}

Chicken::~Chicken()
{}

bool Chicken::isDead()
{
    return _bDead;
}
void Chicken::show()
{
    _sprite->runAction(_show);
}

void Chicken::hide()
{
    
}
bool Chicken::isVisible()
{
    return _bVisible;
}
void Chicken::setVisible(bool value)
{
    _bVisible = value;
    _sprite->setVisible(_bVisible);
}
 void Chicken::createAnimations()
{
    
    CCAnimation* animation;
    CCSpriteFrame * frame;
    
    //create CCAnimation object
    animation = CCAnimation::create();
    CCString * name;
    for(int i = 1; i <= 19; i++) {
        name = CCString::createWithFormat("mhfore%i.png", i);
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animation->addSpriteFrame(frame);
    }
    
    animation->setDelayPerUnit(3 / 19.0f);
    animation->setRestoreOriginalFrame(true);
    _show = CCSequence::create(
                                CCAnimate::create(animation),
                                CCCallFuncN::create(this, callfuncN_selector(Chicken::showAnimationDone)),
                                NULL);
    _show->retain();
    
    animation = CCAnimation::create();
    //CCString * name;
    for(int i = 19; i >= 1; i--) {
        name = CCString::createWithFormat("mhfore%i.png", i);
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animation->addSpriteFrame(frame);
    }
    
    animation->setDelayPerUnit(3 / 19.0f);
    animation->setRestoreOriginalFrame(true);
    _hide = CCSequence::create(
                            CCAnimate::create(animation),
                            CCCallFuncN::create(this, callfuncN_selector(Chicken::hideAnimationDone)),
                            NULL);
    _hide->retain();
    
    animation = CCAnimation::create();
    //CCString * name;
    for(int i = 1; i <= 6; i++) {
        name = CCString::createWithFormat("mhforedead%i.png", i);
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animation->addSpriteFrame(frame);
    }
    
    animation->setDelayPerUnit(3 / 19.0f);
    animation->setRestoreOriginalFrame(true);
    _die = CCSequence::create(
                            CCAnimate::create(animation),
                            CCCallFuncN::create(this, callfuncN_selector(Chicken::dieAnimationDone)),
                            NULL);
    _die->retain();
    
    
    
    
    
}
void Chicken::die()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("chickDie.mp3");
    _bDead = true;
    if(_sprite->numberOfRunningActions() > 0)
        _sprite->stopAllActions();
    _sprite->runAction(_die);
}
void Chicken::showAnimationDone(cocos2d::CCNode *pSender)
{
    if (!_bDead) {
        _sprite->runAction(_hide);
    }
}

void Chicken::hideAnimationDone(cocos2d::CCNode *pSender)
{
    setVisible(false);
}

void Chicken::dieAnimationDone(cocos2d::CCNode *pSender)
{
    _bDead = true;
    setVisible(false);
}

void Chicken::updatePosition()
{
    
}