//
//  SubSprite.h
//  testgozapreader
//
//  Created by zhaojm on 14/12/16.
//
//

#ifndef __testgozapreader__SubSprite__
#define __testgozapreader__SubSprite__


#include "cocos2d.h"
#include "GozapModel.h"
#include "GozapNode.h"

#include "DebugNode.h"

USING_NS_CC;

class GozapNode;

typedef struct subSpriteFrame {
    int frameIndex;
    std::string libName;
    AffineTransform  transform;
    int cx; int cy; // 锚点
} SubSpriteFrame;


SubSpriteFrame SubSpriteFrameMake(std::string libName, int frameIndex,  float a, float b, float c, float d, float tx, float ty, float cx, float cy);



class SubSprite : public DebugNode
{
private:
    std::vector<SubSpriteFrame> subSpriteFrameVector;
    int _layerIndex;
    Sprite * _realSprite;
    Vector<Sprite*> sceneSpriteList;
    GozapNode* _fatherNode;
    SpriteBatchNode* _batchNode;
    std::string fileName;
    CC_SYNTHESIZE(ReadType, readType, ReadType);    // 类型
    CC_SYNTHESIZE(float, spriteScale, SpriteScale);    // 整体缩放


public:
    
    std::map<std::string, std::vector<ClipObj>> clipping;
    
    virtual bool init(std::vector<SubSpriteFrame> subSpriteFrameVector, int layerIndex, GozapModel* model);
        
    void setSpriteSubSpriteDisplayFrame(SubSpriteFrame frame);
    void setSceneSubSpriteDisplayFrame(SubSpriteFrame frame);
    void setSubSpriteDisplayFrameByIndex(int index);
    void setFatherNode(GozapNode* node);
    
    int getLayerIndex();

    
    static SubSprite* createWithSubSpriteFrameVector(std::vector<SubSpriteFrame> subSpriteFrameVector, int layerIndex, GozapModel* model);
};


#endif /* defined(__testgozapreader__SubSprite__) */
