//
//  GozapReader.cpp
//  testgozapreader
//
//  Created by zhaojm on 14/12/11.
//
//

#include "GozapReader.h"
#include "SubSprite.h"


//GozapSprite* GozapReader::readSpriteFromJsonFile(std::string path)
//{
//    CCLOG("GozapReader::readSpriteFromJsonFile");
//    
//    GozapModel* model = GozapReader::parseJsonFileToModel(path, READ_TYPE_SPRITE);
//    
//    GozapSprite* node = GozapSprite::createWithModel(model);
//    return node;
//}
//
//GozapScene* GozapReader::readSceneFromJsonFile(std::string path)
//{
//    CCLOG("GozapReader::readLayerFromJsonFile");
//  
//    GozapModel* model = GozapReader::parseJsonFileToModel(path, READ_TYPE_SCENE);
//    GozapScene* node = GozapScene::createWithModel(model);
//    return node;
//    
//}


GozapModel* GozapReader::parseJsonFileToModel(std::string path, ReadType readtype)
{
    CCLOG("GozapReader::parseJsonFileToModel");
    auto model = GozapModel::create();
    
    model->setReadType(readtype);
    
    rapidjson::Document doc = NULL;
    
    if (!FileUtils::getInstance()->isFileExist(path))
    {
        CCLOG("json file is not find [%s]", path.c_str());
        return model;
    }
    
    std::string data = FileUtils::getInstance()->getStringFromFile(path);
    doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
    
    if (doc.HasParseError() || !doc.IsObject())
    {
        CCLOG("get json data err!");
        return model;
    }
    
    if (doc.HasMember("imgArr") && doc.HasMember("fileName") && doc.HasMember("mcObjs"))
    {
        rapidjson::Value &fileName =doc["fileName"];
        rapidjson::Value &imgArr = doc["imgArr"];
        rapidjson::Value &mcObjs = doc["mcObjs"];
        
        model->setFileName(fileName.GetString());
        
        GozapReader::parseImgArr(imgArr, fileName.GetString());
        if (doc.HasMember("clipping")) {
            rapidjson::Value &clipping = doc["clipping"];
            GozapReader::parseClipping(clipping, model);
        }
        if (doc.HasMember("scale")) {
            rapidjson::Value &scale = doc["scale"];
            model->setSpriteScale(scale.GetDouble());
        }else{
            model->setSpriteScale(1);
        }

        GozapReader::parseMCObj(mcObjs, "root", model);
        
        
        return model;
        
    }else{
        CCLOG("error get imgArr fileName mcObjs");
        return model;
    }
    
}

void GozapReader::parseImgArr(rapidjson::Value& imgArr,std::string fileName)
{
    CCLOG("GozapReader::parseImgArr");
    
    for (unsigned int i = 0; i< imgArr.Size(); i++)
    {
        rapidjson::Value &v = imgArr[i];
        if(v.HasMember("size") && v.HasMember("name"))
        {
            double size = v["size"].GetDouble();
            
            std::stringstream namess;
            namess << v["name"].GetInt();
            std::string name = namess.str();
            namess.clear();

            if (size > 0) {
                std::string imgName = "res/" + fileName + "/" + name;
                CCLOG("imgName=%s", imgName.c_str());
                SpriteFrameCache::getInstance()->addSpriteFramesWithFile(imgName + ".plist", imgName + ".png");
            }
            
        }
        
    }
    
}

void GozapReader::parseClipping(rapidjson::Value& clipping, GozapModel* model)
{
    CCLOG("GozapReader parseClipping");
    CCASSERT(clipping.IsObject(), "clipping type error");
    
    for (rapidjson::Value::ConstMemberIterator itr = clipping.MemberonBegin(); itr != clipping.MemberonEnd(); ++itr)
    {
        std::string name = itr->name.GetString();
        rapidjson::Value& array = (rapidjson::Value&)itr->value;
        if (name == "clippingPadding") {
            continue;
        }
        std::vector<ClipObj> clipObjArray;
        for(int i = 0; i < array.Size(); i++){
            rapidjson::Value& v = array[i];
            
            ClipObj c;
            c.x = v["x"].GetDouble();
            c.y = v["y"].GetDouble();
            c.name = v["name"].GetString();
            clipObjArray.push_back(c);
        }
        model->clipping.insert(std::make_pair(name, clipObjArray));

    }
    
}


void GozapReader::parseMCObj(rapidjson::Value& mcObjs, std::string objName, GozapModel* model)
{
    CCLOG("GozapReader::parseMCObj");
    CCASSERT(mcObjs.IsObject() && mcObjs.HasMember(objName.c_str()) ,"mcObjs error");
    
    
    rapidjson::Value& mcObj = mcObjs[objName.c_str()];
    
    CCLOG("GozapReader::parseMCObj->mcObj");

    if(mcObj.IsObject() && mcObj.HasMember("layers") && mcObj.HasMember("frameTime") && mcObj.HasMember("totalFrame") && mcObj.HasMember("screenH"))
    {
        rapidjson::Value& layers = mcObj["layers"];
        rapidjson::Value& frameTime = mcObj["frameTime"];
        rapidjson::Value& totalFrame = mcObj["totalFrame"];
        rapidjson::Value& screenH = mcObj["screenH"];
        if(mcObj.HasMember("direction")){
            rapidjson::Value& direction = mcObj["direction"];
            model->setDirection(direction.GetInt());
        }else{
            model->setDirection(1);
        }
        
        if( ! (  layers.IsArray() && layers.Size() > 0 && totalFrame.IsInt()  ) ){
            CCLOG("mcObj members error");
            
            return ;
        }
        if(mcObj.HasMember("screenY")){
            rapidjson::Value& screenY = mcObj["screenY"];
            model->setScreenY(screenY.GetDouble());
        }
        if(mcObj.HasMember("floor")){
            rapidjson::Value& floor = mcObj["floor"];
            model->setFloor(floor.GetDouble());
        }
        if(mcObj.HasMember("floorHeight")){
            rapidjson::Value& floorH = mcObj["floorHeight"];
            model->setFloorH(floorH.GetDouble());
        }
        model->setScreenH(screenH.GetDouble());
        model->setFrameTime(frameTime.GetInt());
        model->setTotalFrame(totalFrame.GetInt());
        
        GozapReader::parseFrameMoveObj(mcObj, model);
        GozapReader::parseLayers(layers, model);
        
        GozapReader::parseFrameLabels(mcObj, model);
        
        
    }else{
        CCLOG("GozapReader::parseMCObj error mcObj");
        return;
    }
}

void GozapReader::parseLayers(rapidjson::Value& layers, GozapModel* model)
{
    CCLOG("GozapReader::parseMCObj->layer");
    
    for (unsigned int i = 0; i< layers.Size(); i++)
    {
        rapidjson::Value &layer = layers[i];
        
        if(! (  layer.IsArray() && layer.Size() > 0  ) ){
            CCLOG("layer error");
            return;
        }
        
        std::vector<SubSpriteFrame> frameVector;
        int frameIndex = 0;
        
        for (int j = 0; j < layer.Size(); j++)
        {
            if(j == 1){
                CCLOG("debug j == 1");
            }
            
            rapidjson::Value& obj = layer[j];
            if ( !   obj.IsObject()  ){
                CCLOG("obj error, j=%d", j);
                continue;
            }
            std::string libName ;
            if(obj.HasMember("libName")){
                libName = obj["libName"].GetString();
            }else{
                if (j == 0) {
                    libName = "";
                }else{
                    libName = ((SubSpriteFrame)frameVector.at(frameIndex-1)).libName;
                }
            }
            
            int frameNum = obj.HasMember("frameNum") ?  obj["frameNum"].GetInt() : 0;
            
            double x = obj.HasMember("x") ? obj["x"].GetDouble() : 0;
            double y = obj.HasMember("y") ? obj["y"].GetDouble() : 0;
            
            double cx = obj.HasMember("cx") ? obj["cx"].GetDouble() : 0;
            double cy = obj.HasMember("cy") ? obj["cy"].GetDouble() : 0;
            
            double a = obj.HasMember("a") ? obj["a"].GetDouble() : 1;
            double b = obj.HasMember("b") ? obj["b"].GetDouble() : 0;
            double c = obj.HasMember("c") ? obj["c"].GetDouble() : 0;
            double d = obj.HasMember("d") ? obj["d"].GetDouble() : 1;
            
            
            while(frameNum >= 0){   // 至少一次
                
                SubSpriteFrame f;
                if (!obj.HasMember("x")) {
                    libName = "";
                }
                f = SubSpriteFrameMake(libName, frameIndex, a, b, c, d, x, y, cx, cy);
                frameVector.push_back(f);
                frameNum--;
                if(frameIndex == 72){
                    CCLOG("103");
//                    CCASSERT(false, "frameindex=%d");
                }
                frameIndex++;
            }
            
        } // for layer
        
        CCASSERT(model->getTotalFrame() == frameVector.size(), "error json mcObj layer");
        auto subSprite = SubSprite::createWithSubSpriteFrameVector(frameVector, i, model);
        model->pushSubSprite(subSprite);
        
    } // for layers
    
}



void GozapReader::parseFrameLabels(rapidjson::Value& mcObj, GozapModel* model)
{
    CCLOG("parseMCObj->frameLabels");
    if(mcObj.HasMember("frameLabels")){
        rapidjson::Value& frameLabels = mcObj["frameLabels"];
        if (frameLabels.IsObject()) {
            for (rapidjson::Value::ConstMemberIterator itr = frameLabels.MemberonBegin(); itr != frameLabels.MemberonEnd(); ++itr)
            {
                std::string name = itr->name.GetString();
                rapidjson::Value& v = (rapidjson::Value&)itr->value;
                
                int begin = v["begin"].GetInt();
                int end = v.HasMember("end") ? v["end"].GetInt() : model->getTotalFrame() - 1;
                
                std::vector<int> vec;
                vec.push_back(begin);
                vec.push_back(end);
                model->frameLabels.insert(std::make_pair(name, vec));
                
                Point des = Vec2(0, 0);
                for (std::map<int, Vec2>::iterator it = model->frameMoveObj.begin(); it != model->frameMoveObj.end(); it++) {
                    int index = it->first;
                    if (index >= begin && index <= end) {
                        Point p = it->second;
                        des += p;
                    }
                }
                model->defaultActionDestinationMap.insert(std::make_pair(name, des));
                
            }
        }
    }
    std::vector<int> vec2;
    vec2.push_back(0);
    vec2.push_back(model->getTotalFrame() - 1);
    model->frameLabels.insert(std::make_pair("all", vec2));
}

void GozapReader::parseFrameMoveObj(rapidjson::Value& mcObj, GozapModel* model)
{
    if (mcObj.HasMember("frameMoveObj")) {
        rapidjson::Value& frameMoveObj = mcObj["frameMoveObj"];
        if (frameMoveObj.IsObject()) {
            for (rapidjson::Value::ConstMemberIterator itr = frameMoveObj.MemberonBegin(); itr != frameMoveObj.MemberonEnd(); ++itr)
            {
                std::string name = itr->name.GetString();
                double x = itr->value["x"].GetDouble();
                double y = itr->value["y"].GetDouble();
                std::stringstream ss(name);
                int name_int;
                ss >> name_int;
                
                model->frameMoveObj.insert(std::make_pair(name_int, Vec2(x , y)));
            }
        }
        
    }
}


