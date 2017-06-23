//
//  DebugSprite.cpp
//  testgozapreader
//
//  Created by zhaojm on 14/12/23.
//
//

#include "DebugSprite.h"
bool DebugSprite::init()
{
    this->_debugDrawNode = DrawNode::create();
    this->addChild(this->_debugDrawNode);
    return true;
}

void DebugSprite::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
    Sprite::draw(renderer, transform, flags);
    
    CCLOG("DebugNode::draw");
    // 画出 Node的四条边界
    Point anchor = this->getAnchorPoint();
    Size size = this->getContentSize();
    
    _debugDrawNode->clear();
    Vec2 vertices[4] = {
        Vec2(0, 0),
        Vec2(0, size.height),
        Vec2(size.width, size.height),
        Vec2(size.width, 0),
    };
    _debugDrawNode->drawPoly(vertices, 4, true, Color4F(1.0, 1.0, 1.0, 1.0));
    // 画 anchor 圆
    _debugDrawNode->drawDot(Vec2(anchor.x * size.width, anchor.y * size.height), 5, Color4F(1, 1, 1, 1));
    
}

Scene* DebugSprite::createScene()
{
    Scene* scene = Scene::create();
    DebugSprite *sprite = DebugSprite::create();    // create with some spriteframe
    
    
//    node->setContentSize(Size(100, 100));
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
    sprite->setPosition(200, 200);
    sprite->setScale(0.5);
    scene->addChild(sprite);
    return scene;
}