//
//  SickRoomScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/4.
//

#ifndef SickRoomScene_hpp
#define SickRoomScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"
#include <iostream>

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
USING_NS_CC;
class SickRoomScene:public cocos2d::Scene{
public:
    void onEnter();
    int bedNum;
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SickRoomScene);
    
    cocos2d::Layer* addCalendarLayer();
    
    cocos2d::Layer* createPromptLayer(std::string content);
    
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);
    void selectedItemEventScrollView(Ref* pSender, cocos2d::ui::ScrollView::EventType type);
    
    cocos2d::ui::Layout *createMessageLayout(int i,std::string title,std::string content);
    
    
    void onHttpRequestCompleted3(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushLeaveHospitalToNetWork();
    
    void getUserDataToNetWork();
    void onHttpRequestCompleted2(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
    std::string searchContentForInfoData(std::string content,std::string title,rapidjson::Document& data);
    
private:
     rapidjson::Document infoData;
//impress
    rapidjson::Document impressData;
     rapidjson::Document formationData;
     rapidjson::Document infectData;
     rapidjson::Document injuryData;
//symptom
    rapidjson::Document symptomData;
    
     rapidjson::Document userData;
    
    cocos2d::ui::ListView* lv;
    
    
    
    
    float createVideoLayerForListView(float height,cocos2d::ui::Layout*bkView);
    
#pragma-读取网络图片
     void onHttpRequestImageCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void  getImageFromNetWork(std::string url,int photoTag);
    
    cocos2d::ValueVector videoArr;
    
};

#endif /* SickRoomScene_hpp */
