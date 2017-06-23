//
//  GozapScene.h
//  testgozapreader
//
//  Created by zhaojm on 14/12/19.
//
//

#ifndef __testgozapreader__GozapScene__
#define __testgozapreader__GozapScene__

#include "GozapNode.h"

class GozapModel;

class GozapScene : public GozapNode
{
public:
    GozapScene(){};
    ~GozapScene(){};
    virtual bool init(GozapModel* model);
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);

    
    static GozapScene* createWithModel(GozapModel* model);
    static GozapScene* createWithJsonFile(std::string path);
};


#endif /* defined(__testgozapreader__GozapScene__) */
