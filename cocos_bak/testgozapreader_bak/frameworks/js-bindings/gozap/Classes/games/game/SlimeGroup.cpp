//
//  SlimeGroup.cpp
//  testgozapreader
//
//  Created by zhaojm on 14/12/24.
//
//

#include "SlimeGroup.h"

bool SlimeGroup::init()
{
    CCLOG("SlimeGroup::init");
    
    this->_radius = 100;
    
    
    srand(unsigned(time(0)));
    
    for (int i = 0; i < 10; i++) {
        Slime* si = Slime::createWithJsonFile("res/hongsedonghua.json");
        
        double r = ((rand() % 1000) * 0.001) * this->_radius;   // 半径
        double angle = ((rand() % 1000) * 0.001) * 360;         // 角度
        
//        float x = (rand()%2?-1:1) * ((rand()%1000)*0.001) * this->_radius;
//        float y = (rand()%2?-1:1) * ((rand()%1000)*0.001) * this->_radius;
        float x = r * cos(angle);
        float y = r * sin(angle);
        
        si->setPosToCenterPos(Vec2(x, y));
        
        this->_slimeList.pushBack(si);
        
    }
    
    
    auto _listener = EventListenerCustom::create("gamelayer_update_event", [=](EventCustom* event){
        this->onGameLayerUpdate(event);
    });
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_listener, 1);
    
    
    return true;
}

void SlimeGroup::addToNode(Node* node, Point centerPos)
{
    this->_currentCenterPos = centerPos;
    
    for(int i = 0; i < this->_slimeList.size(); i++){
        Slime* si = this->_slimeList.at(i);
        
        si->setPosition(this->_currentCenterPos + si->getPosToCenterPos());
        
        node->addChild(si);
        
        si->runActionByName("待机", true);
        
    }
    
    
}


void SlimeGroup::onGameLayerUpdate(EventCustom* event){
//    CCLOG("gamelayer_update_event received");
    
    this->depthSorting();
    
}


void SlimeGroup::depthSorting()
{
//    CCLOG("SlimeGroup::depthSorting");
    /**
     设置Z轴顺序
     **/
  
    Vector<Slime*> _slimeList2;
    
    for(int i = 0; i < this->_slimeList.size(); i++){
        Slime* si = this->_slimeList.at(i);
        
        int j;
        for(j = 0; j < _slimeList2.size(); j++){
            Slime* sj = _slimeList2.at(j);
            if (si->getPositionY() > sj->getPositionY()) {
                _slimeList2.insert(j, si);
                break;
            }
        }
        
        if (j == _slimeList2.size()) {
            _slimeList2.pushBack(si);
        }
    }
    
    this->_slimeList = _slimeList2;
    
    for(int i = 0; i < this->_slimeList.size(); i++){
        Slime* s = this->_slimeList.at(i);
        s->setZOrder(i);
    }
    
}

void SlimeGroup::moveTo(Point destinationPos)
{
    CCLOG("SlimeGroup::moveTo");
    
    srand(unsigned(time(0)));
    
    
    for(int i = 0; i < this->_slimeList.size(); i++){
        Slime* si = this->_slimeList.at(i);
        
        double r = ((rand() % 1000) * 0.001) * this->_radius;   // 半径
        double angle = ((rand() % 1000) * 0.001) * 360;         // 角度
        
        CCLOG("r=%f, angle=%f", r, angle);
        
        //        float x = (rand()%2?-1:1) * ((rand()%1000)*0.001) * this->_radius;
        //        float y = (rand()%2?-1:1) * ((rand()%1000)*0.001) * this->_radius;
        float x = r * cos(angle);
        float y = r * sin(angle);
        
        si->setPosToCenterPos(Vec2(x, y));
        
        si->moveTo(destinationPos + si->getPosToCenterPos());
    }
}


SlimeGroup* SlimeGroup::create()
{
    CCLOG("SlimeGroup::create");
    SlimeGroup *pRet = new SlimeGroup();
    if (pRet && pRet->init())
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

