//
//  SlimeGroup.h
//  testgozapreader
//
//  Created by zhaojm on 14/12/24.
//
// 用于定义群体的属性
//
// 还要包含 群体的逻辑，群体深度排序，群体聚集算法等。
//
// 应该是单例，游戏中只有一个slime群
//


#ifndef __testgozapreader__SlimeGroup__
#define __testgozapreader__SlimeGroup__

#include <stdio.h>
#include "Slime.h"

class SlimeGroup : public Ref
{
private:
    Point _currentCenterPos;   // 当前的 圆心位置
    Point _destinationCenterPos;    // 目的地 圆心
    float _radius;      // 半径
    Vector<Slime*> _slimeList; // slimes
    int _slimeCount;    // slime数量

public:
    virtual bool init();
    
    void addToNode(Node* node, Point centerPos);
    void onGameLayerUpdate(EventCustom* event);
    
    void depthSorting();
    void moveTo(Point destinationPos);
    
    static SlimeGroup* create();
        
};

#endif /* defined(__testgozapreader__SlimeGroup__) */
