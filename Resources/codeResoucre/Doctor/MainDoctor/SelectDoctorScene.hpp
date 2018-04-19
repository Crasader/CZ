//
//  SelectDoctorScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/3/20.
//

#ifndef SelectDoctorScene_hpp
#define SelectDoctorScene_hpp

#include <stdio.h>
#include <cocos2d.h>
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace std;
using namespace rapidjson; // 命名空间
class SelectDoctorScene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(SelectDoctorScene);
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    cocos2d::ui::ScrollView* createTableView(cocos2d::Vec2 point,cocos2d::Size size);
    cocos2d::Layer* createMessageLayer(int i, cocos2d::Size  innerSize);
    
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
    void pushDoctorDataToNetWork();
    void onHttpRequestCompleted2(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
private:
    rapidjson::Document loginData;
    cocos2d::Map<int, cocos2d::ui::CheckBox*> boxDic;
    rapidjson::vector<int>  selectNumVector;
    cocos2d::ui::TextField *  searchText;
    
    cocos2d::ValueMap nameMap;
    
    cocos2d::ui::ScrollView* scrollView;
    
};


#endif /* SelectDoctorScene_hpp */
