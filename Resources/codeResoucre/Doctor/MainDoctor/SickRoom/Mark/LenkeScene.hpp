//
//  LenkeScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/3/29.
//

#ifndef LenkeScene_hpp
#define LenkeScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;
class LenkeScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LenkeScene);
   cocos2d::ui::ScrollView* createTableView(cocos2d::Vec2 point,cocos2d::Size size);
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    cocos2d::ui::TextField*  createBasicData(cocos2d::Sprite* bkView,cocos2d::Vec2 point,std::string name1,std::string name2);
    
    cocos2d::Layer* createSelectLayer();
    void createSelectItem(std::string title,float Y,cocos2d::Sprite* contentV);
    
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
//计算结果
    std::string   addDataToResult();
private:
    rapidjson::Document infoData;
     cocos2d::ui::ScrollView *scrollV;
    
    cocos2d::ui::TextField*textfieldTop1;
    cocos2d::ui::TextField*textfieldTop2;
    cocos2d::ui::TextField*textfieldTop3;
    cocos2d::ui::TextField*textfieldCobb1;
    cocos2d::ui::TextField*textfieldCobb2;
    cocos2d::ui::TextField*textfieldCobb3;
    cocos2d::ui::TextField*textfieldCobbSB1;
    cocos2d::ui::TextField*textfieldCobbSB2;
    cocos2d::ui::TextField*textfieldCobbSB3;
    cocos2d::ui::TextField*textfieldKP1;
    cocos2d::ui::TextField*textfieldKP2;
    cocos2d::ui::TextField*textfieldKP3;
    cocos2d::Label* csvlNum;
    cocos2d::Label* resultStr;
};
#endif /* LenkeScene_hpp */
