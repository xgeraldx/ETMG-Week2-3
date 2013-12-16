//
//  Player.h
//  ChickenHunt
//
//  Created by Gerald Quick on 12/14/13.
//
//

#ifndef __ChickenHunt__Player__
#define __ChickenHunt__Player__
#include "cocos2d.h"


class Player : public cocos2d::CCObject
{
private:
    int _currentScore;
    int _currentAmmo;
    int _kills;
    int _misses;
    int _streaks;
    void initPlayerGUI();
    void setupAnimations();
    
    cocos2d::CCSequence * _canReload;
    cocos2d::CCSequence * _cannotReload;
    cocos2d::CCSequence * _rotateShells;
    void canReloadAnimationDone(cocos2d::CCNode * pSender);
    void cannotReloadAnimationDone(cocos2d::CCNode * pSender);
    void shellAnimationDone(cocos2d::CCNode * pSender);
public:

    cocos2d::CCSprite * _reloadsprite;
    cocos2d::CCSprite * _ammosprite;
    cocos2d::CCSprite * _shells;
    cocos2d::CCSprite * _shells2;
    Player(void);
    ~Player(void);
    int getScore();
    void addScore(int value);
    int getAmmo();
    void setAmmo(int value);
    void addStreaks(int value);
    void addMisses(int value);
    void reset();
    void shoot();
    void reload();
    bool bReloadReady;
    void animationEmptyShell(float dt);
    
};

#endif /* defined(__ChickenHunt__Player__) */
