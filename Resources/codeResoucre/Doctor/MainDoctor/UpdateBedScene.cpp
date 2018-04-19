//
//  UpdateBedScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/3/15.
//

#include "UpdateBedScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "NetWrokMangerData.hpp"
#include "SickRoomScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *UpdateBedScene::createScene(){
    return UpdateBedScene::create();
}

bool UpdateBedScene::init(){
    if (!Scene::init()) {
        return false;
    }
    bedNum=1;
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin =Director::getInstance()->getVisibleOrigin();
    auto bkView=Sprite::create("bk_updateBed.png");
    bkView->setContentSize(visibleSize);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setPosition(Vec2(0, 0));
    this->addChild(bkView);
    
    auto backBtn=Button::create();
    backBtn->loadTextures("btn_register_return.png", "btn_register_return.png");
    backBtn->setPosition(Vec2(80, visibleSize.height-85));
    backBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->popScene();
        default:
            break;
    }
    });
    this->addChild(backBtn);
    
    auto addbtn=Button::create();
    addbtn->loadTextures("alpha.png", "alpha.png");
    addbtn->setPosition(Vec2(53, 911));
    addbtn->setAnchorPoint(Vec2(0, 0));
    addbtn->setScale9Enabled(true);
    addbtn->setContentSize(Size(visibleSize.width-53*2, 65));
    addbtn->setColor(Color3B::BLACK);
    addbtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto layer=createAddUserPromptLayer();
            layer->setTag(1002);
            this->addChild(layer);
            log("新建");
        }default:
            break;
    }
    });
    bkView->addChild(addbtn);
    auto importbtn=Button::create();
    importbtn->loadTextures("alpha.png", "alpha.png");
    importbtn->setPosition(Vec2(53, 846));
    importbtn->setAnchorPoint(Vec2(0, 0));
    importbtn->setScale9Enabled(true);
    importbtn->setContentSize(Size(visibleSize.width-53*2, 65));
    importbtn->setColor(Color3B::BLACK);
    importbtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto layer=createUpdateBedPromptLayer();
            layer->setTag(1000);
            this->addChild(layer);
            log("导入");
        }
        default:
            break;
    }
    });
    bkView->addChild(importbtn);
    return true;
}

void UpdateBedScene::onEnter(){
    Size visibleSize=Director::getInstance()->getVisibleSize();
     selectBoxIndex=0;
    selectBoxIndexSex=0;
    bedNum=atoi(bedInfoData["data"]["bedNo"].GetString());
    bedId=bedInfoData["data"]["id"].GetString();
    Scene::onEnter();
    char str[10];
    sprintf(str,"%d床",bedNum);
    string title=str;
    auto timeLB = Label::createWithSystemFont(title,"Arial",45,Size(380,60),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
    timeLB->setPosition(Point(visibleSize.width/2,1023));
    timeLB->setTextColor(Color4B(255, 255, 255, 255));
    timeLB->setAnchorPoint(Vec2(0.5, 0));
    this->addChild(timeLB);
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    bedInfoData.Accept(writer);
    CCLOG("%s", buffer.GetString());
}

cocos2d::Layer* UpdateBedScene::createAddUserPromptLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(0, 0, 0, 255/3));
    layer->setContentSize(visibleSize);
    layer->setPosition(Point(0, 0));
    layer->setAnchorPoint(Vec2(0, 0));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    auto contentV = Sprite::create("bk_add_bed_case.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(0,0));
    contentV->setContentSize(visibleSize);
    layer->addChild(contentV);
    
    char str[10];
    sprintf(str,"%d床",bedNum);
    string title=str;
    auto timeLB = Label::createWithSystemFont(title,"Arial",45,Size(380,60),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
    timeLB->setPosition(Point(visibleSize.width/2,1023));
    timeLB->setTextColor(Color4B(255, 255, 255, 255));
    timeLB->setAnchorPoint(Vec2(0.5, 0));
    contentV->addChild(timeLB);
    
    auto backBtn=Button::create();
    backBtn->loadTextures("btn_register_return.png", "btn_register_return.png");
    backBtn->setPosition(Vec2(80, visibleSize.height-85));
    backBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            this->removeChildByTag(1002);
        default:
            break;
    }
    });
    contentV->addChild(backBtn);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_group_leader_sure.png", "btn_group_leader_sure.png");
    sureBtn->setPosition(Vec2(visibleSize.width-100, visibleSize.height-85));
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            if (strcmp(textFieldName->getString().c_str(), "")!=0&&strcmp(textFieldAge->getString().c_str(), "")!=0&&strcmp(textFieldCaseNo->getString().c_str(), "")!=0&&strcmp(sexLB->getString().c_str(), "必选")!=0) {
#pragma-先注册病人信息，获取到patientId，然后新建病例获取到caseId,再加上bedId
                getUserDataToNetWork();
            }
        }
            
        default:
            break;
    }
    });
    contentV->addChild(sureBtn);
    
    textFieldName = TextField::create("必填","Arial",36);
    textFieldName->setMaxLength(40);
    textFieldName->setTouchSize(Size(400, 65));
    textFieldName->setPosition(Vec2(180,920));
    textFieldName->setAnchorPoint(Vec2(0,0));
    textFieldName->setContentSize(Size(400, 65));
    textFieldName->setTextColor(Color4B::BLACK);
    textFieldName->setPlaceHolderColor(Color4B::GRAY);
    textFieldName->setTextHorizontalAlignment(TextHAlignment::LEFT);
    textFieldName->addEventListener(CC_CALLBACK_2(UpdateBedScene::eventCallBack, this));
    contentV->addChild(textFieldName);
    
    sexLB= Label::createWithSystemFont("必选","Arial",36,Size(380,65),TextHAlignment::LEFT,TextVAlignment::CENTER);
    sexLB->setPosition(Point(180,840));
    sexLB->setTextColor(Color4B(0, 0, 0, 255));
    sexLB->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(sexLB);
    auto sexbtn=Button::create();
    sexbtn->loadTextures("alpha.png", "alpha.png");
    sexbtn->setPosition(Vec2(180, 840));
    sexbtn->setAnchorPoint(Vec2(0, 0));
    sexbtn->setScale9Enabled(true);
    sexbtn->setContentSize(Size(400, 65));
    sexbtn->setColor(Color3B::BLACK);
    sexbtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto layer=createSelectSexPromptLayer();
            layer->setTag(1003);
            this->addChild(layer);
            log("选择性别");
        }default:
            break;
    }
    });
    contentV->addChild(sexbtn);
    
    
    
    textFieldAge = TextField::create("必填","Arial",36);
    textFieldAge->setMaxLength(40);
    textFieldAge->setTouchSize(Size(400, 65));
    textFieldAge->setPosition(Vec2(180,790));
    textFieldAge->setAnchorPoint(Vec2(0,0));
    textFieldAge->setContentSize(Size(400, 65));
    textFieldAge->setTextColor(Color4B::BLACK);
    textFieldAge->setPlaceHolderColor(Color4B::GRAY);
    textFieldAge->setTextHorizontalAlignment(TextHAlignment::LEFT);
    textFieldAge->addEventListener(CC_CALLBACK_2(UpdateBedScene::eventCallBack, this));
    contentV->addChild(textFieldAge);
    
    textFieldCaseNo = TextField::create("必填","Arial",36);
    textFieldCaseNo->setMaxLength(40);
    textFieldCaseNo->setTouchSize(Size(400, 65));
    textFieldCaseNo->setPosition(Vec2(200,725));
    textFieldCaseNo->setAnchorPoint(Vec2(0,0));
    textFieldCaseNo->setContentSize(Size(400, 65));
    textFieldCaseNo->setTextColor(Color4B::BLACK);
    textFieldCaseNo->setPlaceHolderColor(Color4B::GRAY);
    textFieldCaseNo->setTextHorizontalAlignment(TextHAlignment::LEFT);
    textFieldCaseNo->addEventListener(CC_CALLBACK_2(UpdateBedScene::eventCallBack, this));
    contentV->addChild(textFieldCaseNo);
    
    return layer;
}


cocos2d::Layer* UpdateBedScene::createSelectSexPromptLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(0, 0, 0, 255/3));
    layer->setContentSize(visibleSize);
    layer->setPosition(Point(0, 0));
    layer->setAnchorPoint(Vec2(0, 0));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    auto contentV = Sprite::create("prompt_select_sex.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(66,431));
    contentV->setContentSize(Size(508,349));
    layer->addChild(contentV);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_sureExit_sure.png", "btn_sureExit_sure.png");
    sureBtn->setPosition(Vec2(110, 25));
    sureBtn->setAnchorPoint(Vec2(0,0));
    sureBtn->setScale(0.9);
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            if (selectBoxIndexSex==3) {
                sexLB->setString("男");
                log("男");
            }else  if(selectBoxIndexSex==4){
                sexLB->setString("女");
                log("女");
            }
            this->removeChildByTag(1003);
            break;
        }
        default:
            break;
    }
    });
    contentV->addChild(sureBtn);
    
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_QRCode_close.png", "btn_QRCode_close.png");
    deleteBtn->setPosition(Vec2(450, 290));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            this->removeChildByTag(1003);
            break;
    }
    });
    contentV->addChild(deleteBtn);
    
    auto codeBox = CheckBox::create("alpha.png","rect_select_sex.png");
    //设置CheckBox的位置
    codeBox->setPosition(Vec2(-15,115));
    codeBox->setScale(0.85);
    //    box->setContentSize(Size(506, 64));
    codeBox->setTag(3);
    codeBox->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    codeBox->setTouchEnabled(true);
    codeBox->addEventListener(CC_CALLBACK_2(UpdateBedScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    contentV->addChild(codeBox);
    boxDic.insert(3, codeBox);
    
    auto caseBox = CheckBox::create("alpha.png","rect_select_sex.png");
    //设置CheckBox的位置
    caseBox->setPosition(Vec2(-15,186));
    caseBox->setScale(0.85);
    //    box->setContentSize(Size(506, 64));
    caseBox->setTag(4);
    caseBox->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    caseBox->setTouchEnabled(true);
    caseBox->addEventListener(CC_CALLBACK_2(UpdateBedScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    contentV->addChild(caseBox);
    boxDic.insert(4, caseBox);
    
    return layer;
}

cocos2d::Layer* UpdateBedScene::createUpdateBedPromptLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(0, 0, 0, 255/3));
    layer->setContentSize(visibleSize);
    layer->setPosition(Point(0, 0));
    layer->setAnchorPoint(Vec2(0, 0));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    auto contentV = Sprite::create("prompt_select_case.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(66,431));
    contentV->setContentSize(Size(508,349));
    layer->addChild(contentV);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_sureExit_sure.png", "btn_sureExit_sure.png");
    sureBtn->setPosition(Vec2(110, 25));
    sureBtn->setAnchorPoint(Vec2(0,0));
    sureBtn->setScale(0.9);
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            if (selectBoxIndex==1) {
                log("二维码");
            }else  if(selectBoxIndex==2){
                auto layer=createWriteCasePromptLayer();
                layer->setTag(1001);
                this->addChild(layer);
                 log("病例编号");
            }
            this->removeChildByTag(1000);
            break;
        }
        default:
            break;
    }
    });
    contentV->addChild(sureBtn);
    
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_QRCode_close.png", "btn_QRCode_close.png");
    deleteBtn->setPosition(Vec2(450, 290));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            this->removeChildByTag(1000);
            break;
    }
    });
    contentV->addChild(deleteBtn);
    
    auto codeBox = CheckBox::create("alpha.png","rect_select_sex.png");
    //设置CheckBox的位置
    codeBox->setPosition(Vec2(-15,115));
    codeBox->setScale(0.85);
//    box->setContentSize(Size(506, 64));
    codeBox->setTag(1);
    codeBox->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    codeBox->setTouchEnabled(true);
    codeBox->addEventListener(CC_CALLBACK_2(UpdateBedScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    contentV->addChild(codeBox);
    boxDic.insert(1, codeBox);
    
    auto caseBox = CheckBox::create("alpha.png","rect_select_sex.png");
    //设置CheckBox的位置
    caseBox->setPosition(Vec2(-15,186));
    caseBox->setScale(0.85);
    //    box->setContentSize(Size(506, 64));
    caseBox->setTag(2);
    caseBox->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    caseBox->setTouchEnabled(true);
    caseBox->addEventListener(CC_CALLBACK_2(UpdateBedScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    contentV->addChild(caseBox);
    boxDic.insert(2, caseBox);
    
    return layer;
}

cocos2d::Layer* UpdateBedScene::createWriteCasePromptLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(0, 0, 0, 255/3));
    layer->setContentSize(visibleSize);
    layer->setPosition(Point(0, 0));
    layer->setAnchorPoint(Vec2(0, 0));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    auto contentV = Sprite::create("prompt_write_case.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(66,431));
    contentV->setContentSize(Size(508,349));
    layer->addChild(contentV);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_sureExit_sure.png", "btn_sureExit_sure.png");
    sureBtn->setPosition(Vec2(110, 15));
    sureBtn->setAnchorPoint(Vec2(0,0));
    sureBtn->setScale(0.9);
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            if (strcmp(textFieldCase->getString().c_str(), "")!=0) {
#pragma-通过caseNo查询病人病例
                pushCaseNoToNetWork();
            }
            break;
        }
        default:
            break;
    }
    });
    contentV->addChild(sureBtn);
    
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_QRCode_close.png", "btn_QRCode_close.png");
    deleteBtn->setPosition(Vec2(450, 290));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            this->removeChildByTag(1001);
            break;
    }
    });
    contentV->addChild(deleteBtn);
    
    textFieldCase = TextField::create("在此输入病例号","Arial",40);
    textFieldCase->setMaxLength(40);
    textFieldCase->setTouchSize(Size(508, 65));
    textFieldCase->setPosition(Vec2(254,160));
    textFieldCase->setAnchorPoint(Vec2(0.5,0));
    textFieldCase->setContentSize(Size(508, 65));
    textFieldCase->setTextColor(Color4B::BLACK);
    textFieldCase->setPlaceHolderColor(Color4B::GRAY);
    textFieldCase->setTextHorizontalAlignment(TextHAlignment::CENTER);
    textFieldCase->addEventListener(CC_CALLBACK_2(UpdateBedScene::eventCallBack, this));
    contentV->addChild(textFieldCase);
    
    return layer;
}

void UpdateBedScene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
{
    switch (type){
            
        case cocos2d::ui::TextField::EventType::INSERT_TEXT:
            CCLOG("INSERT_TEXT");
            break;
        case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
            CCLOG("DELETE_BACKWARD");
        case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
            CCLOG("DETACH_WITH_IME");
            
            break;
    }
}

void UpdateBedScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            
            log("SELECTED!");
        {
            if (tag==1||tag==2) {
            selectBoxIndex=tag;
            for (int i=0; i<2; i++) {
                auto box=boxDic.at(i+1);
                if (tag!=i+1) {
                    box->setSelected(false);
                }
            }
            }
              if (tag==3||tag==4) {
                selectBoxIndexSex=tag;
            for (int i=2; i<4; i++) {
                auto box=boxDic.at(i+1);
                if (tag!=i+1) {
                    box->setSelected(false);
                }
            }
              }
        }
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED!");{
                 selectBoxIndex=0;
                selectBoxIndexSex=0;;
            }
            break;
        default:
            break;
    }
}


#pragma-个人资料界面
void UpdateBedScene::getUserDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char memberUrl[1000]={0};
    sprintf(memberUrl,"userId=%s",textFieldName->getString().c_str());
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/getUserById";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(UpdateBedScene::onHttpRequestCompleted2, this),url);
}

void UpdateBedScene::onHttpRequestCompleted2(HttpClient* sender, HttpResponse* response)
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    if (!response)
    {
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    // rapidjson::Document Jsondata;
    userData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    if (userData.HasParseError()) {
        return;
    }
    if(userData.HasMember("status")){
        if (userData["status"].GetInt()==0) {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            userData.Accept(writer);
            CCLOG("病人个人资料：  %s", buffer.GetString());
            if (userData["data"]!=false) {
                createCaseToNetWork();
            }else{
                getUserInfoToNetWork();
            }
        }else{
            getUserInfoToNetWork();
        }
    }
}

//新建用户
std::string UpdateBedScene::getTimeForSystem(){
    //获取系统时间
    struct timeval now;
    struct tm *time;
    gettimeofday(&now, NULL);
    time = localtime(&now.tv_sec);      //microseconds: 微秒
    int year = time->tm_year +1900;
    log("year = %d", year);         //显示年份
    char date1[32] = {0};
    sprintf(date1, "%d %02d %02d", (int)time->tm_year + 1900, (int)time->tm_mon + 1, (int)time->tm_mday);
    log("%s", date1);        //显示年月日
    char date2[50] = {0};
    sprintf(date2, "%02d %02d %02d", (int)time->tm_hour, (int)time->tm_min, (int)time->tm_sec);
    log("%s", date2);       //显示时分秒
    char date[100] = {0};
    sprintf(date, "%d%d%d%d%d%d", (int)time->tm_year + 1900, (int)time->tm_mon + 1, (int)time->tm_mday,(int)time->tm_hour, (int)time->tm_min, (int)time->tm_sec);
    return date;
}
void UpdateBedScene::getUserInfoToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    string gender="M";
    if (strcmp(sexLB->getString().c_str(), "男")==0) {
        gender="M";
    }else if(strcmp(sexLB->getString().c_str(), "女")==0){
        gender="F";
    }
    char memberUrl[1000]={0};
    sprintf(memberUrl,"userId=%s&passwd=%s&name=%s&sex=%s&age=%s&caseNo=%s",textFieldName->getString().c_str(),"123456",textFieldName->getString().c_str(),gender.c_str(),textFieldAge->getString().c_str(),textFieldCaseNo->getString().c_str());
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/createUser";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(UpdateBedScene::onHttpRequestCompleted, this),url);
}

void UpdateBedScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    if (!response)
    {
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    
    // rapidjson::Document Jsondata;
    
    userData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (userData.HasParseError()) {
        
        return;
    }
    if(userData.HasMember("status")){
        if (userData["status"].GetInt()==0) {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            userData.Accept(writer);
            CCLOG("%s", buffer.GetString());
            createCaseToNetWork();
        }
    }
}

#pragma-新建病例
void UpdateBedScene::createCaseToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    string keyValue="";
    if (!userData["data"]["step2"].IsNull()) {
        keyValue.append("&remark=");
        keyValue.append(userData["data"]["step2"].GetString());
    }
    char memberUrl[1000]={0};
    sprintf(memberUrl,"patientId=%s&doctorId=%s&type=%s&status=%s%s",userData["data"]["id"].GetString(),UserDefault::getInstance()->getStringForKey("id").c_str(),"bein","new",keyValue.c_str());
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/updateMedicalRecords";
    UserDefault::getInstance()->setStringForKey("patientId",userData["data"]["id"].GetString());
    this->removeChildByTag(1002);
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(UpdateBedScene::onHttpRequestCompleted3, this),url);
}

void UpdateBedScene::onHttpRequestCompleted3(HttpClient* sender, HttpResponse* response)
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    if (!response)
    {
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    
    rapidjson::Document Jsondata;
    
    Jsondata.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (Jsondata.HasParseError()) {
        
        return;
    }
    if(Jsondata.HasMember("status")){
        if (Jsondata["status"].GetInt()==0) {
            UserDefault::getInstance()->setStringForKey("caseId", Jsondata["recordId"].GetString());
            updateBedToNetWork();
        }
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        Jsondata.Accept(writer);
        CCLOG("%s", buffer.GetString());
    }
}





#pragma-绑定床位
void UpdateBedScene::updateBedToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/updateBed?bedId=%s&caseId=%s&patientId=%s",bedId.c_str(),UserDefault::getInstance()->getStringForKey("caseId").c_str(),UserDefault::getInstance()->getStringForKey("patientId").c_str());
    string memberURL=memberUrl;
    netManeger->sendMessage(memberURL,CC_CALLBACK_2(UpdateBedScene::onHttpRequestCompleted4, this),nullptr);
}

void UpdateBedScene::onHttpRequestCompleted4(HttpClient* sender, HttpResponse* response)
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    if (!response)
    {
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    rapidjson::Document Jsondata;
    Jsondata.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    if (Jsondata.HasParseError()) {
        return;
    }
    if(Jsondata.HasMember("status")){
        if (Jsondata["status"].GetInt()==0) {
#pragma-应该修改病人的状态为new后再跳转到sickRoomSC
            changeStatusToNetWork();
        }
    }
}

#pragma-修改病人状态
void UpdateBedScene::changeStatusToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/updatePatientStatus?status=%s&patientId=%s","new",UserDefault::getInstance()->getStringForKey("patientId").c_str());
    string memberURL=memberUrl;
    netManeger->sendMessage(memberURL,CC_CALLBACK_2(UpdateBedScene::onHttpRequestCompleted6, this),nullptr);
}

void UpdateBedScene::onHttpRequestCompleted6(HttpClient* sender, HttpResponse* response)
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    if (!response)
    {
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    rapidjson::Document Jsondata;
    Jsondata.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    if (Jsondata.HasParseError()) {
        return;
    }
    if(Jsondata.HasMember("status")){
        if (Jsondata["status"].GetInt()==0) {
            auto sickroomSC=(SickRoomScene*)SickRoomScene::createScene();
            sickroomSC->bedNum=bedNum;
            Director::getInstance()->replaceScene(sickroomSC);
        }
    }
}




#pragma-通过caseNo获取caseId和patientId
void UpdateBedScene::pushCaseNoToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/searchCase?caseNo=%s",textFieldCase->getString().c_str());
    string memberURL=memberUrl;
    netManeger->sendMessage(memberURL,CC_CALLBACK_2(UpdateBedScene::onHttpRequestCompleted5, this),nullptr);
}

void UpdateBedScene::onHttpRequestCompleted5(HttpClient* sender, HttpResponse* response)
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    if (!response)
    {
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    //    rapidjson::Document Jsondata;
    infoData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    if (infoData.HasParseError()) {
        return;
    }
    if(infoData.HasMember("status")){
        if (infoData["status"].GetInt()==0) {
            if (infoData["data"].Size()) {
                rapidjson::Value& data=infoData["data"][0];
                UserDefault::getInstance()->setStringForKey("patientId", data["patientId"].GetString());
                UserDefault::getInstance()->setStringForKey("caseId", data["id"].GetString());
                updateBedToNetWork();
            }
        }
    }
}
