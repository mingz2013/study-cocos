//
//  SubSprite.cpp
//  testgozapreader
//
//  Created by zhaojm on 14/12/16.
//
//

#include "SubSprite.h"
#include "math/TransformUtils.h"

SubSpriteFrame SubSpriteFrameMake(std::string libName, int frameIndex, float a, float b, float c, float d, float tx, float ty, float cx, float cy)
{
    AffineTransform t;
    t = AffineTransformMake(a, b, c, d, tx, ty);
    
    SubSpriteFrame f;
    f.libName = libName;
    f.frameIndex = frameIndex;
    f.transform = t;
    f.cx = cx;
    f.cy = cy;
    return f;
}

bool SubSprite::init(std::vector<SubSpriteFrame > subSpriteFrameVector, int layerIndex, GozapModel* model)
{
    if(!DebugNode::init()){
        return false;
    }
    
    this->setSpriteScale(model->getSpriteScale());
    this->clipping = model->clipping;
    this->setReadType(model->getReadType());
    this->fileName = model->getFileName();
    this->subSpriteFrameVector = subSpriteFrameVector;
    this->_layerIndex = layerIndex;
    this->_batchNode = SpriteBatchNode::create("res/" + this->fileName + "/0.png");
    this->addChild(this->_batchNode);
    
    this->setSubSpriteDisplayFrameByIndex(0);
    
    return true;
}


void SubSprite::setFatherNode(GozapNode *node)
{
    this->_fatherNode = node;
}
void SubSprite::setSceneSubSpriteDisplayFrame(SubSpriteFrame frame)
{
//    CCLOG("SubSprite::setSubSpriteDisplayFrame");
    
    if (frame.libName == "" || frame.libName.empty()) {
//        CCLOG("SubSprite::setSubSpriteDisplayFrame, frame is NULL");
        this->setVisible(false);
        return;
    }
    this->setVisible(true);
    
    std::map<std::string, std::vector<ClipObj>>::iterator it = this->clipping.find(frame.libName);
    if (it == this->clipping.end()) {
        CCLOG("error find clipping");
        return;
    }
    std::vector<ClipObj> objs = it->second;
    float sceneW = 0, sceneH = 0;
    for (int i = 0; i < objs.size(); i++) {
        ClipObj obj = objs[i];
        auto s = Sprite::createWithSpriteFrameName(obj.name);
        s->setAnchorPoint(Vec2(0, 0));
        
        s->setPosition(obj.x / this->getSpriteScale(), obj.y / this->getSpriteScale());
        s->setScale(1 / this->getSpriteScale());
        this->addChild(s);
        sceneW += (s->getPositionY() == 0) ? s->getContentSize().width * (1 / this->getSpriteScale()) : 0;
        sceneH += (s->getPositionX() == 0) ? s->getContentSize().height * (1 / this->getSpriteScale()): 0;
        this->sceneSpriteList.pushBack(s);
    }
    CCLOG("subSprite befor set contentsize, w=%f, h=%f", this->getContentSize().width, this->getContentSize().height);
    this->setContentSize(Size(sceneW, sceneH ));

//    this->setAnchorPoint(Vec2(frame.cx, frame.cy));
    
    
    
//    Mat4 tmp;
//    CGAffineToGL(frame.transform, tmp.m);
//    this->setNodeToParentTransform(tmp);
    
    //    this->setAdditionalTransform(frame.transform);
    //    this->setAdditionalTransform(frame.transform);
    //
//    this->updateTransform();
    
}

void SubSprite::setSpriteSubSpriteDisplayFrame(SubSpriteFrame frame)
{
//    CCLOG("SubSprite::setSubSpriteDisplayFrame");
    
    if (frame.libName == "" || frame.libName.empty()) {
//        CCLOG("SubSprite::setSubSpriteDisplayFrame, frame is NULL");
        this->setVisible(false);
        return;
    }
    this->setVisible(true);
    if(!this->_realSprite){
        this->_realSprite = Sprite::create();
        CCLOG("SubSprite::setSubSpriteDisplayFrame, realSprite create");
        this->_realSprite->setDisplayFrame(
                                           SpriteFrameCache::getInstance()->getSpriteFrameByName(frame.libName)
                                           );
        this->addChild(this->_realSprite);
        this->_realSprite->setScale(1/ this->getSpriteScale());
        this->setContentSize(this->_realSprite->getContentSize() * (1/ this->getSpriteScale()));
        CCLOG("%f, %f", this->getContentSize().width, this->getContentSize().height);
        this->_realSprite->setPosition(Vec2(0, 0));
        this->_realSprite->setAnchorPoint(Vec2(0, 0));
        
    }
    this->_realSprite->setDisplayFrame(
                          SpriteFrameCache::getInstance()->getSpriteFrameByName(frame.libName)
                          );
    this->setContentSize(this->_realSprite->getContentSize() * (1/ this->getSpriteScale()));
//
    this->setAnchorPoint(Vec2(frame.cx, frame.cy));

    
    float cx = frame.cx;
    float cy = frame.cy;
    float a = frame.transform.a;
    float b = frame.transform.b;
    float c = frame.transform.c;
    float d = frame.transform.d;
    float tx = frame.transform.tx;
    float ty = frame.transform.ty;
    int index = frame.frameIndex;
    
    Mat4 tmp;
    CGAffineToGL(frame.transform, tmp.m);
    this->setNodeToParentTransform(tmp);
    
//    this->setAdditionalTransform(frame.transform);
//    this->setAdditionalTransform(frame.transform);
//
//    this->updateTransform();
    
//    CCLOG("SubSprite::setSpriteSubSpriteDisplayFrame,index=%d, a=%f, b=%f, c=%f, d=%f, tx=%f, ty=%f, cx=%f, cy=%f", index, a, b, c, d, tx, ty, cx, cy);
    
    
}

void  SubSprite::setSubSpriteDisplayFrameByIndex(int index)
{
//    CCLOG("SubSprite::setSubSpriteDisplayFrameByIndex, index=%d", index);
    CCASSERT(index >= 0 && index < this->subSpriteFrameVector.size(), "subSpriteFrameVector out of range");
    
    SubSpriteFrame frame = this->subSpriteFrameVector.at(index);
    
    // 区分 类型的操作
    if (this->getReadType() == READ_TYPE_SCENE) {
        this->setSceneSubSpriteDisplayFrame(frame);
    }else if(this->getReadType() == READ_TYPE_SPRITE){
        this->setSpriteSubSpriteDisplayFrame(frame);
    }
    
}

int SubSprite::getLayerIndex()
{
    return this->_layerIndex;
}

//Sprite* SubSprite::getRealSprite()
//{
//    return this->_realSprite;
//}

SubSprite* SubSprite::createWithSubSpriteFrameVector(std::vector<SubSpriteFrame> subSpriteFrameVector, int layerIndex, GozapModel* model)
{
    CCLOG("SubSprite::createWithSubSpriteFrameVector");
    SubSprite *pRet = new SubSprite();
    if (pRet && pRet->init(subSpriteFrameVector, layerIndex, model))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}