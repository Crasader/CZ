//
//  AddOutpatientCaseScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/2.
//

#ifndef AddOutpatientCaseScene_hpp
#define AddOutpatientCaseScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;
using namespace cocos2d::ui;
class AddOutpatientCaseScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(AddOutpatientCaseScene);
    cocos2d::ui::EditBox*  createBasicData(cocos2d::Sprite* bkView,cocos2d::Vec2 point,std::string name1,std::string name2);
    
    
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    
    //声明CheckBox回调函数
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    
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
    
private:
    EditBox* textfieldName;
    EditBox* textfieldAge;
    std::string sexLB;
    
    //    rapidjson::Document infoData;
    rapidjson::Document userData;
    cocos2d::ui::Button * importCompleteBtn;

};

#endif /* AddOutpatientCaseScene_hpp */
