//
//  GozapSprite.h
//  testgozapreader
//
//  Created by zhaojm on 14/12/19.
//
//

#ifndef __testgozapreader__GozapSprite__
#define __testgozapreader__GozapSprite__

#include "GozapNode.h"
#include "GozapAnimate.h"

class GozapAnimate;

class GozapSprite : public GozapNode
{
private:
    GozapAnimate* _animate;
    Point vector;   // 方向向量
    Point currentPos;   // 当前要设置的位置
    Point destinationPos;   // 最终目的地位置
    float y_factor;     // 
    
   
protected:
    
    virtual void update(float delta);
    
public:
    ~GozapSprite();
    virtual bool init(GozapModel* model);
    virtual void onActionStop();

    void runActionByName(std::string name, bool loop);
    void runActionTo(Point to, std::string action);
    void stopAnimate();
    void setDisplayFrameByIndex(int index);
    void setVector(Point v);   // 设置方向
    void setPosition(Point p);
    
    
    static GozapSprite* createWithModel(GozapModel* model);
    static GozapSprite* createWithJsonFile(std::string path);
};


#endif /* defined(__testgozapreader__GozapSprite__) */
