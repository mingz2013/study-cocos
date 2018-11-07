//
//  Slime.cpp
//  testgozapreader
//
//  Created by zhaojm on 14/12/22.
//
//

#include "Slime.h"
bool Slime::init(GozapModel* model)
{
    if (!GozapSprite::init(model)) {
        return false;
    }
    return true;
}

void Slime::update(float delta)
{
    GozapSprite::update(delta);
    
    
}
void Slime::onActionStop()
{
    this->runActionByName("待机", true);
}

void Slime::moveTo(Point p)
{
    
    this->runActionTo(p, "移动");
}

void Slime::attack()
{
    this->runActionByName("攻击", false);
}
void Slime::split()
{
    this->runActionByName("分裂", false);
}
void Slime::stand()
{
    this->runActionByName("待机", false);
}
void Slime::death()
{
    this->runActionByName("死亡", false);
}
void Slime::move(Point v)
{
//    this->setVector(v);
//    this->runActionByName("移动", false);
    Point des = this->model->defaultActionDestinationMap.at("移动") * this->getScaleFactor();
    Point to = this->getPosition() +　Vec2(des.x * v.x * this->getModel()->getDirection(), des.y * v.y);
    this->runActionTo(to, "移动");
}


Slime* Slime::createWithJsonFile(std::string path)
{
    GozapModel* model = GozapReader::parseJsonFileToModel(path, READ_TYPE_SPRITE);
    Slime *node = Slime::createWithModel(model);
    return node;
}

Slime* Slime::createWithModel(GozapModel* model)
{
    CCLOG("Slime::createWithModel");
    Slime *pRet = new Slime();
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