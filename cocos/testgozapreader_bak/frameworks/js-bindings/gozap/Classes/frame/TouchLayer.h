//
//  TouchLayer.h
//  testgozapreader
//
//  Created by zhaojm on 14/12/19.
//
//

#ifndef __testgozapreader__TouchLayer__
#define __testgozapreader__TouchLayer__

#include "cocos2d.h"
USING_NS_CC;

const int minSwipdistance=100;
const int minSwiptime=1000;    //毫秒
const int maxClickedDis=20;

enum E_SWIP_DIR
{
    E_INVAILD,
    E_LEFT,
    E_RIGHT,
    E_UP,
    E_DOWN
};


class TouchLayer:public Layer
{
public:
    TouchLayer();
    
    virtual bool init();
    
    bool touchBegan(Touch * touch,Event * event);
    void touchMoved(Touch * touch,Event * event);
    void touchEnded(Touch * touch,Event * event);
    void touchCancel(Touch * touch,Event * event);
    
//    void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
//    void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
//    void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
//    void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event);
    
    
    void updateSingleDelay(float);
    void updateDoubleDelay(float);
    
    void updatelongprogress(float);
    
    long long getCurrentTime();
    
    
    void stopSchedule();
    
private:
    E_SWIP_DIR GetSwipDir(Point start,Point end,long long timeDis);
    
public:
    virtual void onSingleCLick(Point) = 0;        //单击
    virtual void onDoubleClick(Point) = 0;        //双击
    virtual void onThreeClick(Point) = 0;         //3连击
    virtual void onLongPressed(Point) = 0;        //长按
    virtual void onMove(Point, Point) = 0;          //移动
    virtual void onSwip(Point,Point,E_SWIP_DIR) = 0;   //滑动
    
private:
    bool m_longProgress;
    Point m_startPoint;
    Point m_endPoint;
    float m_startTime;
};
#endif /* defined(__testgozapreader__TouchLayer__) */
