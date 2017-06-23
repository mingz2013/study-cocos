//
//  GozapReader.h
//  testgozapreader
//
//  Created by zhaojm on 14/12/11.
//
//

#ifndef __testgozapreader__GozapReader__
#define __testgozapreader__GozapReader__


#include "json/rapidjson.h"
#include "json/document.h"
#include "GozapModel.h"

#include "GozapReaderCommon.h"

class GozapModel;


class GozapReader {
public:
    
    static void parseImgArr(rapidjson::Value& imgArr,std::string fileName);
    static void parseMCObj(rapidjson::Value& mcObjs, std::string objName, GozapModel* model);
    static void parseClipping(rapidjson::Value& clipping, GozapModel* model);
    
    static void parseLayers(rapidjson::Value& layers, GozapModel* model);

    static void parseFrameLabels(rapidjson::Value& mcObj, GozapModel* model);
    static void parseFrameMoveObj(rapidjson::Value& mcObj, GozapModel* model);
    static GozapModel* parseJsonFileToModel(std::string path, ReadType readtype);

//    static GozapSprite* readSpriteFromJsonFile(std::string path);
//    
//    static GozapScene* readSceneFromJsonFile(std::string path);

    
};


#endif /* defined(__testgozapreader__GozapReader__) */
