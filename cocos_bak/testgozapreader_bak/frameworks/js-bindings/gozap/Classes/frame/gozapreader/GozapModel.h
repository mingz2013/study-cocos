//
//  GozapModel.h
//  testgozapreader
//
//  Created by zhaojm on 14/12/19.
//
//

#ifndef __testgozapreader__GozapModel__
#define __testgozapreader__GozapModel__

#include <stdio.h>
#include "cocos2d.h"
#include "SubSprite.h"
USING_NS_CC;
#include "GozapReaderCommon.h"

class SubSprite;

class GozapModel : public Ref
{
private:
    Vector<SubSprite*> subSpriteList;
protected:
    virtual bool init();
    
public:
    
    std::map<int, Vec2> frameMoveObj;
    std::map<std::string, std::vector<int>> frameLabels;        // 存储每个动作的起始frame
    std::map<std::string, std::vector<ClipObj>> clipping;
    std::map<std::string, Point> defaultActionDestinationMap;   // 存储 的  每个 action的默认位移
    
    void pushSubSprite(SubSprite*subSprite);
    int getSubSpriteSize();
    SubSprite* getSubSpriteByIndex(int index);
    
    CC_SYNTHESIZE(int, frameTime, FrameTime);   // 帧率
    
    CC_SYNTHESIZE(std::string, fileName, FileName);// 需要的plist文件，用于之后的销毁时移除图片
    CC_SYNTHESIZE(int, totalFrame, TotalFrame); // 总帧数
    CC_SYNTHESIZE(ReadType, readType, ReadType);    // 类型
    CC_SYNTHESIZE(float, spriteScale, SpriteScale);    // 整体缩放
    CC_SYNTHESIZE(float, _screenH, ScreenH);    // 设计尺寸高度
    CC_SYNTHESIZE(float, _screenY, ScreenY);
    CC_SYNTHESIZE(float, floor , Floor);
    CC_SYNTHESIZE(float, floorH, FloorH);
    CC_SYNTHESIZE(int, direction, Direction);   // 动画 默认方向 x轴
    
    
    CREATE_FUNC(GozapModel);
    
};

#endif /* defined(__testgozapreader__GozapModel__) */
