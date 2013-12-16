//
//  Chicken.h
//  ChickenHunt
//
//  Created by Gerald Quick on 12/12/13.
//
//

#ifndef __ChickenHunt__Chicken__
#define __ChickenHunt__Chicken__

#include "cocos2d.h"


class Chicken : public cocos2d::CCObject
{

private:
    
    cocos2d::CCSequence * _show;
    cocos2d::CCSequence * _hide;
    
protected:
    bool _bDead;
    bool _bVisible;
    cocos2d::CCSequence * _die;
public:
    
    Chicken();
    ~Chicken();
    
    cocos2d::CCSprite * _sprite;
    
    virtual void createAnimations();
    bool isDead();
    bool isVisible();
    void showAnimationDone(cocos2d::CCNode * pSender);
    void hideAnimationDone(cocos2d::CCNode * pSender);
    void dieAnimationDone(cocos2d::CCNode * pSender);
    void show();
    void hide();
    void setVisible(bool);
    void updatePosition();
    virtual void die();
    
};


#endif /* defined(__ChickenHunt__Chicken__) */
