//
//  GozapModel.cpp
//  testgozapreader
//
//  Created by zhaojm on 14/12/19.
//
//

#include "GozapModel.h"
//



bool GozapModel::init()
{
    CCLOG("GozapModel::init()");
    this->fileName = "";
    this->totalFrame = 1;
    
    
    return true;
}

void GozapModel::pushSubSprite(SubSprite *subSprite)
{
    this->subSpriteList.pushBack(subSprite);
}
int GozapModel::getSubSpriteSize()
{
    return (int)this->subSpriteList.size();
}

SubSprite* GozapModel::getSubSpriteByIndex(int index)
{
    return this->subSpriteList.at(index);
}