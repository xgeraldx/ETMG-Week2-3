//
//  Player.cpp
//  ChickenHunt
//
//  Created by Gerald Quick on 12/14/13.
//
//

#include "Player.h"

USING_NS_CC;

Player::Player() 
{
    _currentAmmo = 2;
    _currentScore = 0;
    _kills = 0;
    _streaks = 0;
    initPlayerGUI();
    setupAnimations();
}

Player::~Player()
{}

void Player::initPlayerGUI()
{
    _ammosprite = CCSprite::createWithSpriteFrameName("ammo.png");
    _reloadsprite = CCSprite::createWithSpriteFrameName("reload.png");
    _shells = CCSprite::createWithSpriteFrameName("shell0.png");
    _shells2 = CCSprite::createWithSpriteFrameName("shell0.png");
}
void Player::setupAnimations()
{

    CCAnimation* animation;
    CCSpriteFrame * frame;
    
    //create CCAnimation object
    animation = CCAnimation::create();
    //CCString * name;
    
    frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("reload.png");
    animation->addSpriteFrame(frame);
    frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("reloadready.png");
    animation->setDelayPerUnit(.5 / 2.0f);
    animation->setRestoreOriginalFrame(false);
    _cannotReload = CCSequence::create(
                                 CCAnimate::create(animation),
                                 CCCallFuncN::create(this, callfuncN_selector(Player::canReloadAnimationDone)),
                                 NULL);
    _cannotReload->retain();
    
    animation = CCAnimation::create();
    frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("reloadready.png");
    animation->addSpriteFrame(frame);
    frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("reload.png");
    animation->setDelayPerUnit(.5 / 2.0f);
    animation->setRestoreOriginalFrame(false);
    _canReload = CCSequence::create(
                                    CCAnimate::create(animation),
                                    CCCallFuncN::create(this, callfuncN_selector(Player::cannotReloadAnimationDone)),
                                    NULL);
    _canReload->retain();
    
    //create CCAnimation object
    animation = CCAnimation::create();
    CCString * name;
    for(int i = 0; i <= 20; i++) {
        name = CCString::createWithFormat("shell%i.png", i);
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        animation->addSpriteFrame(frame);
    }
    
    animation->setDelayPerUnit(.5 / 21.0f);
    animation->setRestoreOriginalFrame(false);
    animation->setLoops(10);
    _rotateShells = CCSequence::create(
                                 CCAnimate::create(animation),
                                 CCCallFuncN::create(this, callfuncN_selector(Player::shellAnimationDone)),
                                 NULL);
    _rotateShells->retain();
    
}
int Player::getScore()
{
    return _currentScore;
}

void Player::addScore(int value)
{
    _currentScore += value;
}

int Player::getAmmo()
{
    return _currentAmmo;
}

void Player::setAmmo(int value)
{
    _currentAmmo = value;
}

void Player::addStreaks(int value)
{
    _streaks += value;
}

void Player::shoot()
{
    //_shells->runAction(_rotateShells);
    _currentAmmo--;
    if (_currentAmmo <= 0) {
        _shells2->setVisible(false);
        bReloadReady = true;
        _reloadsprite->runAction(_canReload);
    }else
    {
        _shells->setVisible(false);
    }
    
}

void Player::reload()
{
    _currentAmmo = 2;
    bReloadReady = false;
    _reloadsprite->runAction(_cannotReload);
    _shells->setVisible(true);
    _shells2->setVisible(true);
}
void Player::addMisses(int value)
{
    _misses += value;
}

void Player::reset()
{
    _currentAmmo = 2;
    _currentScore = 0;
    _kills = 0;
    _streaks = 0;
    bReloadReady =false;
    
}
void Player::animationEmptyShell(float dt)
{
    
}
void Player::cannotReloadAnimationDone(cocos2d::CCNode *pSender)
{

}
void Player::canReloadAnimationDone(cocos2d::CCNode *pSender)
{

}
void Player::shellAnimationDone(cocos2d::CCNode *pSender)
{

}