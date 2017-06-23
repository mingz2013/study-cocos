#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "base/ccMacros.h"
#include "base/CCVector.h"
#include "base/CCProtocols.h"
#include "base/CCScriptSupport.h"

#include "math/CCAffineTransform.h"
#include "math/CCMath.h"

USING_NS_CC;

//class Renderer;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    //其它函数省略
    virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags);
//    virtual void visit(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;

    
    void onDraw();

    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    private:
    CustomCommand _command;
};

#endif // __HELLOWORLD_SCENE_H__
