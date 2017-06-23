//
//  GozapNode.cpp
//  testgozapreader
//
//  Created by zhaojm on 14/12/19.
//
//

#include "GozapNode.h"

GozapNode::GozapNode(){};
GozapNode::~GozapNode()
{
    
    this->model->release();

}
bool GozapNode::init(GozapModel* model)
{
    if (!this->DebugNode::init()) {
        return false;
    }
    CCLOG("GozapNode::init");
        
    this->model = model;
    this->model->retain();
    
    // print actions
    for (std::map<std::string, std::vector<int>>::iterator i=this->model->frameLabels.begin(); i!=this->model->frameLabels.end(); i++)
    {
        CCLOG("action=%s", i->first.c_str());
    }
    this->scaleFactor = Director::getInstance()->getOpenGLView()->getFrameSize().height  / this->model->getScreenH() ;
    
//    this->_spriteBatchNode = SpriteBatchNode::create("res/"+ this->model->getFileName() +"/0.png");
//    this->addChild(this->_spriteBatchNode);
    
    for(int i = 0; i < this->model->getSubSpriteSize(); i ++){
        SubSprite* s = this->model->getSubSpriteByIndex(i);
        s->setFatherNode(this);
        //        if(s->getTexture()){
        //            this->_spriteBatchNode->addChild(s, s->getLayerIndex());
        //        }
        this->addChild(s);
    }
    this->setContentSize(this->model->getSubSpriteByIndex(0)->getContentSize());
    CCLOG("GozapNode contentsize, w=%f, h=%f", this->getContentSize().width, this->getContentSize().height);
    this->setScale( this->getScaleFactor() );
    return true;
    
}



//void GozapNode::onEnter()
//{
//    this->Node::onEnter();
//    CCLOG("GozapNode::onEnter");
//}




//GozapNode* GozapNode::createWithJsonFile(std::string path, ReadType readType)
//{
//    GozapModel* model = GozapReader::parseJsonFileToModel(path, readType);
//    GozapNode *node = GozapNode::createWithModel(model);
//    return node;
//}
//
//GozapNode* GozapNode::createWithModel(GozapModel* model)
//{
//    CCLOG("GozapNode::createWithModel");
//    GozapNode *pRet = new GozapNode();
//    if (pRet && pRet->init(model))
//    {
//        pRet->autorelease();
//        return pRet;
//    }
//    else
//    {
//        delete pRet;
//        pRet = NULL;
//        return NULL;
//    }
//}


SpriteBatchNode* GozapNode::getBatchNode()
{
    return this->_spriteBatchNode;
}