//
//  SpineTendernessScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/21.
//

#ifndef SpineTendernessScene_hpp
#define SpineTendernessScene_hpp
#include "cocos2d.h"
#include <stdio.h>
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
USING_NS_CC;
class SpineTendernessScene:public cocos2d::Scene{
public:
    static  cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SpineTendernessScene);
    
    void menuSelectCallback(cocos2d::Ref* pSender);
    
    
    Label*   createRectButton(cocos2d::Vec2 point,int index,int tag);
    
    
    void onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    void onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    void onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    void onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    
    std::string getJsonData(int type);
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void pushDataToNetWork();
    
    
};
#endif /* SpineTendernessScene_hpp */
