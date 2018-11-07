//
//  GameLayer.cpp
//  testgozapreader
//
//  Created by zhaojm on 14/12/19.
//
//

#include "GameLayer.h"



#include "GozapSprite.h"
#include "GozapScene.h"
#include "SlimeGroup.h"
#include "FilterSprite.h"

USING_NS_CC;

GameLayer::~GameLayer()
{
    this->unscheduleUpdate();
    this->slimeGroup->release();
}

Scene* GameLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = GameLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameLayer::init()
{
    if ( !TouchLayer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//    Size winSize = Director::getInstance()->getWinSize();
//    Size frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
//
//    CCLOG("visibleSize, w=%f, h=%f", visibleSize.width, visibleSize.height);
//    CCLOG("winSize, w=%f, h=%f", winSize.width, winSize.height);
//    CCLOG("frameSize, w=%f, h=%f", frameSize.width, frameSize.height);
    
//    auto mylabel = cocos2d::Label::create("hello world", "arial", 48);
//    mylabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
//    this->addChild(mylabel);
    
    this->_debugDrawNode = DrawNode::create();
    this->addChild(this->_debugDrawNode, 10);

    
    
    this->scheduleUpdate();
   
    
    this->setAnchorPoint(Vec2(0, 0));
    
    

    auto layer = GozapScene::createWithJsonFile("res/changjing3.json");
    layer->setAnchorPoint(Vec2(0, 0));
    this->addChild(layer);
    this->setContentSize(layer->getContentSize() * layer->getScaleFactor());
    CCLOG("GameLayer  contentsize, w=%f, h=%f", this->getContentSize().width, this->getContentSize().height);
    this->setPosition(layer->getPosition());
    layer->setPosition(Vec2(0, 0));
    

    this->scaleFactor = Director::getInstance()->getOpenGLView()->getFrameSize().height  / layer->getModel()->getScreenH() ;
    this->_floor = layer->getModel()->getFloor() * scaleFactor;
    this->_floorH = layer->getModel()->getFloorH() * scaleFactor;
    
    

//    auto mySprite = GozapSprite::createWithJsonFile("res/youwentideceshi1.json");
//    this->addChild(mySprite);
//    mySprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
//    mySprite->runActionByName("all", true);
    
    
    this->slime = Slime::createWithJsonFile("res/hongsedonghua.json");
    this->addChild(slime);
    slime->setPosition(Vec2(this->getContentSize().width  , this->getContentSize().height) );
    slime->setPosition(Vec2(400,400));
//    slime->setAnchorPoint(Vec2(0,0));
    slime->runActionByName("待机", true);
//    slime->setDisplayFrameByIndex(103);
    this->slimeTestPoint = slime->getPosition();
    
    
//    this->slimeGroup = SlimeGroup::create();
//    this->slimeGroup->addToNode(this, Vec2(visibleSize.width / 2, visibleSize.height / 2));
//    this->slimeGroup->retain();
//
    
    // shader sprite
//    Sprite *_sprite1;
//    _sprite1 = FilterSprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("i_1"));
//    this->addChild(_sprite1);
//    _sprite1->setPosition(200, 200);
//    GLfloat  filterMat[16]= {
//        0.3f,  0.3f,  0.3f,  0.0f,
//        0.59f, 0.59f, 0.59f, 0.59f,
//        0.11f, 0.11f, 0.11f, 0.0f,
//        0.0f,  0.0f,  0.0f,  1.0f,
//    };
//    
//    dynamic_cast<FilterSprite*>(_sprite1)->setFilterMat(filterMat);
    
    
    // 键盘响应事件
    // only available on desktop and android
//    this->setKeyboardEnabled(true);
//    this->setKeypadEnabled(true);
    auto listener=EventListenerKeyboard::create();
    listener->onKeyPressed=CC_CALLBACK_2(GameLayer::onKeyPressed,this);
    listener->onKeyReleased=CC_CALLBACK_2(GameLayer::onKeyReleased,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    
    
    return true;
}

void GameLayer::onSingleCLick(Point point)
{
    CCLOG("GameLayer::onSingleCLick");
//    CCLOG("point.y=%f",);
    Point realPoint = point - this->getPosition();
    
//    CCLOG("point.x=%f, point.y=%f", point.x, point.y);
//    CCLOG("realPoint.x=%f, realPoint.y=%f", realPoint.x, realPoint.y);
//    CCLOG("floor=%f, floorH=%f", this->_floor, this->_floorH);
    if(realPoint.y > this->_floor && realPoint.y < this->_floorH + this->_floor)
    {
//        CCLOG("move...");
//        this->slime->setPosition(realPoint);
        
        this->_debugDrawNode->clear();

        this->slime->moveTo(realPoint);
//         this->slimeGroup->moveTo(realPoint);
        
    }

    
    
    
}


//int indexDoubleClick = 73;

void GameLayer::onDoubleClick(Point point)
{
    CCLOG("GameLayer::onDoubleClick");
    
//    // 73-111 分裂
//    CCLOG("indexDoubleClick=%d", indexDoubleClick);
//    slime->setDisplayFrameByIndex(indexDoubleClick);
//    indexDoubleClick++;
//    if (indexDoubleClick > 111) {
//        indexDoubleClick = 73;
//    }
    
}
void GameLayer::onMove(Point prePoint, Point curPoint)
{
    CCLOG("GameLayer::onMove");
//    Point testPoint = this->getPosition() + (curPoint - prePoint);
    Size contentSize = this->getContentSize();
//    Size frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();

    
    Point testPoint = this->getPosition() + (curPoint - prePoint);
    float x = contentSize.width - visibleSize.width ;
    float y = contentSize.height - visibleSize.height;
    CCLOG("x=%f, y=%f", x, y);
    
    float cx = testPoint.x;
    cx = cx < -x ? -x : cx;
    cx = cx > origin.x ? origin.x : cx;
    float cy = testPoint.y;
    cy = this->getPositionY();    // 先不移动Y方向

    cy = cy < -y ? -y : cy;
    cy = cy > origin.y ? origin.y : cy;
    CCLOG("cx=%f, cy=%f", cx, cy);
    
    this->setPosition(cx, cy);
    this->setAnchorPoint(Vec2(0, 0));
    
}

void GameLayer::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
    Layer::draw(renderer, transform, flags);
//    CCLOG("GameLayer::draw");
    
    Point curP = this->slime->getPosition();
    if (this->slimeTestPoint != curP) {
//        CCLOG("|||||||||||||||||||||||||||||||");
//            _debugDrawNode->clear();
        Vec2 vertices[4] = {
            this->slimeTestPoint,
            curP,
        };
        _debugDrawNode->drawLine(vertices[0], vertices[1], Color4F(1.0, 1.0, 1.0, 1.0));
        
        this->slimeTestPoint = curP;
        // 画 anchor 圆点
        _debugDrawNode->drawDot(this->slimeTestPoint, 5, Color4F(1, 1, 1, 1));

    }
}

void GameLayer::update(float delta)
{
    Layer::update(delta);
//    CCLOG("GameLayer::update");
    
    EventCustom event("gamelayer_update_event");
//    event.setUserData(delta);
    _eventDispatcher->dispatchEvent(&event);
    
}


//键位响应函数原型
void GameLayer::onKeyPressed(EventKeyboard::KeyCode keyCode,Event*event)
{
    CCLOG("Key with keycode %d pressed", keyCode);
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_W :
            // 上
            this->moveUp();
            break;
        case EventKeyboard::KeyCode::KEY_S :
            // 下
            this->moveDown();
            break;
        case EventKeyboard::KeyCode::KEY_A :
            // 左
            this->moveLeft();
            break;
        case EventKeyboard::KeyCode::KEY_D :
            // 右
            this->moveRight();
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW :
            this->moveDown();
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW :
            this->moveUp();
            break;
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW :
            this->moveLeft();
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW :
            this->moveRight();
            break;
            
        case EventKeyboard::KeyCode::KEY_J :
            // 攻击
            this->attack();
            break;
        default:
            break;
    }
}

void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode,Event*event)
{
    CCLOG("Key with keycode %d released", keyCode);
    
    if (EventKeyboard::KeyCode::KEY_ESCAPE == keyCode){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
        MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
        return;
#endif
        Director::getInstance()->end();
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif  
    }
    
    
}

void GameLayer::moveRight()
{
    this->slime->move(Point(1, 0));
}
void GameLayer::moveLeft()
{
    this->slime->move(Point(-1, 0));
}
void GameLayer::moveUp()
{
//    this->slime->move(Point(0, 1));
}
void GameLayer::moveDown()
{
//    this->slime->move(Point(0, -1));
}
void GameLayer::attack()
{
    this->slime->attack();
}



