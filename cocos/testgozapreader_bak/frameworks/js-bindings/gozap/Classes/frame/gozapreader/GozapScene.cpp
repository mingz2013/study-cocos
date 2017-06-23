//
//  GozapScene.cpp
//  testgozapreader
//
//  Created by zhaojm on 14/12/19.
//
//

#include "GozapScene.h"

bool GozapScene::init(GozapModel *model)
{
    
    if (!GozapNode::init(model)) {
        return false;
    }
    CCLOG("GozapScene::init");
    
    
   
    
    this->setAnchorPoint(Vec2(0, 0));
    this->setPosition(Vec2(0, 0));
    

    
    
    if(this->model->getScreenY()){
        this->setPositionY(this->getPositionY() + scaleFactor * this->model->getScreenY());
    }else{
        this->setPositionY(-this->getContentSize().height + Director::getInstance()->getOpenGLView()->getFrameSize().height);
    }
    CCLOG("GozapScene contentsize, w=%f, h=%f", this->getContentSize().width, this->getContentSize().height);

    return true;
}

GozapScene* GozapScene::createWithJsonFile(std::string path)
{
    GozapModel* model = GozapReader::parseJsonFileToModel(path, READ_TYPE_SCENE);
    GozapScene *node = GozapScene::createWithModel(model);
    return node;
}

GozapScene* GozapScene::createWithModel(GozapModel* model)
{
    CCLOG("GozapScene::createWithModel");
    GozapScene *pRet = new GozapScene();
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

void GozapScene::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
//    CCLOG("GozapScene::draw");
    GozapNode::draw(renderer, transform, flags);
    
    if(this->model->getFloor()){
        // test floor layer
        Size size = this->getContentSize();
        float floor = this->model->getFloor();
        float floorH = this->model->getFloorH();
//        LayerColor * testlayer = LayerColor::create(Color4B(255, 2, 24, 24), 10000, floorH);
//        testlayer->setAnchorPoint(Vec2(0, 0));
//        testlayer->setPosition(0, floor);
//        this->addChild(testlayer);
                this->getDebugDrawNode()->drawLine(Vec2(0, floor), Vec2(size.width, floor), Color4F(1, 1, 1, 1));
                this->getDebugDrawNode()->drawLine(Vec2(0, floor + floorH), Vec2(size.width, floor + floorH), Color4F(1, 1, 1, 1));
        
    }
}
