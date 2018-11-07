//
//  GozapNode.h
//  testgozapreader
//
//  Created by zhaojm on 14/12/19.
//
//

#ifndef __testgozapreader__GozapNode__
#define __testgozapreader__GozapNode__

#include <stdio.h>
#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "SubSprite.h"

#include "GozapReader.h"
#include "GozapModel.h"

#include "GozapReaderCommon.h"

#include "DebugNode.h"

USING_NS_CC;


class GozapModel;

class GozapNode : public DebugNode
{
    
    
//protected:
//    virtual void onEnter();
    

    
public:
    GozapNode();
    ~GozapNode();
    virtual bool init(GozapModel* model);
    
    SpriteBatchNode* getBatchNode();
    
    CC_SYNTHESIZE(GozapModel* , model, Model);
    CC_SYNTHESIZE(float, scaleFactor, ScaleFactor);
    
//    //    CREATE_FUNC(GozapNode);
//    static GozapNode* createWithModel(GozapModel* model);
//    static GozapNode* createWithJsonFile(std::string path, ReadType readType);
    
private:
    
    SpriteBatchNode * _spriteBatchNode;
    
};
#endif /* defined(__testgozapreader__GozapNode__) */
