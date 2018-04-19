//
//  UpdateBedScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/3/15.
//

#ifndef UpdateBedScene_hpp
#define UpdateBedScene_hpp

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

#include <stdio.h>
#include "ui/CocosGUI.h"
#include "QR_Encode.h"
class UpdateBedScene:public cocos2d::Scene{
    public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void onEnter();
    CREATE_FUNC(UpdateBedScene);
    
    int bedNum;
    
    cocos2d::Layer* createUpdateBedPromptLayer();//1000,选择新建还是导入
    cocos2d::Layer* createWriteCasePromptLayer();//1001,填写病例号
    cocos2d::Layer* createAddUserPromptLayer();//1002,新建
    cocos2d::Layer* createSelectSexPromptLayer();//1003,选择性别
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    
    
    //先查询
    void getUserDataToNetWork();
    void onHttpRequestCompleted2(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    //查询没有再新建
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void getUserInfoToNetWork();
    std::string getTimeForSystem();
    //新建病例
    void createCaseToNetWork();
    void onHttpRequestCompleted3(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    
//通过caseNo获取病人病例
    void pushCaseNoToNetWork();
    void onHttpRequestCompleted5(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);

    
    void onHttpRequestCompleted4(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void updateBedToNetWork();
//修改病人状态
    void onHttpRequestCompleted6(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void changeStatusToNetWork();
    rapidjson::Document bedInfoData;
private:
    cocos2d::Map<int, cocos2d::ui::CheckBox*> boxDic;
     int selectBoxIndex;
     int selectBoxIndexSex;
    cocos2d::ui::TextField* textFieldCase;
    cocos2d::ui::TextField* textFieldName;
    cocos2d::ui::TextField* textFieldAge;
    cocos2d::ui::TextField* textFieldCaseNo;
    cocos2d::Label* sexLB;
    
    rapidjson::Document infoData;
    rapidjson::Document userData;
    std::string bedId;
    
};

#endif /* UpdateBedScene_hpp */
