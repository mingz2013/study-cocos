//
//  GozapSprite.cpp
//  testgozapreader
//
//  Created by zhaojm on 14/12/19.
//
//

#include "GozapSprite.h"

GozapSprite::~GozapSprite()
{
    this->unscheduleUpdate();
    this->_animate->release();
}

bool GozapSprite::init(GozapModel *model)
{
    if (!GozapNode::init(model)) {
        return false;
    }    
    
    this->vector = Point(1, 1);
    this->currentPos = Point(0, 0);
    this->destinationPos = Point(0, 0);
    
    this->setAnchorPoint(Vec2(0.5, 0));
    
    
    this->setScaleX(this->getScaleX()* this->getModel()->getDirection());
    
    this->_animate = GozapAnimate::createWithGozapSprite(this);
    this->_animate->retain();
    
    
     this->scheduleUpdate();
    
    CCLOG("GozapSprite contentsize, w=%f, h=%f", this->getContentSize().width, this->getContentSize().height);
    CCLOG("GozapSprite anchorPoint, x=%f, y=%f", this->getAnchorPoint().x, this->getAnchorPoint().y);

    return true;
}

void GozapSprite::update(float delta)
{
    GozapNode::update(delta);
    
    if (this->_animate) {
        this->_animate->step(delta);
    }
    
    
    GozapNode::setPosition(this->currentPos);
    
}

void GozapSprite::setPosition(Point p)
{
    GozapNode::setPosition(p);
    this->destinationPos = this->currentPos = p;
}

void GozapSprite::setDisplayFrameByIndex(int index)
{
//    CCLOG("GozapNode::setDisplayFrameByIndex, index=%d", index);
    for(int i = 0; i < this->model->getSubSpriteSize(); i++){
        this->model->getSubSpriteByIndex(i)->setSubSpriteDisplayFrameByIndex(index);
    }
        
    // 设置 MoveObj
    std::map<int, Vec2>::iterator it = this->model->frameMoveObj.find(index);
    if (!(it == this->model->frameMoveObj.end())) {
        float x = this->getPositionX() + it->second.x * this->vector.x * this->getModel()->getDirection() * this->getScaleFactor();
        float y1 = this->getPositionY();
        
        
        float my = it->second.x  * this->y_factor;
//
        y1 += abs(my) * this->vector.y * this->getScaleFactor();
//
        float y;
        
        y = y1;
        y +=  it->second.y * this->getScaleFactor();

        
        if ((this->vector.y < 0 && y <= this->destinationPos.y) ||
            (this->vector.y > 0 && y >= this->destinationPos.y)
            ) {
//            y = destinationPos.y;
//            x = destinationPos.x;
//            this->vector.y = 0;
        }else if(this->vector.y == 0){
//            y = destinationPos.y;
        }
        
//        CCLOG("111111111111");
        if ((this->vector.x < 0 && x <= this->destinationPos.x) ||
            (this->vector.x > 0 && x >= this->destinationPos.x)
            ) {
//            CCLOG("2222222222");
            x = destinationPos.x;
            y = destinationPos.y;
//            this->vector.x =0;
            
        }else if(this->vector.x == 0){
            x = destinationPos.x;
            y = destinationPos.y;

        }
        
        if (this->destinationPos == Vec2(x, y)) {
            this->_animate->setIsLoop(false);
//            this->onRunActionToSuccess();

        }
        this->currentPos = Point(x, y);
    }
    
}

void GozapSprite::onActionStop()
{
    CCLOG("GozapSprite::onRunActionToSuccess, need to be rewrite");
}

void GozapSprite::stopAnimate()
{
    this->_animate->stop();

}

void GozapSprite::runActionByName(std::string name, bool loop)
{
    CCLOG("GozapNode::runActionByName->name=%s", name.c_str());
    this->_animate->runActionByName(name, loop);
}

void GozapSprite::runActionTo(Point to, std::string action)
{
    this->destinationPos = to;

    float vx;
    if(this->currentPos.x < to.x ) {
        vx = 1;
    }else if(this->currentPos.x == to.x ){
        vx = 0;
    }else if(this->currentPos.x > to.x ){
        vx = -1;
    }
    float vy;
    if(this->currentPos.y < to.y ) {
        vy = 1;
    }else if(this->currentPos.y == to.y ){
        vy = 0;
    }else if(this->currentPos.y > to.y ){
        vy = -1;
    }
    
//    this->setScaleX(vx * this->vector.x * this->getScaleX());
//    
//    this->vector = Point(vx , vy);
    this->setVector(Point(vx, vy));
    
    
    Size des = Size(this->destinationPos.x - this->getPosition().x, this->destinationPos.y - this->getPosition().y);
    this->y_factor = des.height / des.width;
    
    this->runActionByName(action, true);
    
}

void GozapSprite::setVector(Point v)
{
    this->setScaleX(v.x * this->vector.x * this->getScaleX());

    this->vector = v;
    
}


GozapSprite* GozapSprite::createWithJsonFile(std::string path)
{
    GozapModel* model = GozapReader::parseJsonFileToModel(path, READ_TYPE_SPRITE);
    GozapSprite *node = GozapSprite::createWithModel(model);
    return node;
}

GozapSprite* GozapSprite::createWithModel(GozapModel* model)
{
    CCLOG("GozapNode::createWithModel");
    GozapSprite *pRet = new GozapSprite();
    if (pRet && pRet->init(model))
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