//
//  RotatingShell.h
//  ChickenHunt
//
//  Created by Gerald Quick on 12/15/13.
//
//

#ifndef __ChickenHunt__RotatingShell__
#define __ChickenHunt__RotatingShell__

#include "cocos2d.h"

class RotatingShell :  public cocos2d::CCObject
{
private:
    float _currenTime;
    float _posX;
    float _posY;
    float _velocity;
    cocos2d::CCSequence * _rotate;
    void shellAnimationDone(cocos2d::CCNode * pSender);
public:
    bool isVisible;
    RotatingShell(void);
    ~RotatingShell(void);
    cocos2d::CCSprite * _shell;
    void update(float dt);
    
};

#endif /* defined(__ChickenHunt__RotatingShell__) */
