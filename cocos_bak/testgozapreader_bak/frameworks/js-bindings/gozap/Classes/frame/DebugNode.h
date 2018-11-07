//
//  DebugNode.h
//  testgozapreader
//
//  Created by zhaojm on 14/12/23.
//
//

#ifndef __testgozapreader__DebugNode__
#define __testgozapreader__DebugNode__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class DebugNode : public Node
{
private:
//    DrawNode * _debugDrawNode;
public:
    CC_SYNTHESIZE(DrawNode*, _debugDrawNode, DebugDrawNode);
public:
    
    virtual bool init();
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
    
    
    
    CREATE_FUNC(DebugNode);
    
    static Scene* createScene();
};

#endif /* defined(__testgozapreader__DebugNode__) */
