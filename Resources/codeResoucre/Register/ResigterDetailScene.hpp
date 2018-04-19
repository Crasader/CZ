//
//  ResigterDetailScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/13.
//

#ifndef ResigterDetailScene_hpp
#define ResigterDetailScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include <stdio.h>
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace cocos2d::ui;
class RegisterDetailScene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void onEnter();
    
    CREATE_FUNC(RegisterDetailScene);
    
    
    //声明CheckBox回调函数
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
    
    cocos2d::Layer* createAlbumLayer();
    
    
    cocos2d::ui::EditBox*  createBasicData(cocos2d::Sprite* bkView,cocos2d::Vec2 point,std::string name1,std::string name2);
    
    rapidjson::Document userData;
    
    
#pragma-用于加载数据
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork(std::string username,std::string passwd,std::string name,std::string sex,std::string age,std::string phone,std::string phone1,std::string idCardNo,std::string address,std::string headUrl,std::string caseNo);
private:
    rapidjson::Document loginData;
    cocos2d::Sprite*bkView;
    
    
    EditBox* textfieldName;
    EditBox* textfieldPass;
    EditBox* textfieldSurePass;
    EditBox* textfieldTel;
    EditBox* textfieldCaseTel2;
    EditBox* textfieldCaseAddress;
    EditBox* textfieldCaseRefer;
    std::string sexLB;
};


#endif /* ResigterDetailScene_hpp */
