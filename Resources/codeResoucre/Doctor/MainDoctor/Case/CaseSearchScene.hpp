//
//  CaseSearchScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/29.
//

#ifndef CaseSearchScene_hpp
#define CaseSearchScene_hpp
#include <stdio.h>
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;
class CaseSearchScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(CaseSearchScene);
    
    cocos2d::ui::EditBox*  createBasicData(Sprite* bkView,Vec2 point,std::string name1,std::string name2);
    void  createLabelWithoutField(cocos2d::Sprite* bkView,cocos2d::Vec2 point,std::string name);
    
    
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    
    
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
private:
    rapidjson::Document infoData;
    
    cocos2d::ui::EditBox*textFiledName;
    cocos2d::ui::EditBox*textFiledSex;
    cocos2d::ui::EditBox*textFiledAge;
    cocos2d::ui::EditBox*textFiledCase;
    cocos2d::ui::EditBox*textFiledDate1;
    cocos2d::ui::EditBox*textFiledDate2;
};
#endif /* CaseSearchScene_hpp */
