//
//  GozapAnimate.cpp
//  testgozapreader
//
//  Created by zhaojm on 14/12/11.
//
//

#include "GozapAnimate.h"
bool GozapAnimate::init(GozapSprite *sprite)
{
    this->_currentSprite = sprite;
    this->_isrunning = false;
    this->_frameTime = this->_currentSprite->getModel()->getFrameTime() / 1000.0;
    this->_currentTime = 0;
    this->_currentFrameIndex = 0;
    this->_isLoop = false;
    
    return true;
}

void GozapAnimate::step(float dt)
{
    if (this->_isrunning) {
        this->_currentTime += dt;
        if (this->_currentTime >= this->_frameTime) {
            this->_currentTime = 0;
            if (this->_currentFrameIndex <= this->_currentFrameLabel[1]) {
                this->_currentSprite->setDisplayFrameByIndex(this->_currentFrameIndex);
                this->_currentFrameIndex++;
            }else{
                if (this->_isLoop) {
                    this->_currentFrameIndex = this->_currentFrameLabel[0];
                    this->_currentSprite->setDisplayFrameByIndex(this->_currentFrameIndex);
                    this->_currentFrameIndex++;
                }else{
                    this->stop();
                }
            }
        }// if
    }// if
    
}
void GozapAnimate::stop()
{
    CCLOG("GozapAnimate::stop");
    this->_isrunning = false;
    this->_currentTime = 0;
    this->_isLoop = false;
    this->_currentSprite->onActionStop();
}

void GozapAnimate::runActionByName(std::string name, bool loop)
{
    CCLOG("name=%s, loop=%d", name.c_str(), loop);
    std::map<std::string, std::vector<int>> ::iterator it = this->_currentSprite->getModel()->frameLabels.find(name);
    if(it == this->_currentSprite->getModel()->frameLabels.end()){
        CCASSERT(false, "action name is error");
        return;
    }
    this->_currentFrameLabel = this->_currentSprite->getModel()->frameLabels[name];
    this->_currentFrameIndex = this->_currentFrameLabel[0];
    this->_isLoop = loop;
    
    if (this->_isrunning) {
        this->_isrunning = true;
        this->_currentTime = 0;
    }else{
        this->_isrunning = true;
        this->_currentTime = 0;
    }
}

GozapAnimate* GozapAnimate::createWithGozapSprite(GozapSprite *sprite)
{
    GozapAnimate *pRet = new GozapAnimate();
    if (pRet && pRet->init(sprite))
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