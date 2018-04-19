//
//  LenkeScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/3/29.
//

#include "LenkeScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *LenkeScene::createScene(){
    return LenkeScene::create();
}
bool LenkeScene::init(){
    if (!Scene::init()) {
        return false;
    }
    
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_lenke.png");
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
    this->addChild(backBtn);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_group_leader_sure.png", "btn_group_leader_sure.png");
    sureBtn->setPosition(Vec2(visibleSize.width-100, visibleSize.height-85));
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            pushDataToNetWork();
            log("Lenke sure");
        }
            
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    
    scrollV=createTableView(Vec2(0, visibleSize.height-145), Size(visibleSize.width, visibleSize.height-175));
    this->addChild(scrollV);
    return true;
}
ScrollView* LenkeScene::createTableView(Vec2 origin,Size visibleSize){
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(origin.x, origin.y));
    scrollView->setAnchorPoint(Vec2(0, 1));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);//方向
    scrollView->setScrollBarEnabled(true);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, visibleSize.height));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 0, 255));//设置背景颜色
    
    auto moveView=Sprite::create("alpha.png");
    moveView->setAnchorPoint(Vec2(0, 1));
    moveView->setContentSize(visibleSize);
    scrollView->addChild(moveView);
    
    auto step1SP=Sprite::create("recover_rect_green.png");
    step1SP->setAnchorPoint(Vec2(0, 0));
    step1SP->setContentSize(Size(visibleSize.width-26, 60));
    step1SP->setPosition(Vec2(13, visibleSize.height-60));
    moveView->addChild(step1SP);
    auto step1LB = Label::createWithSystemFont("step1","Arial",38,Size(300,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    step1LB->setPosition(Vec2(46,0));
    step1LB->setTextColor(Color4B(255, 255, 255, 255));
    step1LB->setAnchorPoint(Vec2(0, 0));
    step1SP->addChild(step1LB);
    
   textfieldTop1=createBasicData(moveView, Vec2(59, visibleSize.height-70-50), "顶锥1", "数值,可不填");
    textfieldTop2=createBasicData(moveView, Vec2(59, visibleSize.height-70*2-50), "顶锥2", "数值");
    textfieldTop3=createBasicData(moveView, Vec2(59, visibleSize.height-70*3-50), "顶锥3", "数值,可不填");
    textfieldCobb1=createBasicData(moveView, Vec2(59, visibleSize.height-70*4-50), "Cobb1", "数值");
    textfieldCobb2=createBasicData(moveView, Vec2(59, visibleSize.height-70*5-50), "Cobb2", "数值");
    textfieldCobb3=createBasicData(moveView, Vec2(59, visibleSize.height-70*6-50), "Cobb3", "数值");
    textfieldCobb1->setVisible(false);
    textfieldCobb2->setVisible(false);
    textfieldCobb3->setVisible(false);
    textfieldCobbSB1=createBasicData(moveView, Vec2(59, visibleSize.height-70*7-50), "Cobb SB1", "数值");
    textfieldCobbSB2=createBasicData(moveView, Vec2(59, visibleSize.height-70*8-50), "Cobb SB2", "数值");
    textfieldCobbSB3=createBasicData(moveView, Vec2(59, visibleSize.height-70*9-50), "Cobb SB3", "数值");
    textfieldCobbSB1->setVisible(false);
    textfieldCobbSB2->setVisible(false);
    textfieldCobbSB3->setVisible(false);
    textfieldKP1=createBasicData(moveView, Vec2(59, visibleSize.height-70*10-50), "KP1(T2-5)", "数值");
    textfieldKP2=createBasicData(moveView, Vec2(59, visibleSize.height-70*11-50), "KP2(T10-L2)", "数值");
    textfieldKP3=createBasicData(moveView, Vec2(59, visibleSize.height-70*12-50), "KP3(T5-12)", "数值");
    textfieldKP1->setVisible(false);
    textfieldKP2->setVisible(false);
    textfieldKP3->setVisible(false);
    auto step2SP=Sprite::create("recover_rect_green.png");
    step2SP->setAnchorPoint(Vec2(0, 0));
    step2SP->setContentSize(Size(visibleSize.width-26, 60));
    step2SP->setPosition(Vec2(13, visibleSize.height-70*12-120));
    moveView->addChild(step2SP);
    auto step2LB = Label::createWithSystemFont("step2","Arial",38,Size(300,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    step2LB->setPosition(Vec2(46,0));
    step2LB->setTextColor(Color4B(255, 255, 255, 255));
    step2LB->setAnchorPoint(Vec2(0, 0));
    step2SP->addChild(step2LB);
    
    auto csvlBtn=Button::create();
    csvlBtn->loadTextures("alpha.png", "alpha.png");//alpha.png
    csvlBtn->setPosition(Vec2(60, visibleSize.height-70*13-120));
    csvlBtn->setScale9Enabled(true);
    csvlBtn->setContentSize(Size(520, 70));
    csvlBtn->setAnchorPoint(Vec2(0, 0));
    csvlBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            Layer *layer=createSelectLayer();
            layer->setTag(200);
            this->addChild(layer);
        }
        default:
            break;
    }
    });
    moveView->addChild(csvlBtn);
    auto csLB1 = Label::createWithSystemFont("CSVL","Arial",35,Size(150,70),TextHAlignment::LEFT,TextVAlignment::CENTER);
    csLB1->setPosition(Vec2(60, visibleSize.height-70*13-120));
    csLB1->setTextColor(Color4B(91, 144, 229, 255));
    csLB1->setAnchorPoint(Vec2(0, 0));
    moveView->addChild(csLB1);
    csvlNum=Label::createWithSystemFont("","Arial",35,Size(visibleSize.width-320,70),TextHAlignment::RIGHT,TextVAlignment::CENTER);
    csvlNum->setPosition(Vec2(250, visibleSize.height-70*13-120));
    csvlNum->setTextColor(Color4B::BLACK);
    csvlNum->setAnchorPoint(Vec2(0, 0));
    moveView->addChild(csvlNum);
    
    auto step3SP=Sprite::create("recover_rect_green.png");
    step3SP->setAnchorPoint(Vec2(0, 0));
    step3SP->setContentSize(Size(visibleSize.width-26, 30));
    step3SP->setPosition(Vec2(13, visibleSize.height-70*13-150));
    moveView->addChild(step3SP);
    
    auto resultLB = Label::createWithSystemFont("结果","Arial",35,Size(100,70),TextHAlignment::LEFT,TextVAlignment::CENTER);
    resultLB->setPosition(Vec2(60, visibleSize.height-70*14-150));
    resultLB->setTextColor(Color4B(91, 144, 229, 255));
    resultLB->setAnchorPoint(Vec2(0, 0));
    moveView->addChild(resultLB);
    resultStr=Label::createWithSystemFont("3B-","Arial",35,Size(visibleSize.width-270,70),TextHAlignment::RIGHT,TextVAlignment::CENTER);
    resultStr->setPosition(Vec2(200, visibleSize.height-70*14-150));
    resultStr->setTextColor(Color4B::BLACK);
    resultStr->setAnchorPoint(Vec2(0, 0));
    moveView->addChild(resultStr);
    
    
#warning -在这里设置没有用，因为当innerSize<contentSize，以contentSize为准
    float pointY2=visibleSize.height-40-(70*14+150);
    if (visibleSize.height>visibleSize.height-20-pointY2) {
        scrollView->setContentSize(Size(visibleSize.width,visibleSize.height-20-pointY2));
        scrollView->setInnerContainerSize(Size(visibleSize.width, visibleSize.height-20-pointY2));
        moveView->setPosition(Vec2(0, scrollView->getInnerContainerSize().height));
    }else{
        scrollView->setContentSize(Size(visibleSize.width,visibleSize.height));
        scrollView->setInnerContainerSize(Size(visibleSize.width, visibleSize.height-20-pointY2));
        moveView->setPosition(Vec2(0, scrollView->getInnerContainerSize().height));
    }
    log("%f,%f",scrollView->getInnerContainerSize().height,visibleSize.height-20-pointY2);
    return scrollView;
}

TextField*  LenkeScene::createBasicData(Sprite* bkView,Vec2 point,string name1,string name2){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto userName = Label::createWithSystemFont(name1,"Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userName->setPosition(point);
    userName->setTextColor(Color4B(91, 144, 229, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    auto textFieldUser = TextField::create(name2,"Arial",35);
    textFieldUser->setMaxLength(40);
    textFieldUser->setTouchSize(Size(visibleSize.width-300, 50));
    textFieldUser->setPosition(Vec2(visibleSize.width-70,point.y));
    textFieldUser->setAnchorPoint(Vec2(1,0));
    textFieldUser->setContentSize(Size(visibleSize.width-300,50));
    textFieldUser->setTextColor(Color4B::BLACK);
    textFieldUser->setPlaceHolderColor(Color4B::GRAY);
    textFieldUser->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFieldUser->addEventListener(CC_CALLBACK_2(LenkeScene::eventCallBack, this));
    bkView->addChild(textFieldUser);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(51, point.y-6));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.85);
    bkView->addChild(lineV);
    
    return textFieldUser;
}

Layer* LenkeScene::createSelectLayer(){
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
    
    auto contentV = Sprite::create("bk_strength_select.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(66,244));
    contentV->setContentSize(Size(508,681));
    layer->addChild(contentV);
    
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_message_cancel.png", "btn_message_cancel.png");
    deleteBtn->setPosition(Vec2(114, 15));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->cocos2d::Node::setScale(0.87);
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            this->removeChildByTag(200);
            break;
    }
    });
    contentV->addChild(deleteBtn);
    
    auto fiveBtn=Button::create();
    fiveBtn->loadTextures("alpha.png", "alpha.png");
    fiveBtn->setTitleText("C");
    fiveBtn->setTitleColor(Color3B(40, 40, 40));
    fiveBtn->setTitleFontSize(45);
    fiveBtn->setPosition(Vec2(0, 83));
    fiveBtn->setAnchorPoint(Vec2(0,0));
    fiveBtn->setScale9Enabled(true);
    fiveBtn->setContentSize(Size(508, 166));
    fiveBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            csvlNum->setString("C");
            string result=addDataToResult();
            resultStr->setString(result);
            this->removeChildByTag(200);
        }
        default:
            break;
    }
    });
    contentV->addChild(fiveBtn);
    
    createSelectItem("B", 166+83, contentV);
    createSelectItem("A", 166*2+83, contentV);
    
    return layer;
}

void LenkeScene::createSelectItem(string title,float Y,Sprite* contentV){
    auto fourBtn=Button::create();
    fourBtn->loadTextures("alpha.png", "alpha.png");
    fourBtn->setTitleText(title);
    fourBtn->setTitleColor(Color3B(40, 40, 40));
    fourBtn->setTitleFontSize(45);
    fourBtn->setPosition(Vec2(0, Y));
    fourBtn->setAnchorPoint(Vec2(0,0));
    fourBtn->setScale9Enabled(true);
    fourBtn->setContentSize(Size(508, 166));
    fourBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            Button *btn=(Button *)sender;
             csvlNum->setString(btn->getTitleText());
            string result=addDataToResult();
            resultStr->setString(result);
            this->removeChildByTag(200);
        }
        default:
            break;
    }
    });
    contentV->addChild(fourBtn);
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(0, Y));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setContentSize(Size(508, 1.5));
    contentV->addChild(lineV);
    
}

std::string   LenkeScene::addDataToResult(){
    string result;
    if (strcmp(textfieldCobbSB1->getString().c_str(), "")!=0 ) {
        if (strcmp(textfieldKP1->getString().c_str(), "")!=0) {
        if (atoi(textfieldCobbSB1->getString().c_str())>=25||atoi(textfieldKP1->getString().c_str())>=20) {
            if (atoi(textfieldCobbSB3->getString().c_str())>=25||atoi(textfieldKP2->getString().c_str())>=20) {//2，4
                result="Lenke4";
            }else{result="Lenke2";}
        }
        }
    }else{
        if (atoi(textfieldCobb2->getString().c_str())>=atoi(textfieldCobb3->getString().c_str())) {//1，3
            if (atoi(textfieldCobbSB3->getString().c_str())>=25||atoi(textfieldKP2->getString().c_str())>=20) {
                result="Lenke3";
            }else{ result="Lenke1";;}
        }else{
            if (atoi(textfieldCobbSB2->getString().c_str())>=25||atoi(textfieldKP2->getString().c_str())>=20) {//5，6
                result="Lenke6";
            }else{ result="Lenke5";}
        }
    }
    result.append(csvlNum->getString().c_str());
   
    if (strcmp(textfieldKP3->getString().c_str(),"")!=0) {
        if(atoi(textfieldKP3->getString().c_str())>40){
            result.append("+");
        }else if (atoi(textfieldKP3->getString().c_str())<10){
            result.append("-");
        }else{result.append("N");}
    }
    return result;
}


void LenkeScene::eventCallBack(cocos2d::Ref* pSender,cocos2d::ui::TextField::EventType type)
{
    TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
    int tag= textField->getTag();
    switch (type){
        case cocos2d::ui::TextField::EventType::INSERT_TEXT:
            CCLOG("INSERT_TEXT");
            break;
        case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
            CCLOG("DELETE_BACKWARD");
            break;
        case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
        {
            if (strcmp(textfieldTop1->getString().c_str(), "")==0) {
                textfieldCobb1->setVisible(false);
                textfieldCobbSB1->setVisible(false);
                textfieldKP1->setVisible(false);
            }else{
                textfieldCobb1->setVisible(true);
                textfieldCobbSB1->setVisible(true);
                textfieldKP1->setVisible(true);
            }
            if (strcmp(textfieldTop2->getString().c_str(), "")==0) {
                textfieldCobb2->setVisible(false);
                textfieldCobbSB2->setVisible(false);
                textfieldKP2->setVisible(false);
            }else{
                textfieldCobb2->setVisible(true);
                textfieldCobbSB2->setVisible(true);
                textfieldKP2->setVisible(true);
            }
            if (strcmp(textfieldTop3->getString().c_str(), "")==0) {
                textfieldCobb3->setVisible(false);
                textfieldCobbSB3->setVisible(false);
                textfieldKP3->setVisible(false);
            }else{
                textfieldCobb3->setVisible(true);
                textfieldCobbSB3->setVisible(true);
                textfieldKP3->setVisible(true);
            }
            CCLOG("DETACH_WITH_IME");
            break;
        }
    }
}
void LenkeScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char content[1000]={0};
    sprintf(content,"%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s",textfieldTop1->getString().c_str(),textfieldTop2->getString().c_str(),textfieldTop3->getString().c_str(),textfieldCobb1->getString().c_str(),textfieldCobb2->getString().c_str(),textfieldCobb3->getString().c_str(),textfieldCobbSB1->getString().c_str(),textfieldCobbSB2->getString().c_str(),textfieldCobbSB3->getString().c_str(),textfieldKP1->getString().c_str(),textfieldKP2->getString().c_str(),textfieldKP3->getString().c_str(),csvlNum->getString().c_str(),resultStr->getString().c_str());
    char*contentStr=content;
    char memberUrl[1000]={0};
    sprintf(memberUrl,"recordId=%s&keys=%s&answers=%s",UserDefault::getInstance()->getStringForKey("caseId").c_str(),"pf_lenke_dz1;pf_lenke_dz2;pf_lenke_dz3;pf_lenke_cobb1;pf_lenke_cobb2;pf_lenke_cobb3;pf_lenke_cobbsb1;pf_lenke_cobbsb2;pf_lenke_cobbsb3;pf_lenke_kp1;pf_lenke_kp2;pf_lenke_kp3;pf_lenke_csvl;pf_lenke_result",contentStr);
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/updateMedicalRecords";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(LenkeScene::onHttpRequestCompleted, this),url);
}

void LenkeScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
    
    rapidjson::Document jsondata;
    
    jsondata.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (jsondata.HasParseError()) {
        
        return;
    }
    if(jsondata.HasMember("status")){
        if (jsondata["status"].GetInt()==0) {
            Director::getInstance()->popScene();
        }
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        jsondata.Accept(writer);
        CCLOG("%s", buffer.GetString());
    }
}
