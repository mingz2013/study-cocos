//
//  Slime.h
//  testgozapreader
//
//  Created by zhaojm on 14/12/22.
//
//

#ifndef __testgozapreader__Slime__
#define __testgozapreader__Slime__

#include <stdio.h>
#include "GozapSprite.h"

class Slime : public GozapSprite
{
protected:
    virtual bool init(GozapModel* model);
    virtual void update(float delta);
    virtual void onActionStop();

    
public:
    CC_SYNTHESIZE(Point, _posToCenterPos, PosToCenterPos);  // 相对于中心的位置
public:
    
    // actions
    void move(Point v);    // 移动
    void attack();      // 攻击
    void death();    // 死亡
    void split();   // 分裂
    void stand();   // 待机
    
    void moveTo(Point p);   // 移动到
    
    
    static Slime* createWithModel(GozapModel* model);
    static Slime* createWithJsonFile(std::string path);
};

#endif /* defined(__testgozapreader__Slime__) */
