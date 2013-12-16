//
//  FlyingChicken.cpp
//  ChickenHunt
//
//  Created by Gerald Quick on 12/13/13.
//
//

#include "FlyingChicken.h"

using namespace cocos2d;

FlyingChicken::FlyingChicken(CHICKENTYPE cType, bool vis, FLYINGDIRECTION direction)
{
    chickenType = cType;
    _bDead = false;
    _bVisible = vis;
    flyingDirection = direction;
}

FlyingChicken::~FlyingChicken()
{
    this->release();
}

void FlyingChicken::createAnimations()
{
    
    CCAnimation* animation;
    CCSpriteFrame * frame;
        //create CCAnimation object
    animation = CCAnimation::create();
    CCString * name;
    for(int i = 0; i <= 12; i++) {
        switch (chickenType) {
            case LARGE:
                name = CCString::createWithFormat("chickFlyLarge%i.png", i);
                break;
            case MED:
                name = CCString::createWithFormat("chickFlyMed%i.png", i);
                break;
            case SMALL:
                name = CCString::createWithFormat("chickFlySmall%i.png", i);
                break;
            default:
                break;
        }
        
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animation->addSpriteFrame(frame);
    }
    animation->setLoops(10);
    animation->setDelayPerUnit(1 / 13.0f);
    animation->setRestoreOriginalFrame(true);
    _flying = CCSequence::create(CCSpawn::createWithTwoActions(CCMoveBy::create(8.0f, ccp(-1500.0f,0.0f)),CCAnimate::create(animation))
                                 ,
                               CCCallFuncN::create(this, callfuncN_selector(FlyingChicken::flyingAnimationDone)),
                               NULL);
    _flying->retain();
    
    animation = CCAnimation::create();
    
    for(int i = 0; i <= 7; i++) {
        switch (chickenType) {
            case LARGE:
                name = CCString::createWithFormat("chickFlyDieLarge%i.png", i);
                break;
            case MED:
                name = CCString::createWithFormat("chickFlyDieMed%i.png", i);
                break;
            case SMALL:
                name = CCString::createWithFormat("chickFlyDieSmall%i.png", i);
                break;
            default:
                break;
        }
        
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animation->addSpriteFrame(frame);
    }
    
    animation->setDelayPerUnit(1 / 7.0f);
    animation->setRestoreOriginalFrame(false);
    _die = CCSequence::create(CCSpawn::createWithTwoActions(CCMoveBy::create(2.0f, ccp(0.0f,-800.0f)), CCAnimate::create(animation)),
                                 CCCallFuncN::create(this, callfuncN_selector(FlyingChicken::dieAnimationDone)),
                                 NULL);
    _die->retain();
}
void FlyingChicken::Fly()
{
    _sprite->runAction(_flying);
}
void FlyingChicken::die()
{
    if (_sprite->numberOfRunningActions() >0) {
        _sprite->stopAllActions();
    }
    _sprite->runAction(_die);
}

void FlyingChicken::setPositionMod(float xPosMod)
{
    _sprite->setPosition(CCPoint(ccp(xPosMod,_sprite->getPositionY())));
    
    
}

void FlyingChicken::update(float dt)
{
    if(flyingDirection == LEFT)
    {
        _sprite->setPositionX(5.0f*dt);
        
    }else
    {
        _sprite->setPositionX(-5.0f*dt);
        
    }
    
}
void FlyingChicken::dieAnimationDone(cocos2d::CCNode *pSender)
{
    setVisible(false);
}
void FlyingChicken::flyingAnimationDone(CCNode * pSender)
{
    if (_sprite->numberOfRunningActions() <=0) {
        _sprite->runAction(_flying);
    }
}