//
//  DebugNode.cpp
//  testgozapreader
//
//  Created by zhaojm on 14/12/23.
//
//

#include "DebugNode.h"


bool DebugNode::init()
{
    if(!Node::init()){
        return false;
    }
    this->_debugDrawNode = DrawNode::create();
    this->addChild(this->_debugDrawNode, 10);
    return true;
}

void DebugNode::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
//    CCLOG("DebugNode::draw");
    // 画出 Node的四条边界
    Point anchor = this->getAnchorPoint();
    Size size = this->getContentSize();
    
//    CCLOG("anchor, x=%f, y=%f, size, width=%f, height=%f", anchor.x, anchor.y, size.width, size.height);

    _debugDrawNode->clear();
    Vec2 vertices[4] = {
        Vec2(0, 0),
        Vec2(0, size.height),
        Vec2(size.width, size.height),
        Vec2(size.width, 0),
    };
    _debugDrawNode->drawPoly(vertices, 4, true, Color4F(1.0, 1.0, 1.0, 1.0));
    // 画 anchor 圆
    _debugDrawNode->drawDot(Vec2(anchor.x * size.width, anchor.y * size.height), 30, Color4F(1, 1, 1, 1));
    
//    Vec2 test[4] = {
//        Vec2(100, 100),
//        Vec2(100, 200),
//        Vec2(200, 200),
//        Vec2(200, 100),
//    };
//    _debugDrawNode->drawPoly(test, 4, true, Color4F(1.0, 1.0, 1.0, 1.0));
//    
}

Scene* DebugNode::createScene()
{
    Scene* scene = Scene::create();
    DebugNode *node = DebugNode::create();
    
    
    node->setContentSize(Size(100, 100));
    node->setAnchorPoint(Vec2(0.5, 0.5));
    node->setPosition(200, 200);
    node->setScale(0.5);
    scene->addChild(node);
    return scene;
}