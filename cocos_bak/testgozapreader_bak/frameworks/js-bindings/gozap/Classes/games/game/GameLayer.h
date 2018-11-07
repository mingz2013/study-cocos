//
//  GameLayer.h
//  testgozapreader
//
//  Created by zhaojm on 14/12/19.
//
//

#ifndef __testgozapreader__GameLayer__
#define __testgozapreader__GameLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "TouchLayer.h"
#include "GozapSprite.h"
#include "Slime.h"
#include "SlimeGroup.h"

class GameLayer : public TouchLayer
{
private:
    float _floor ;
    float _floorH;
    Slime* slime;
    float scaleFactor;
    SlimeGroup* slimeGroup;
    
    Point slimeTestPoint;
    
    DrawNode* _debugDrawNode;
    
private:
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void attack();
    
protected:
    virtual void update(float delta);
    void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
    
    virtual void onSingleCLick(Point point);//单击
    virtual void onDoubleClick(Point point);//双击
    virtual void onThreeClick(Point point){CCLOG("onThreeClick");};//3连击
    virtual void onLongPressed(Point point){CCLOG("onLongPressed");};//长按
    virtual void onMove(Point prePoint, Point curPoint);//移动
    virtual void onSwip(Point,Point,E_SWIP_DIR){CCLOG("onSwip");};//滑动
    
    void onKeyPressed(EventKeyboard::KeyCode keyCode,Event*event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode,Event*event);
    
public:
    GameLayer(){};
    ~GameLayer();
    virtual bool init();
    
    static cocos2d::Scene* createScene();
    CREATE_FUNC(GameLayer);
};

#endif /* defined(__testgozapreader__GameLayer__) */
