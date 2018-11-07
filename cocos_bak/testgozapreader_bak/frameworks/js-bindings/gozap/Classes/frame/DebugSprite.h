//
//  DebugSprite.h
//  testgozapreader
//
//  Created by zhaojm on 14/12/23.
//
//

#ifndef __testgozapreader__DebugSprite__
#define __testgozapreader__DebugSprite__




#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class DebugSprite : public Sprite
{
private:
    DrawNode * _debugDrawNode;
public:
    
    virtual bool init();
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
    
    CREATE_FUNC(DebugSprite);
    
    static Scene* createScene();
};

#endif /* defined(__testgozapreader__DebugSprite__) */
