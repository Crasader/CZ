//
//  SelectDoctorScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/3/20.
//

#include "SelectDoctorScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace rapidjson; // 命名空间
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
rapidjson::Value selectArr(rapidjson::kArrayType);
Scene *SelectDoctorScene::createScene(){
    return SelectDoctorScene::create();
}
bool SelectDoctorScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    
    auto bkView=Sprite::create("bk_step4.png");
    bkView->setPosition(Vec2(0, 0));
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
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
    bkView->addChild(backBtn);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_step4_sure.png", "btn_step4_sure.png");
    sureBtn->setPosition(Vec2(visibleSize.width-70, visibleSize.height-85));
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            log("确认选择医生");
            pushDoctorDataToNetWork();
        }
            
        default:
            break;
    }
    });
    bkView->addChild(sureBtn);
    
    auto serachV=Sprite::create("bk_step4_search.png");
    serachV->setPosition(Vec2(14, 915));
    serachV->setAnchorPoint(Vec2(0, 0));
    serachV->setScale(0.86);
    bkView->addChild(serachV);
    
    auto searchBtn=Button::create();
    searchBtn->loadTextures("btn_step4_search.png", "btn_step4_search.png");
    searchBtn->setPosition(Vec2(serachV->getContentSize().width-61,20));
    searchBtn->setAnchorPoint(Vec2(0, 0));
    searchBtn->setScale9Enabled(true);
    searchBtn->setContentSize(Size(41, 37));
    searchBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
        }
            
        default:
            break;
    }
    });
    serachV->addChild(searchBtn);
    searchText = TextField::create("最多可选三位医生作为您的责任医生","Arial",30);
    searchText->setMaxLength(40);
    searchText->setTouchSize(Size(visibleSize.width-300, 40));
    searchText->setPosition(Vec2(120,20));
    searchText->setAnchorPoint(Vec2(0,0));
    searchText->setContentSize(Size(visibleSize.width-300,40));
    searchText->setTextColor(Color4B::BLACK);
    searchText->setPlaceHolderColor(Color4B(91, 144, 230, 255/2));
    searchText->setTextHorizontalAlignment(TextHAlignment::LEFT);
    searchText->addEventListener(CC_CALLBACK_2(SelectDoctorScene::eventCallBack, this));
    serachV->addChild(searchText);
    
    
#pragma-TableView
    scrollView=createTableView(Vec2(0, 0), Size(visibleSize.width, 910));
    bkView->addChild(scrollView);
    
    return true;
}

ScrollView* SelectDoctorScene::createTableView(Vec2 origin,Size visibleSize){
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(origin.x, origin.y));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);//方向
    scrollView->setScrollBarEnabled(true);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, visibleSize.height));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 0, 255));//设置背景颜色
    pushDataToNetWork();
    return scrollView;
}

Layer* SelectDoctorScene::createMessageLayer(int i, Size  innerSize){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    //Data
    rapidjson::Value& object = this->loginData["data"][i];
    if (selectArr.GetArray().Size()) {
        object=selectArr[i];
    }
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    layer->setContentSize(Size(visibleSize.width-40, 140));
    layer->setPosition(Point(20,innerSize.height-160*(i+1)+10));
    layer->setAnchorPoint(Vec2(0, 0));
    layer->setTag(1000+i);
    
    auto bkView=Sprite::create("bk_tableView_white.png");
    bkView->setPosition(Vec2(0, 0));
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(layer->getContentSize());
    layer->addChild(bkView);
    
    auto headV=Sprite::create("bk_headIV.png");
    headV->setPosition(Vec2(5, 5));
    headV->setAnchorPoint(Vec2(0, 0));
    float height5=headV->getContentSize().height;
    headV->setScale(125.0/height5);
    bkView->addChild(headV);
    auto headBtn=ImageView::create("bk_headIV.png");
    headBtn->setPosition(Vec2(0, 0));
    headBtn->setAnchorPoint(Vec2(0, 0));
    headBtn->setTouchEnabled(true);
    float height=headBtn->getContentSize().height;
    headBtn->setScale(125.0/height);
    headBtn->setTag(i);
    headV->addChild(headBtn);
    headBtn->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
        if (type == Widget::TouchEventType::ENDED){
            log("点击上传头像");
        }
    });
    string name=object["name"].GetString();
    
    if (object["intro"].IsObject()||object["intro"].IsNull()) {
    }else{
        string info=object["intro"].GetString();
        auto contentLB = Label::createWithSystemFont(info,"Arial",28,Size(380,80),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        contentLB->setPosition(Point(140,10));
        contentLB->setTextColor(Color4B(0, 0, 0, 255/2));
        contentLB->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(contentLB);
    }
    
    if (object["education"].IsObject()||object["education"].IsNull()) {
    }else{
        string education=object["education"].GetString();
        auto jobLB = Label::createWithSystemFont(education,"Arial",32,Size(380,60),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        jobLB->setPosition(Point(300,80));
        jobLB->setTextColor(Color4B(0, 0, 0, 240));
        jobLB->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(jobLB);
    }
    auto nameLB = Label::createWithSystemFont(name,"Arial",35,Size(380,60),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    nameLB->setPosition(Point(140,80));
    nameLB->setTextColor(Color4B(0, 0, 0, 255));
    nameLB->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(nameLB);
    
    auto selectCheckBox = CheckBox::create("btn_step4_unselect.png","btn_step4_select.png");
    //设置CheckBox的位置
    selectCheckBox->setPosition(Vec2(layer->getContentSize().width-60, 45));
    selectCheckBox->setTag(100+i);
    selectCheckBox->setAnchorPoint(Vec2(0, 0));
    selectCheckBox->setScale(0.87);
    //设置CheckBox是否可点击
    if (strcmp(object["userId"].GetString(), UserDefault::getInstance()->getStringForKey("userId").c_str())==0 ) {
        selectCheckBox->setSelectedState(true);
        selectCheckBox->setTouchEnabled(false);
        selectNumVector.push_back(atoi(object["id"].GetString()));
        nameMap[object["id"].GetString()] =object["name"].GetString();
    }else{
          selectCheckBox->setTouchEnabled(true);}
    selectCheckBox->addEventListener(CC_CALLBACK_2(SelectDoctorScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    bkView->addChild(selectCheckBox);
    boxDic.insert(100+i, selectCheckBox);
    
    return layer;
}

//实现CheckBox回调函数
void SelectDoctorScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    MenuItem* item = (MenuItem*)ref;
    int tag= item->getTag();
    auto   checkBox=(CheckBox*)this->getChildByTag(tag);
    log("tag %d",tag);
    //tag值100以及100+
    //     bool selected  = checkBox->getSelectedState();
    rapidjson::Value& object = this->loginData["data"][tag-100];
    if (selectArr.GetArray().Size()) {
        if (!selectArr[tag-100].IsNull()) {
            object=selectArr[tag-100];
        }
        StringBuffer buffer;
        rapidjson::Writer<StringBuffer> writer(buffer);
        selectArr.Accept(writer);
        CCLOG("%s", buffer.GetString());
    }
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:{
            log("id:%s",object["id"].GetString());
            vector<int>::iterator it;
            for(it=selectNumVector.begin();it!=selectNumVector.end();)
            {
                log("%d",*it);
                if(*it==atoi(object["id"].GetString()))//判断是否有重复
                    it=selectNumVector.erase(it);    //删除元素，返回值指向已删除元素的下一个位置
                else
                    ++it;    //指向下一个位置
            }
            selectNumVector.push_back(atoi(object["id"].GetString()));
            nameMap[object["id"].GetString()]=object["name"].GetString();
            log("SELECTED!");
            //            checkBox->setSelected(false);
            break;}
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:{
            vector<int>::iterator it;
            for(it=selectNumVector.begin();it!=selectNumVector.end();)
            {
                log("%d",*it);
                if(*it==atoi(object["id"].GetString()))
                    it=selectNumVector.erase(it);    //删除元素，返回值指向已删除元素的下一个位置
                else
                    ++it;    //指向下一个位置
            }
            log("UNSELECTED!");
            break;}
        default:
            break;
    }
}


void SelectDoctorScene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
{
    TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
    switch (type){
            
        case cocos2d::ui::TextField::EventType::INSERT_TEXT:
            if (textField->getString().length()) {
                log("有数据");
                for (int i=0; i<loginData["data"].Size(); i++) {
                    rapidjson::Value& object = this->loginData["data"][i];
                    rapidjson::Document::AllocatorType&allocator= loginData.GetAllocator();
                    CCLOG("%s", object["name"].GetString());
                    if(strcmp(object["name"].GetString(), textField->getString().c_str())==0){
                        log("%s",object["name"].GetString());
                        selectArr.PushBack(object, allocator);
                    }
                }
                if (selectArr.GetArray().Size()>0) {
                    scrollView->removeAllChildren();
                    /*             for (int j=0; j<loginData["data"].Size(); j++) {
                     rapidjson::Value& object = this->loginData["data"][j];
                     if (!object.IsNull()) {
                     log("%s",object["name"].GetString());}
                     Select4Scroll->removeChildByTag(1000+j);
                     }    */
                    for (int k=0; k<selectArr.GetArray().Size(); k++) {
                        Size visibleSize=Director::getInstance()->getVisibleSize();
                        scrollView->setInnerContainerSize(Size(visibleSize.width, 160*selectArr.GetArray().Size()));//设置内容大小
                        auto layer1 = createMessageLayer(k,scrollView->getInnerContainerSize());
                        scrollView->addChild(layer1);
                    }
                }
                
                log("%d",selectArr.GetArray().Size());
                
            }
            CCLOG("INSERT_TEXT");
            
            break;
        case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
            if (textField->getString().length()) {
                log("%s",textField->getString().c_str());
            }else{
                Size visibleSize=Director::getInstance()->getVisibleSize();
                scrollView->setInnerContainerSize(Size(visibleSize.width, 160*loginData["data"].Size()));//设置内容大小
                for (int j=0; j<selectArr.GetArray().Size(); j++) {
                    scrollView->removeChildByTag(1000+j);
                }
                selectArr.Clear();
                pushDataToNetWork();
            }
            CCLOG("DELETE_BACKWARD");
            break;
        case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
            
            CCLOG("DETACH_WITH_IME");
            
            break;
            
    }
    
}
#pragma-获取医疗小组成员
void SelectDoctorScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    string url="http://czapi.looper.pro/web/getGroupMember?groupId=";
    url.append(UserDefault::getInstance()->getStringForKey("groupId"));
    netManeger->sendMessage(url,CC_CALLBACK_2(SelectDoctorScene::onHttpRequestCompleted, this),nullptr);
}

void SelectDoctorScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
    if (!response)
    {
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    // rapidjson::Document Jsondata;
    this->loginData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    if (this->loginData.HasParseError()) {
        return;
    }
    if(this->loginData.HasMember("data")){
        Size visibleSize=Director::getInstance()->getVisibleSize();
        scrollView->setInnerContainerSize(Size(visibleSize.width, 160*loginData["data"].Size()));//设置内容大小
        for (int i=0; i<loginData["data"].Size(); i++) {
            auto layer1 = createMessageLayer(i,scrollView->getInnerContainerSize());
            scrollView->addChild(layer1);
        }
        //                for(int i = 0; i < this->loginData["data"].Size(); i++) {
        //                    rapidjson::Value& object = this->loginData["data"][i];
        //                    CCLOG("%s", object["name"].GetString());
        //                }
    }
    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer(buffer);
    loginData["data"].Accept(writer);
    CCLOG("%s", buffer.GetString());
    
}

void SelectDoctorScene::pushDoctorDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    string names="";
    vector<int>::iterator it;
    int count=0;
    for(it=selectNumVector.begin();it!=selectNumVector.end();)
    {
        string name=nameMap.at(to_string(*it)).asString();
        log("id:%d,name:%s",*it,name.c_str());
        if (count==0) {
            names.append(name);
        }else if(count==1||count==2){
            names.append(";");   names.append(name);
        }
        ++it;    //指向下一个位置
        ++count;
    }
    char memberUrl[1000]={0};

    sprintf(memberUrl,"recordId=%s&doctors=%s",UserDefault::getInstance()->getStringForKey("caseId").c_str(),names.c_str());
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/updateMedicalRecords";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(SelectDoctorScene::onHttpRequestCompleted2, this),url);
}

void SelectDoctorScene::onHttpRequestCompleted2(HttpClient* sender, HttpResponse* response)
{
    
    auto visibleSize=Director::getInstance()->getVisibleSize();
    if (!response)
    {
        return;
    }
    if(!response -> isSucceed()){
        log("response failed");
        log("error buffer: %s", response -> getErrorBuffer());
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
        Director::getInstance()->popScene();
    }
}



