//
//  GameScene.h
//  ChickenHunt
//
//  Created by Gerald Quick on 12/11/13.
//
//

#ifndef __ChickenHunt__GameScene__
#define __ChickenHunt__GameScene__

#include "cocos2d.h"
#include "CCParallaxNodeExtras.h"
#include "Chicken.h"
#include "FlyingChicken.h"
#include "GameLogic.h"
#include "Player.h"
#include "RotatingShell.h"

class GameScene : public cocos2d::CCLayer
{
private:
    Player * _player;
    GameLogic * _gameLogic;
    int _score;
    CCSize visibleSize;
    CCString * strScore;
    CCSprite *_sky;
    CCSprite *_background1;
    CCSprite *_background2;
    CCSprite *_background3;
    CCSprite *_background4;
    CCPoint _skyPos;
    CCLabelBMFont * _scoreDisplay;
    float _backgroundPointsPerSecX;
    CCSpriteBatchNode * _gameBatchNode;
    CCSpriteBatchNode * _flyingChickenNode;
    CCSpriteBatchNode * _shellsNode;
    CCSpriteBatchNode * _GUINode;
    Chicken * foreChick;
    FlyingChicken * flyingChicken;
    int _currentAmmo;
    void setupSprites();
    void setupBackground();
    void initPlayer();
    void initGUI();
    void createObjectPools();
    void spawnChicken();
    CCArray * _rotatingShells;
    CCArray * _foregroundChickenPool;
    CCArray * _flyingChickenPool;
    CCArray * _flyingChickens;
    CCArray * _foregroundChickens;
    float _spawnTime;
    //RotatingShell * rotatingShells[3];
public:
    ~GameScene(void);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    CCParallaxNodeExtras *_backgroundNode;
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    virtual void didAccelerate(CCAcceleration* pAccelerationValue);
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void update(float dt);
    void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
    void addScore(int value);
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
    RotatingShell * _rotatingShell;
};

#endif /* defined(__ChickenHunt__GameScene__) */
