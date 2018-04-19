//
//  WaitChatDetailScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/3.
//

#ifndef WaitChatDetailScene_hpp
#define WaitChatDetailScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

class WaitChatDetailScene:public cocos2d::Scene ,public cocos2d::TextFieldDelegate{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
//用于传值
    void onEnter();
    int type;
    
    CREATE_FUNC(WaitChatDetailScene);
    
    void createBKView();
    void createScrollDetailView(cocos2d::ui::ScrollView* superV);
    float createLabel(cocos2d::Vec2 point,std::string name1,std::string name2,cocos2d::Sprite* superV);
//用于上传影像
    cocos2d::Layer* createUpdateImageLayer();
//用于上传头像
    cocos2d::Layer* createAlbumLayer();
    
    cocos2d::Layer*createRefuseLayer();
    
    cocos2d::Layer* createPromptLayer(std::string content);
    
    void createPhotoSpriteArr(float height);
    void eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type);
    
    rapidjson::Document infoData;
    int indexForData;
    
//获取个人信息
    void getInfoDataToNetWork();
    void onHttpRequestCompleted2(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    
//处理请求信息
    void pushDataToNetWork(std::string applicationType);
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    
    
    void onHttpRequestImageCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);
    void  getImageFromNetWork(std::string url,int photoTag);
private:
    
    
    rapidjson::Document userData;
    
    rapidjson::Document networkData;
    std::string refuseReason;
    
   
    cocos2d::Sprite*bkViewForPhoto;
    cocos2d::ui::ScrollView* scrollView;
    float contentHeight;
    cocos2d::ValueVector videoArr;
    cocos2d::Sprite* bkView;
    
//注：当type为1时接诊病人，当type为2时待接诊病人，当type为3时拒绝病人
};

#endif /* WaitChatDetailScene_hpp */
