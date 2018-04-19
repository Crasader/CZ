//
//  RegisterScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/11/29.
//

#ifndef RegisterScene_hpp
#define RegisterScene_hpp

#include "cocos2d.h"
#include <stdio.h>
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

#include "CursorTextField.hpp"
class RegisterScene:public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(RegisterScene);
    
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    cocos2d::Layer* createCaseLayer();
    
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
private:
    cocos2d::ui::EditBox* textFieldCase;
     rapidjson::Document loginData;
};


#endif /* RegisterScene_hpp */
