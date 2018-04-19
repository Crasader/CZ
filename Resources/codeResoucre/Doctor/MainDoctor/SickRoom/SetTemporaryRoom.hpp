//
//  SetTemporaryRoom.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/3.
//

#ifndef SetTemporaryRoom_hpp
#define SetTemporaryRoom_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;
class SetTemporaryRoom:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SetTemporaryRoom);
    cocos2d::ui::EditBox*  createBasicData(cocos2d::Sprite* bkView,cocos2d::Vec2 point,std::string name1,std::string name2);
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
private:
    cocos2d::ui::EditBox* textfieldHospital;
    cocos2d::ui::EditBox* textfieldBuilding;
    cocos2d::ui::EditBox* textfieldFloor;
    cocos2d::ui::EditBox* textfieldBed;
    
    cocos2d::ui::Button * importCompleteBtn;
};

#endif /* SetTemporaryRoom_hpp */
