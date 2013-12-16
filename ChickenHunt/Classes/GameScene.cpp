//
//  GameScene.cpp
//  ChickenHunt
//
//  Created by Gerald Quick on 12/11/13.
//
//

#include "GameScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    _spawnTime = 0.0f;
    _score = 0;
    _currentAmmo = 2;
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    _flyingChickens = CCArray::createWithCapacity(10);
    _foregroundChickens = CCArray::createWithCapacity(2);
    _foregroundChickens->retain();
    //setup sprite sheets
    this->setupSprites();
    //setup paralax background
    //this->setupBackground();
    _backgroundNode = CCParallaxNodeExtras::node();
    this->addChild(_backgroundNode,-1);
    
    auto _sky = CCSprite::create("sky.png");
    auto _background1 = CCSprite::create("background1.png");
    auto _background2 = CCSprite::create("background2.png");
    auto _background3 = CCSprite::create("background3.png");
    auto _background4 = CCSprite::create("background4.png");
    
    //background scrolling speeds
    CCPoint skySpeed = ccp(0.05,0);
    CCPoint bg1Speed = ccp(.105,0);
    CCPoint bg2Speed = ccp(.08,0);
    CCPoint bg3Speed = ccp(.12,0);
    CCPoint bg4Speed = ccp(.5,0);
    
    
    _sky->setScale(1.2f);
    _background1->setScale(1.2f);
    _background2->setScale(1.2f);
    _background3->setScale(1.2f);
    _background4->setScale(1.2f);
    
    //add children to background node
    _backgroundNode->addChild(_sky, 0, skySpeed, ccp(visibleSize.width,visibleSize.height/2));
    // _backgroundNode->addChild(_background1,1,bg1Speed, ccp(visibleSize.width,visibleSize.height/2));
    _backgroundNode->addChild(_background2,2,bg2Speed, ccp(visibleSize.width,visibleSize.height/2));
    _backgroundNode->addChild(_background3,3,bg3Speed, ccp(visibleSize.width,visibleSize.height/2.5));
    _backgroundNode->addChild(_background4,4,bg4Speed, ccp(_background4->boundingBox().size.width ,visibleSize.height/2));
    
    _gameLogic = new GameLogic();
    //setup Player
    this->initPlayer();
    _player->_ammosprite->setPosition(ccp(visibleSize.width/2,origin.y + _player->_ammosprite->boundingBox().size.height/2));
    _player->_reloadsprite->setPosition((ccp(visibleSize.width/2 + _player->_ammosprite->boundingBox().size.width,origin.y + _player->_reloadsprite->boundingBox().size.height/2)));
    _player->_shells->setPosition(ccp(visibleSize.width/2-_player->_shells->boundingBox().size.width/2,visibleSize.height/12));
    _player->_shells2->setPosition(ccp(visibleSize.width/2+_player->_shells->boundingBox().size.width/2,visibleSize.height/12));
    this->addChild(_player->_ammosprite,5);
    this->addChild(_player->_reloadsprite,5);
    this->addChild(_player->_shells,5);
    this->addChild(_player->_shells2,5);
    //setup gui
    //this->initGUI();
    _gameLogic->timerGUI = CCSprite::createWithSpriteFrameName("timerbox.png");
    
    _gameLogic->initTimer(DEFALUT_TIMER_VALUE, visibleSize);
    _gameLogic->setTimerPosition(visibleSize.width/2, visibleSize.height - _gameLogic->timerGUI->boundingBox().size.height/2);
    this->addChild(_gameLogic->timerGUI,4);
    this->addChild(_gameLogic->timerValue,5);
    _rotatingShells = CCArray::createWithCapacity(3);
    _rotatingShells->retain();
    
    for(int i=0;i<4;i++)
    {
        _rotatingShell = new RotatingShell();
        _rotatingShell->_shell = CCSprite::createWithSpriteFrameName("shell0.png");
        _rotatingShell->_shell->setVisible(false);
        _rotatingShell->isVisible = false;
        if(i % 2 == 0)
        {
            _rotatingShell->_shell->setPosition(_player->_shells2->getPosition());
        }else
        {
            _rotatingShell->_shell->setPosition(_player->_shells->getPosition());
        }
        _rotatingShells->addObject(_rotatingShell);
        this->addChild(_rotatingShell->_shell ,5);
    }
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(GameScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    this->createObjectPools();
    
    foreChick = new Chicken();
    foreChick->_sprite = CCSprite::createWithSpriteFrameName("mhfore1.png");
    this->addChild(foreChick->_sprite,4);
    foreChick->createAnimations();
    foreChick->_sprite->setPosition(CCPoint(ccp(visibleSize.width /2,foreChick->_sprite->boundingBox().size.height/2)));
    foreChick->setVisible(true);
    foreChick->show();

    flyingChicken = new FlyingChicken(LARGE,true,LEFT);
    flyingChicken->_sprite = CCSprite::createWithSpriteFrameName("chickFlyLarge0.png");
    flyingChicken->createAnimations();
    flyingChicken->_sprite->setPosition(ccp(visibleSize.width/1.5,visibleSize.height/1.5));
    this->addChild(flyingChicken->_sprite);
    flyingChicken->setVisible(true);
    flyingChicken->Fly();
    _flyingChickens->addObject(flyingChicken);
    _flyingChickens->retain();
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    //CCLabelTTF* pLabel = CCLabelTTF::create("Game Scene", "Arial", 24);
    
    // position the label on the center of the screen
    //pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
    //                        origin.y + visibleSize.height - pLabel->getContentSize().height));
    auto CCString * value = CCString::createWithFormat("Score:%i",_score);
    _gameLogic->_scoreDisplay =CCLabelBMFont::create(value->getCString(), "fonts-ipadhd.fnt", visibleSize.width * 0.3f);
    //_scoreDisplay = CCLabelBMFont::create(value->getCString(), "fonts-ipadhd.fnt", visibleSize.width * 0.3f);
    _gameLogic->_scoreDisplay->setAnchorPoint(ccp(1,0.5));
    _gameLogic->_scoreDisplay->setPosition(ccp(visibleSize.width * 0.8f, visibleSize.height * 0.94f));
    this->addChild(_gameLogic->_scoreDisplay,5);
    
    // add the label as a child to this layer
   // this->addChild(pLabel, 1);
    this->setAccelerometerEnabled(true);
    this->setTouchEnabled(true);
    this->scheduleUpdate();
    
    
    return true;
}
void GameScene::initGUI()
{
    _gameLogic->timerGUI = CCSprite::createWithSpriteFrameName("timerbox.png");
    
    _gameLogic->initTimer(DEFALUT_TIMER_VALUE, visibleSize);
    _gameLogic->setTimerPosition(500, 500);
    this->addChild(_gameLogic->timerGUI,4);
    this->addChild(_gameLogic->timerValue,5);
}
void GameScene::initPlayer()
{
    _player = new Player();
    
}

void GameScene::spawnChicken()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    int flyCount = _flyingChickens->count();
    int foreCount = _foregroundChickens->count();
    
    if (flyCount >=4) {
        return;
    }
    
    if (flyCount < 5) {
        for (int i=0; i<_flyingChickenPool->count(); i++) {
            FlyingChicken * fc = (FlyingChicken *)_flyingChickenPool->objectAtIndex(i);
            if (!fc->isVisible()) {
                fc->setVisible(true);
                float y = rand() % (int) visibleSize.height * 1.0f;
                fc->_sprite->setPosition(ccp(visibleSize.width * 1.0f,y));
                fc->Fly();
                _flyingChickens->addObject(fc);
                break;
            }
            
            
            
        }
    }
}

void GameScene::createObjectPools()
{
    _flyingChickenPool = CCArray::createWithCapacity(9);
    _foregroundChickenPool = CCArray::createWithCapacity(2);
    
    
    
    
    for (int i=0; i<2; i++) {
        Chicken * tempForeChick = new Chicken();
        tempForeChick->_sprite = CCSprite::createWithSpriteFrameName("mhfore1.png");
        this->addChild(tempForeChick->_sprite,4);
        tempForeChick->createAnimations();
        tempForeChick->_sprite->setPosition(CCPoint(ccp(visibleSize.width /2,tempForeChick->_sprite->boundingBox().size.height/2)));
        tempForeChick->setVisible(false);
        
        _foregroundChickenPool->addObject(tempForeChick);
    }
    
    _foregroundChickenPool->retain();
    
    
    FlyingChicken * tempChicken;
    for (int i =0; i<9; i++) {
        
        
        switch (rand() % 3) {
            case 1:
                tempChicken = new FlyingChicken(LARGE,false, LEFT);
                tempChicken->_sprite = CCSprite::createWithSpriteFrameName("chickFlyLarge0.png");
                break;
            case 2:
                tempChicken = new FlyingChicken(MED,false, LEFT);
                tempChicken->_sprite = CCSprite::createWithSpriteFrameName("chickFlyMed0.png");
                break;
            case 3:
                tempChicken = new FlyingChicken(SMALL,false, LEFT);
                tempChicken->_sprite = CCSprite::createWithSpriteFrameName("chickFlySmall0.png");
                break;
            default:
                tempChicken = new FlyingChicken(LARGE,false, LEFT);
                tempChicken->_sprite = CCSprite::createWithSpriteFrameName("chickFlyLarge0.png");
                break;
        }
        
        
        tempChicken->createAnimations();
        tempChicken->_sprite->setPosition(ccp(visibleSize.width/1.5,visibleSize.height/1.5));
        this->addChild(tempChicken->_sprite);
        
        _flyingChickenPool->addObject(tempChicken);
    }
    _flyingChickenPool->retain();
    //flyingChicken = new FlyingChicken(LARGE,true,LEFT);
    
    //flyingChicken->setVisible(true);
    //flyingChicken->Fly();
}

void GameScene::setupBackground()
{
    
    _backgroundNode = CCParallaxNodeExtras::node();
    this->addChild(_backgroundNode,-1);
    
    auto _sky = CCSprite::create("sky.png");
    auto _background1 = CCSprite::create("background1.png");
    auto _background2 = CCSprite::create("background2.png");
    auto _background3 = CCSprite::create("background3.png");
    auto _background4 = CCSprite::create("background4.png");
    
    //background scrolling speeds
    CCPoint skySpeed = ccp(0.05,0);
    CCPoint bg1Speed = ccp(.105,0);
    CCPoint bg2Speed = ccp(.08,0);
    CCPoint bg3Speed = ccp(.12,0);
    CCPoint bg4Speed = ccp(.5,0);
    
    
    _sky->setScale(1.2f);
    _background1->setScale(1.2f);
    _background2->setScale(1.2f);
    _background3->setScale(1.2f);
    _background4->setScale(1.2f);
    
    //add children to background node
    _backgroundNode->addChild(_sky, 0, skySpeed, ccp(visibleSize.width,visibleSize.height/2));
    // _backgroundNode->addChild(_background1,1,bg1Speed, ccp(visibleSize.width,visibleSize.height/2));
    _backgroundNode->addChild(_background2,2,bg2Speed, ccp(visibleSize.width,visibleSize.height/2));
    _backgroundNode->addChild(_background3,3,bg3Speed, ccp(visibleSize.width,visibleSize.height/2.5));
    _backgroundNode->addChild(_background4,4,bg4Speed, ccp(_background4->boundingBox().size.width ,visibleSize.height/2));
    
}
void GameScene::setupSprites()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Anim-MH-Foreground-ipadhd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Anim-MH-Flying-ipadhd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Anim-Shells-ipadhd.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GUI-ipadhd.plist");
    _gameBatchNode = CCSpriteBatchNode::create("Anim-MH-Foreground-ipadhd.png");
    _flyingChickenNode = CCSpriteBatchNode::create("Anim-MH-Flying-ipadhd.png");
    _shellsNode = CCSpriteBatchNode::create("Anim-Shells-ipadhd.png");
    _GUINode = CCSpriteBatchNode::create("GUI-ipadhd.png");
    this->addChild(_gameBatchNode);
    this->addChild(_flyingChickenNode);
    this->addChild(_shellsNode);
    this->addChild(_GUINode);
    
}
void GameScene::update(float dt)
{
    _skyPos = _backgroundNode->getPosition();
    CCPoint backgroundScrollVert = ccp(_backgroundPointsPerSecX,0);
    if(_skyPos.x >= -11900.0 && _skyPos.x < 1)
    {
    //    backgroundScrollVert = ccp(-1000, 0);
        _backgroundNode->setPosition(ccpAdd(_backgroundNode->getPosition(), ccpMult(backgroundScrollVert, dt)));
    }else
    {
        if(_skyPos.x <= -11900)
        {
            if (_backgroundPointsPerSecX > 0.0f) {
                _backgroundNode->setPosition(ccpAdd(_backgroundNode->getPosition(), ccpMult(backgroundScrollVert, dt)));
            }
        }
        if (_skyPos.x >=1) {
            if (_backgroundPointsPerSecX < 0.0f) {
                _backgroundNode->setPosition(ccpAdd(_backgroundNode->getPosition(), ccpMult(backgroundScrollVert, dt)));
            }
        }
    }
    
    for(int i=0;i<4;i++)
    {
        RotatingShell *s =  (RotatingShell *)_rotatingShells->objectAtIndex(i);
        
        if (s->isVisible) {
            if(s->_shell->getPositionY()<0)
                s->isVisible = false;
            s->update(dt);
        }
        
    }
    
    _gameLogic->update(dt);
    
    if (_spawnTime >=1.0f) {
        this->spawnChicken();
        _spawnTime = 0.0f;
    }else
    {
        _spawnTime += dt;
    }
    
}

void GameScene::ccTouchesBegan(CCSet* pTouches, CCEvent* event)
{
    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    if (_player->getAmmo() <=0) {
        if(touch)
        {
            if(_player->_reloadsprite->boundingBox().containsPoint(touch->getLocation()))
            {
                _player->reload();
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("shotgunReload.mp3");
            }else
            {
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("shotgunempty.mp3");
            }
        }
       
    }else
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("shotgunfire.mp3");
        _player->shoot();
        
        RotatingShell *s = (RotatingShell *)_rotatingShells->objectAtIndex(0);
        if (_player->getAmmo() == 1) {
            
            if(!s->isVisible)
            {
                s->_shell->setPosition(_player->_shells->getPosition());
                s->isVisible = true;
                s->_shell->setVisible(true);
            }
        }else
        {
            s = (RotatingShell *)_rotatingShells->objectAtIndex(1);
            s->_shell->setPosition(_player->_shells2->getPosition());
            s->isVisible = true;
            s->_shell->setVisible(true);
        }
        
        
        
        if (touch) {
            CCLog("Touch: x: %f, y: %f",touch->getLocation().x,touch->getLocation().y);
            
            for (int i =0; i<_flyingChickens->count(); i++) {
                FlyingChicken * c = (FlyingChicken *)_flyingChickens->objectAtIndex(i);
                if (c->_sprite->boundingBox().containsPoint(touch->getLocation())) {
                    c->die();
                    switch (c->chickenType) {
                        case LARGE:
                            _player->addScore(50);
                            break;
                        case MED:
                            _player->addScore(75);
                            break;
                        case SMALL:
                            _player->addScore(100);
                            break;
                        default:
                            break;
                    }
                    _gameLogic->updateScore(_player->getScore());
                    
                    
                    _flyingChickens->removeObjectAtIndex(i);
                    //CC_SAFE_DELETE(c);
                }
            }
            
            if(foreChick->_sprite->boundingBox().containsPoint(touch->getLocation()))
            {
                if(!foreChick->isDead())
                {
                    foreChick->die();
                    _player->addScore(50);
                    _gameLogic->updateScore(_player->getScore());
                    
                }
            }
        }
    }
    
    
    
}

GameScene::~GameScene()
{
    CC_SAFE_DELETE(_background1);
    CC_SAFE_DELETE(_background2);
    CC_SAFE_DELETE(_background3);
    CC_SAFE_DELETE(_background4);
    CC_SAFE_DELETE(_backgroundNode);
    CC_SAFE_DELETE(_flyingChickenNode);
    CC_SAFE_DELETE(_gameBatchNode);
    CC_SAFE_DELETE(_gameLogic);
    CC_SAFE_DELETE(_GUINode);
    CC_SAFE_DELETE(_player);
    CC_SAFE_DELETE(_rotatingShell);
    CC_SAFE_DELETE_ARRAY(_rotatingShells);
    CC_SAFE_DELETE(_sky);
    
    
}
void GameScene::addScore(int v)
{
    _score += v;
    auto CCString * value = CCString::createWithFormat("Score:%i", _player->getScore());
    _scoreDisplay->setString(value->getCString());
}
void GameScene::didAccelerate(CCAcceleration* pAccelerationValue) {
#define KFILTERINGFACTOR 0.1
#define KRESTACCELX -0.8
#define KSHIPMAXPOINTSPERSEC (winSize.width*2)
#define KMAXDIFFX 0.2
    
    double rollingX;
    
    // Cocos2DX inverts X and Y accelerometer depending on device orientation
    // in landscape mode right x=-y and y=x !!! (Strange and confusing choice)
    pAccelerationValue->y = -pAccelerationValue->x;
    rollingX = (pAccelerationValue->y * KFILTERINGFACTOR) + (rollingX * (1.0 - KFILTERINGFACTOR));
    float accelX = pAccelerationValue->y - rollingX;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float accelDiff = accelX - KRESTACCELX;
    float accelFraction = accelDiff / KMAXDIFFX;
    _backgroundPointsPerSecX = KSHIPMAXPOINTSPERSEC * accelFraction;
    //CCLog("Accel: %f",_backgroundPointsPerSecX);
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
