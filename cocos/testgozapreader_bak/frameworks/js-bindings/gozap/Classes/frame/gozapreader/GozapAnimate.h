//
//  GozapAnimate.h
//  testgozapreader
//
//  Created by zhaojm on 14/12/11.
//
//

#ifndef __testgozapreader__GozapAnimate__
#define __testgozapreader__GozapAnimate__


#include "cocos2d.h"
#include "GozapSprite.h"

USING_NS_CC;

class GozapSprite;

class GozapAnimate :public Ref
{
private:
    bool init(GozapSprite* sprite);
    GozapSprite* _currentSprite;
    bool _isrunning;
    float _frameTime;   // 间隔时间
    float _currentTime; // 当前的时间
    std::vector<int> _currentFrameLabel; // 当前播放的帧 间段
    int _currentFrameIndex; // 当前播放的帧
//    bool _isLoop;   /// 是否循环播放
    
public:
    CC_SYNTHESIZE(bool, _isLoop, IsLoop);
public:
    GozapAnimate(){};
    ~GozapAnimate(){};
    void step(float dt);
    void stop();
    void runActionByName(std::string name, bool loop = true);

    static GozapAnimate* createWithGozapSprite(GozapSprite* sprite);
        
};

#endif /* defined(__testgozapreader__GozapAnimate__) */
