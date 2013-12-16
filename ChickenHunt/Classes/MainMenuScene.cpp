#include "MainMenuScene.h"
#include "GameScene.h"

USING_NS_CC;

CCScene* MainMenu::scene()
{
    
        
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainMenu *layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    //CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("MainMenu-ipadhd.plist");
    //_menuBatchNode = CCSpriteBatchNode::create("MainMenu-ipadhd.png");
    
    //this->addChild(_menuBatchNode);
    
    auto CCSprite * sprite;
    sprite = CCSprite::create("mainmenucolor.png");
    sprite->setRotation(90.0f);
    sprite->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
    this->addChild(sprite,0);
    
    sprite = CCSprite::create("mainmenubull.png");
    sprite->setPosition(ccp(visibleSize.width/2-sprite->boundingBox().size.width/2.5,visibleSize.height-sprite->boundingBox().size.height/2));
    sprite->setScale(.95f);
    this->addChild(sprite);
    
    //sprite = CCSprite::createWithSpriteFrameName("playButton.png");
    //sprite->setPosition(ccp(visibleSize.width/2+sprite->boundingBox().size.width/2,visibleSize.height/2+sprite->boundingBox().size.height/2));
    //_menuBatchNode->addChild(sprite);
    
    
    CCMenuItemImage *playbutton = CCMenuItemImage::create("playButton.png","playButton.png",this,menu_selector(MainMenu::playButtonCallback));
    playbutton->setPosition(ccp(visibleSize.width/2+playbutton->boundingBox().size.width/2,visibleSize.height/2+playbutton->boundingBox().size.height/2));
    
    CCMenu* playMenu = CCMenu::create(playbutton, NULL);
    playMenu->setPosition(CCPointZero);
    this->addChild(playMenu, 1);
    
    CCMenuItemImage *quitbutton = CCMenuItemImage::create("quitbutton.png","quitbutton.png",this,menu_selector(MainMenu::menuCloseCallback));
    
    quitbutton->setPosition(ccp(visibleSize.width/2+quitbutton->boundingBox().size.width/2,visibleSize.height/4));
    
    CCMenu* quitMenu = CCMenu::create(quitbutton, NULL);
    quitMenu->setPosition(CCPointZero);
    this->addChild(quitMenu, 1);
    
    
    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    

    
    
    return true;
}

void MainMenu::playButtonCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->pushScene(GameScene::scene());
}

void MainMenu::menuCloseCallback(CCObject* pSender)
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
