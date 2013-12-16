
//
//  EndGameScene.h
//  ChickenHunt
//
//  Created by Gerald Quick on 12/11/13.
//
//

#ifndef __ChickenHunt__EndGameScene__
#define __ChickenHunt__EndGameScene__
#include "cocos2d.h"

class EndGameScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(EndGameScene);
};

#endif /* defined(__ChickenHunt__GameScene__) */
