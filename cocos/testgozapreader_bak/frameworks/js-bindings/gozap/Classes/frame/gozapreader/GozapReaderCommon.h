//
//  GozapReaderCommon.h
//  testgozapreader
//
//  Created by zhaojm on 14/12/19.
//
//

#ifndef __testgozapreader__GozapReaderCommon__
#define __testgozapreader__GozapReaderCommon__

#include "cocos2d.h"
USING_NS_CC;


typedef struct _clipObj
{
    float x;
    float y;
    std::string name;
    
} ClipObj;


typedef enum _readType
{
    READ_TYPE_SPRITE = 0,
    READ_TYPE_SCENE,
} ReadType;


#endif /* defined(__testgozapreader__GozapReaderCommon__) */
