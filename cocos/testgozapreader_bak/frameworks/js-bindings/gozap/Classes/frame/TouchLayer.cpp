//
//  TouchLayer.cpp
//  testgozapreader
//
//  Created by zhaojm on 14/12/19.
//
//

#include "TouchLayer.h"

TouchLayer::TouchLayer()
{
    m_longProgress=false;
}

bool isTouch=false;

bool isMoved=false;

int pressTimes=0;

int touchCounts=0;

bool TouchLayer::init()
{
    if(!Layer::init()){
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();//创建一个触摸监听
    listener->setSwallowTouches(true);//设置是否想下传递触摸
    
    listener->onTouchBegan = CC_CALLBACK_2(TouchLayer::touchBegan, this);
    //拖动精灵移动
    listener->onTouchMoved = CC_CALLBACK_2(TouchLayer::touchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(TouchLayer::touchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(TouchLayer::touchCancel, this);

    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}


void TouchLayer::updateSingleDelay(float ft)
{
    if (touchCounts == 1) {
        onSingleCLick(m_endPoint);
        touchCounts=0;
    }
    
}

void TouchLayer::updateDoubleDelay(float ft)
{
    if (touchCounts == 2 )
    {
        onDoubleClick(m_endPoint);
        touchCounts=0;
    }
}

void TouchLayer::updatelongprogress(float ft)
{
    if (isTouch) {
        pressTimes++;
        
        if (pressTimes >= 2) {
            m_longProgress=true;
            onLongPressed(m_endPoint);
            
        }
    }
    else
    {
        pressTimes=0;
    }
}

long long TouchLayer::getCurrentTime()
{
    struct timeval tm;
    gettimeofday(&tm, NULL);
    return (long long)(tm.tv_sec*1000 + tm.tv_usec/1000);
}




bool TouchLayer::touchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
    m_startPoint=touch->getLocation();
    
    isTouch=true;
    
    m_startTime=getCurrentTime();
    
    //处理长按事件
    this->schedule(schedule_selector(TouchLayer::updatelongprogress),1);
    
    return true;
}

void TouchLayer::touchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    isMoved=true;
    Point curPoint=touch->getLocation();
    Point prePoint = touch->getPreviousLocation();
    onMove(prePoint, curPoint);
    
}

void TouchLayer::touchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    isTouch=false;
    pressTimes=0;
    this->unschedule(schedule_selector(TouchLayer::updatelongprogress));
    
    //如果刚完成长按事件 则把按下次数清零 长按状态置空 直接返回 不继续执行
    if (m_longProgress ) {
        touchCounts=0;
        m_longProgress=false;
        
        return;
    }
    
    m_endPoint=touch->getLocation();
    
    long long endTime=getCurrentTime();
    
    long long timeDis=endTime-m_startTime;
    
    E_SWIP_DIR dir=GetSwipDir(m_startPoint, m_endPoint,timeDis);
    
    if ( dir != E_INVAILD) {
        onSwip(m_startPoint, m_endPoint, dir);
        return;
    }
    
    //做连击判断
    if (isMoved) {
        isMoved=false;
        return;
    }
    if (touchCounts == 2) {
        onThreeClick(m_endPoint);
        touchCounts=0;
    }
    else if (touchCounts == 1) {
        this->scheduleOnce(schedule_selector(TouchLayer::updateDoubleDelay), 0.25);
        touchCounts++;
    }
    else if (touchCounts == 0) {
        this->scheduleOnce(schedule_selector(TouchLayer::updateSingleDelay), 0.25);
        touchCounts++;
    }
    
}
void TouchLayer::touchCancel(cocos2d::Touch *touch, cocos2d::Event *event)
{
    this->touchEnded(touch, event);
}


E_SWIP_DIR TouchLayer::GetSwipDir(Point start,Point end,long long timeDis)
{
    if (timeDis < minSwiptime) {
        return E_INVAILD;
    }
    
    if (abs(end.x - start.x) > minSwipdistance) {
        if (end.x > start.x) {
            return E_RIGHT;
        }else{
            return E_LEFT;
        }
    }
    if (abs(end.y - start.y) > minSwipdistance) {
        if (end.y > start.y) {
            return E_UP;
        }else{
            return E_DOWN;
        }
    }
    return E_INVAILD;
}

