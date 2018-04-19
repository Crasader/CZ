//
//  MainScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/27.
//

#include "MainScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "AccountManageScene.hpp"
#include "GroupLeaderScene.hpp"
#include "GroupMemberScene.hpp"
#include "CaseSearchScene.hpp"
#include "ReceiveChatScene.hpp"
#include "WaitChatScene.hpp"
#include "SetTemporaryRoom.hpp"
#include "SickRoomScene.hpp"
#include "MessageNotificationScene.hpp"
#include "NetWrokMangerData.hpp"
#include "UpdateBedScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *MainScene::createScene(){
    return MainScene::create();
}

bool MainScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin =Director::getInstance()->getVisibleOrigin();
    
    boxVec = std::make_shared<Vector<CheckBox*>>();  //default constructor
    
    caseLayer=createSickRoomLayer();
    auto layer2=createOutPatientLayer();
    auto layer3=createCalendarLayer();
    auto layer4=createSickInfoLayer();
    multLayer = LayerMultiplex::create(caseLayer, layer2,layer3,layer4,nullptr);
    addChild(multLayer, 0);
    isTempBed=0;
    
    auto bottom=Sprite::create("bk_perfect_bottom.png");
    bottom->setPosition(Vec2(0, 0));
    bottom->setAnchorPoint(Vec2(0, 0));
    bottom->setContentSize(Size(visibleSize.width, 100));
    this->addChild(bottom);
    
/*    auto sickRoomBox = CheckBox::create("box_sickRoom_unselect.png","box_sickRoom_select.png");
    //设置CheckBox的位置
    sickRoomBox->setPosition(Vec2(50,10));
    sickRoomBox->setTag(0);
    sickRoomBox->setAnchorPoint(Vec2(0, 0));
    sickRoomBox->setScale(0.87);
    //设置CheckBox是否可点击
    sickRoomBox->setTouchEnabled(true);
    sickRoomBox->setSelected(true);
    sickRoomBox->addEventListener(CC_CALLBACK_2(MainScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(sickRoomBox);
    
    auto outPatientBox = CheckBox::create("box_outpatient_unselect.png","box_outpatient_select.png");
    //设置CheckBox的位置
    outPatientBox->setPosition(Vec2(200,10));
    outPatientBox->setTag(1);
    outPatientBox->setAnchorPoint(Vec2(0, 0));
    outPatientBox->setScale(0.87);
    //设置CheckBox是否可点击
    outPatientBox->setTouchEnabled(true);
    outPatientBox->addEventListener(CC_CALLBACK_2(MainScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(outPatientBox);
    
    auto calendarBox = CheckBox::create("box_calendar_unselect.png","box_calendar_select.png");
    //设置CheckBox的位置
    calendarBox->setPosition(Vec2(370,10));
    calendarBox->setTag(2);
    calendarBox->setAnchorPoint(Vec2(0, 0));
    calendarBox->setScale(0.87);
    //设置CheckBox是否可点击
    calendarBox->setTouchEnabled(true);
    calendarBox->addEventListener(CC_CALLBACK_2(MainScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(calendarBox);
    
    auto sickInfoBox = CheckBox::create("box_sickInfo_unselelct.png","box_sickInfo_selelct.png");
    //设置CheckBox的位置
    sickInfoBox->setPosition(Vec2(520,10));
    sickInfoBox->setTag(3);
    sickInfoBox->setAnchorPoint(Vec2(0, 0));
    sickInfoBox->setScale(0.87);
    //设置CheckBox是否可点击
    sickInfoBox->setTouchEnabled(true);
    sickInfoBox->addEventListener(CC_CALLBACK_2(MainScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(sickInfoBox); */
    
    auto start4 = MenuItemImage::create("box_sickInfo_unselelct.png","");  //显示为on
    auto stop4 = MenuItemImage::create("box_sickInfo_selelct.png","");  //显示为off
    auto toggle4 = MenuItemToggle::createWithCallback(
                                                      CC_CALLBACK_1(MainScene::menuLoginCallback,this),
                                                      start4,
                                                      stop4,
                                                      NULL);
    toggle4->setPosition(Vec2(520,10));//设置坐标在屏幕居中
    toggle4->setAnchorPoint(Vec2(0, 0));
    toggle4->setScale(0.87);
    toggle4->setTag(3);
    auto sickInfoBox = Menu::create(toggle4,NULL);
    sickInfoBox->setPosition(Point::ZERO);
    sickInfoBox->setTag(3);
    addChild(sickInfoBox);
    
    auto start3 = MenuItemImage::create("box_calendar_unselect.png","");  //显示为on
    auto stop3 = MenuItemImage::create("box_calendar_select.png","");  //显示为off
    auto toggle3 = MenuItemToggle::createWithCallback(
                                                      CC_CALLBACK_1(MainScene::menuLoginCallback,this),
                                                      start3,
                                                      stop3,
                                                      NULL);
    toggle3->setPosition(Vec2(370,10));//设置坐标在屏幕居中
    toggle3->setAnchorPoint(Vec2(0, 0));
    toggle3->setScale(0.87);
    toggle3->setTag(2);
    auto calendarBox = Menu::create(toggle3,NULL);
    calendarBox->setPosition(Point::ZERO);
    calendarBox->setTag(2);
    addChild(calendarBox);
    
    auto start2 = MenuItemImage::create("box_outpatient_unselect.png","");  //显示为on
    auto stop2 = MenuItemImage::create("box_outpatient_select.png","");  //显示为off
    auto toggle2 = MenuItemToggle::createWithCallback(
                                                      CC_CALLBACK_1(MainScene::menuLoginCallback,this),
                                                      start2,
                                                      stop2,
                                                      NULL);
    toggle2->setPosition(Vec2(200,10));//设置坐标在屏幕居中
    toggle2->setAnchorPoint(Vec2(0, 0));
    toggle2->setScale(0.87);
    toggle2->setTag(1);
    auto outPatientBox = Menu::create(toggle2,NULL);
    outPatientBox->setPosition(Point::ZERO);
    outPatientBox->setTag(1);
    addChild(outPatientBox);
    
    auto start = MenuItemImage::create("box_sickRoom_unselect.png","");  //显示为on
    auto stop = MenuItemImage::create("box_sickRoom_select.png","");  //显示为off
    auto toggle = MenuItemToggle::createWithCallback(
                                                     CC_CALLBACK_1(MainScene::menuLoginCallback,this),
                                                     start,
                                                     stop,
                                                     NULL);
    toggle->setPosition(Vec2(50,10));//设置坐标在屏幕居中
    toggle->setAnchorPoint(Vec2(0, 0));
    toggle->setScale(0.87);
    toggle->setTag(0);
    toggle->setSelectedIndex(1);
    auto sickRoomBox = Menu::create(toggle,NULL);
    sickRoomBox->setPosition(Point::ZERO);
    sickRoomBox->setTag(0);
    addChild(sickRoomBox);
    return true;
}

void MainScene::menuLoginCallback(Ref* pSender)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    MenuItemToggle* item=(MenuItemToggle*)pSender;
    int  index=item->getSelectedIndex();
    int tag= item->getTag();
    if (index==1) {//选中
        //切换按钮的高亮
        for (int i=0; i<4; i++) {
            if (i!=tag) {
                Menu * checkBox=(Menu*)this->getChildByTag(i);
                MenuItemToggle*toggle=(MenuItemToggle*)checkBox->getChildByTag(i);
                toggle->setSelectedIndex(0);
            }
        }
        //切换页面
        multLayer->switchTo(tag);
        onEnter();
    }else{
        item->setSelectedIndex(1);
    }
}

void MainScene::onEnter(){
    Scene::onEnter();
    pushDataToNetWork();
}

//病床
Layer* MainScene::createSickRoomLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    layer->setContentSize(visibleSize);
    layer->setTag(500);
    layer->setPosition(Point(0, 0));
    layer->setAnchorPoint(Vec2(origin.x, origin.y));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    
    auto bkView=Sprite::create("bk_sickRoom.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setTag(501);
    bkView->setContentSize(visibleSize);
    layer->addChild(bkView);
    createSickRoomWithBackView(bkView);
    return layer;
}
void MainScene::createSickRoomWithBackView(Sprite* bkView){
     auto visibleSize=Director::getInstance()->getVisibleSize();
    auto addBtn=Button::create();
    addBtn->loadTextures("btn_addCase_add.png", "btn_addCase_add.png");
    addBtn->setPosition(Vec2(visibleSize.width-100, visibleSize.height-85));
    addBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto temporaryRoomSC=SetTemporaryRoom::createScene();
            Director::getInstance()->pushScene(temporaryRoomSC);
        }
        default:
            break;
    }
    });
    bkView->addChild(addBtn);
    
    auto tempBedBox=CheckBox::create("box_tempBed_unselect.png","box_tempBed_select.png");
    //设置CheckBox的位置
    tempBedBox->setPosition(Vec2(visibleSize.width/2,918));
    tempBedBox->setTag(5);
    tempBedBox->setAnchorPoint(Vec2(0, 0));
    tempBedBox->setScale(0.87);
    //设置CheckBox是否可点击
    tempBedBox->setTouchEnabled(true);
    tempBedBox->addEventListener(CC_CALLBACK_2(MainScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    bkView->addChild(tempBedBox);
    boxVec->pushBack(tempBedBox);
    auto fixedBedBox=CheckBox::create("box_fixedBed_unselect.png","box_fixedBed_select.png");
    //设置CheckBox的位置
    fixedBedBox->setPosition(Vec2(0,918));
    fixedBedBox->setTag(6);
    fixedBedBox->setAnchorPoint(Vec2(0, 0));
    fixedBedBox->setScale(0.87);
    //设置CheckBox是否可点击
    fixedBedBox->setTouchEnabled(true);
    fixedBedBox->setSelected(true);
    fixedBedBox->addEventListener(CC_CALLBACK_2(MainScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    bkView->addChild(fixedBedBox);
    boxVec->pushBack(fixedBedBox);
    
    auto line1=Sprite::create("userInfo_line.png");
    line1->setPosition(Vec2(0, 915));
    line1->setAnchorPoint(Vec2(0, 0));
    line1->setScaleX(1.05);
    bkView->addChild(line1);
    
    auto job = Label::createWithSystemFont("上海长征医院","Arial",35,Size(visibleSize.width-40,50),TextHAlignment::LEFT,TextVAlignment::CENTER);
    job->setPosition(Vec2(20,850));
    job->setTextColor(Color4B(0, 0, 0, 255/2));
    job->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(job);
    
    auto line2=Sprite::create("userInfo_line.png");
    line2->setPosition(Vec2(0, 835));
    line2->setAnchorPoint(Vec2(0, 0));
    line2->setScaleX(1.05);
    bkView->addChild(line2);
    
}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

ScrollView* MainScene::createScrollV(int index){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setTag(502);
    scrollView->setPosition(Vec2(0,100));
    scrollView->setAnchorPoint(Vec2(0, 0));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);//方向
    scrollView->setScrollBarEnabled(true);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, 730));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 0, 255));//设置背景颜色
//data
    scrollView->setInnerContainerSize(Size(visibleSize.width, (int)(index/5)*155+20));//设置内容大小
    for (int i=0; i<index; i++) {
        Menu *menu=createRectButton(Vec2(27, scrollView->getInnerContainerSize().height-143), i);
        scrollView->addChild(menu);
    }
    return scrollView;
}

Menu*   MainScene::createRectButton(Vec2 point,int i){
    Size visibleSize=Director::getInstance()->getVisibleSize();
    rapidjson::Value& data = this->infoData["data"][i];
    auto menuItem  = MenuItemImage::create("bk_bed.png","bk_bed.png",CC_CALLBACK_1(MainScene::menuBedNumCallback, this));
    menuItem->setAnchorPoint(Vec2(0,0));
    menuItem->setPosition(Vec2(0,0));
    menuItem->setTag(i+100);
    menuItem->setScale(0.87);
    auto button = Menu::create();
    button->setAnchorPoint(Vec2(0,0));
    button->setPosition(point);
    button->addChild(menuItem);
    Size imageSize=menuItem->getContentSize()*0.87;
    int width=point.x+(imageSize.width+46)*i+imageSize.width;
            if (width<visibleSize.width) {
                button->setPosition(Vec2(point.x+(imageSize.width+46)*i, point.y));
            }else{
                button->setPosition(Vec2(point.x+(imageSize.width+46)*(i%5),point.y-((int)((width-point.x)/((imageSize.width+46)*5))*(imageSize.height+31))));
            }
    
    int colorType=2;
    if (data["status"].IsNull()) {
    }
  else  if(strcmp(data["status"].GetString(), "none")==0){
        colorType=1;
    }else   if(strcmp(data["status"].GetString(), "new")==0){
        colorType=2;
    }else   if(strcmp(data["status"].GetString(), "leave")==0){
        colorType=3;
    }else   if(strcmp(data["status"].GetString(), "surgery")==0||strcmp(data["status"].GetString(), "after")==0){
        colorType=4;
    }
    if (data["caseId"].IsNull()||strcmp(data["caseId"].GetString(), "0")==0  ) {//病床中没有病人
        colorType=1;
    }
    
    char strtest[500] = {0};
    sprintf(strtest,"bedNum%d.png",colorType);
    string numStr=strtest;
    auto num=Sprite::create(numStr);
    num->setPosition(Vec2(3, 30));
    num->setAnchorPoint(Vec2(0, 0));
    num->setScale(1.2);
    auto numLB = Label::createWithSystemFont(data["bedNo"].GetString(),"Arial",35,Size(num->getContentSize().width,num->getContentSize().width),TextHAlignment::CENTER,TextVAlignment::CENTER);
    numLB->setPosition(Vec2(0,0));
    numLB->setTextColor(Color4B(255, 255, 255, 255));
    numLB->setAnchorPoint(Vec2(0, 0));
    num->addChild(numLB);
    menuItem->addChild(num);
    return button;
}



//门诊
Layer* MainScene::createOutPatientLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    layer->setContentSize(visibleSize);
    layer->setPosition(Point(0, 0));
    layer->setAnchorPoint(Vec2(origin.x, origin.y));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    
    auto bkView=Sprite::create("bk_outpatient.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    layer->addChild(bkView);
    
    
    auto waitBtn=Button::create();
    waitBtn->loadTextures("btn_outpatient_content.png", "btn_outpatient_content.png");
    waitBtn->setPosition(Vec2(20, 849));
    waitBtn->setAnchorPoint(Vec2(0, 0));
    waitBtn->setScale(0.86);
    waitBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto chatScene=WaitChatScene::createScene();
            Director::getInstance()->pushScene(chatScene);
//候诊病人
        }
        default:
            break;
    }
    });
    bkView->addChild(waitBtn);
    auto waitLB=Label::createWithSystemFont("候诊病人","Arial",50,Size(300,100),TextHAlignment::LEFT,TextVAlignment::CENTER);
    waitLB->setPosition(Vec2(20,15));
    waitLB->setTextColor(Color4B(0, 0, 0, 255/3*2));
    waitLB->setAnchorPoint(Vec2(0, 0));
    waitBtn->addChild(waitLB);
    
    auto receiveBtn=Button::create();
    receiveBtn->loadTextures("btn_outpatient_content.png", "btn_outpatient_content.png");
    receiveBtn->setPosition(Vec2(20, 710));
    receiveBtn->setAnchorPoint(Vec2(0, 0));
    receiveBtn->setScale(0.86);
    receiveBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto chatScene=ReceiveChatScene::createScene();
            Director::getInstance()->pushScene(chatScene);
//接诊病人
        }
        default:
            break;
    }
    });
    bkView->addChild(receiveBtn);
    auto receiveLB=Label::createWithSystemFont("接诊病人","Arial",50,Size(300,100),TextHAlignment::LEFT,TextVAlignment::CENTER);
    receiveLB->setPosition(Vec2(20,15));
    receiveLB->setTextColor(Color4B(0, 0, 0, 255/3*2));
    receiveLB->setAnchorPoint(Vec2(0, 0));
    receiveBtn->addChild(receiveLB);
    
    return layer;
}
//日历
Layer* MainScene::createCalendarLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    layer->setContentSize(visibleSize);
    layer->setPosition(Point(0, 0));
    layer->setAnchorPoint(Vec2(origin.x, origin.y));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    
  /*  auto bkView=Sprite::create("bk_select_body.png");//bk_select_body.png
    bkView->setAnchorPoint(Vec2(0.5, 0.5));
    bkView->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    bkView->setContentSize(visibleSize);
    layer->addChild(bkView);
    auto titleLB = Label::createWithSystemFont("日历","Arial",42,Size(200,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
    titleLB->setPosition(Point(visibleSize.width/2,visibleSize.height-110));
    titleLB->setTextColor(Color4B(255, 255, 255, 255));//91, 144, 229, 255
    titleLB->setAnchorPoint(Vec2(0.5, 0));
    layer->addChild(titleLB);   */
    
    auto   webView = cocos2d::experimental::ui::WebView::create();
    webView->loadURL("http://calendar.looper.pro");
    webView->setContentSize(Size(visibleSize.width, visibleSize.height-100));
    webView->setAnchorPoint(Vec2(0,0));
    webView->setPosition(Vec2(0,100));
    webView->setScalesPageToFit(false);
    layer->addChild(webView);
    webView->setOnDidFinishLoading([](cocos2d::experimental::ui::WebView *sender, const std::string &url){
        //        cocos2d::experimental::ui::WebView::ccWebViewCallback content=sender->getOnJSCallback();
        log("%s",url.c_str());
    });
    
    return layer;
}
//我的
Layer* MainScene::createSickInfoLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    layer->setContentSize(visibleSize);
    layer->setPosition(Point(0, 0));
    layer->setAnchorPoint(Vec2(origin.x, origin.y));
    auto callback = [](Touch * ,Event *){
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    
    auto bkView=Sprite::create("bk_sickInfo.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    layer->addChild(bkView);
    
    auto caseBtn=Button::create();
    caseBtn->loadTextures("btn_sickInfo_case.png", "btn_sickInfo_case.png");
    caseBtn->setPosition(Vec2(30, 840));
    caseBtn->setAnchorPoint(Vec2(0, 0));
    caseBtn->setScale(0.9);
    caseBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED: {
            auto caseScene= CaseSearchScene::createScene();
            Director::getInstance()->pushScene(caseScene);
        }
        default:
            break;
    }
    });
    bkView->addChild(caseBtn);
    
    auto groupBtn=Button::create();
    groupBtn->loadTextures("btn_sickInfo_group.png", "btn_sickInfo_group.png");
    groupBtn->setPosition(Vec2(30, 690));
    groupBtn->setAnchorPoint(Vec2(0, 0));
    groupBtn->setScale(0.9);
    groupBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            if (UserDefault::getInstance()->getIntegerForKey("isleader")) {
            auto groupScene= GroupLeaderScene::createScene();
            Director::getInstance()->pushScene(groupScene);
            }else{
                auto groupScene= GroupMemberScene::createScene();
                Director::getInstance()->pushScene(groupScene);
            }
        }
        default:
            break;
    }
    });
    bkView->addChild(groupBtn);
    
    auto messageBtn=Button::create();
    messageBtn->loadTextures("btn_sickInfo_message.png", "btn_sickInfo_message.png");
    messageBtn->setPosition(Vec2(30, 540));
    messageBtn->setAnchorPoint(Vec2(0, 0));
    messageBtn->setScale(0.9);
    messageBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto messageSC=MessageNotificationScene::createScene();
            Director::getInstance()->pushScene(messageSC);
        }
        default:
            break;
    }
    });
    bkView->addChild(messageBtn);
    
    auto accountBtn=Button::create();
    accountBtn->loadTextures("btn_sickInfo_account.png", "btn_sickInfo_account.png");
    accountBtn->setPosition(Vec2(30, 390));
    accountBtn->setAnchorPoint(Vec2(0, 0));
    accountBtn->setScale(0.9);
    accountBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto accountScene= AccountManageScene::createScene();
            Director::getInstance()->pushScene(accountScene);
        }
        default:
            break;
    }
    });
    bkView->addChild(accountBtn);
    
    auto sponsorBtn=Button::create();
    sponsorBtn->loadTextures("btn_sickInfo_addSponsor.png", "btn_sickInfo_addSponsor.png");
    sponsorBtn->setPosition(Vec2(30, 240));
    sponsorBtn->setAnchorPoint(Vec2(0, 0));
    sponsorBtn->setScale(0.9);
    sponsorBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            Layer *layer= createSponsorLayer();
            layer->setTag(1000);
            this->addChild(layer);
        }
        default:
            break;
    }
    });
    bkView->addChild(sponsorBtn);
    return layer;
}
Layer* MainScene::createSponsorLayer(){
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
    auto contentV = Sprite::create("bk_sickInfo_writeName.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(57,454));
    contentV->setContentSize(Size(526,300));
    layer->addChild(contentV);
    
    //必须写在textfield之前才能释放textfield响应者
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_register_delete.png", "btn_register_delete.png");
    deleteBtn->setPosition(Vec2(465, 240));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            this->removeChildByTag(1000);
        default:
            break;
    }
    });
    contentV->addChild(deleteBtn);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_register_sure.png", "btn_register_sure.png");
    sureBtn->setPosition(Vec2(163, 15));
    sureBtn->setAnchorPoint(Vec2(0,0));
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            Layer *codeLayer= createSQCodeLayer();
            codeLayer->setTag(1001);
            this->addChild(codeLayer);
            this->removeChildByTag(1000);
        }
        default:
            break;
    }
    });
    contentV->addChild(sureBtn);
    
     auto textFieldCase = EditBox::create(Size(330,50), Scale9Sprite::create("alpha.png"));
    textFieldCase->setTextHorizontalAlignment(TextHAlignment::CENTER);
    textFieldCase->setAnchorPoint(Vec2(0, 0));
    textFieldCase->setPosition(Vec2(100,123));//264
    textFieldCase->setFontName("Arial");
    textFieldCase->setFontSize(40);
    textFieldCase->setPlaceholderFontSize(40);
    textFieldCase->setFontColor(Color3B::BLACK);
    textFieldCase->setPlaceHolder("        在此填写：");
    textFieldCase->setPlaceholderFontColor(Color3B::GRAY);
    textFieldCase->setReturnType(EditBox::KeyboardReturnType::DONE);
    textFieldCase->setMaxLength(20);
    textFieldCase->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);//可以输入任何，但是不包括换行
    //    userName->setDelegate(this);
    contentV->addChild(textFieldCase);
    
    auto lineSp=Sprite::create("userInfo_line.png");
    lineSp->setPosition(Vec2(150, 120));
    lineSp->setAnchorPoint(Vec2(0, 0));
    lineSp->setContentSize(Size(226, 1));
    contentV->addChild(lineSp);
    
    return layer;
}
Layer* MainScene::createSQCodeLayer(){
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
    auto contentV = Sprite::create("bk_sickInfo_QRCode.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(57,344));
    contentV->setContentSize(Size(526,410));
    layer->addChild(contentV);
    
    //必须写在textfield之前才能释放textfield响应者
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_register_delete.png", "btn_register_delete.png");
    deleteBtn->setPosition(Vec2(465, 350));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            this->removeChildByTag(1001);
        default:
            break;
    }
    });
    contentV->addChild(deleteBtn);
    
    auto sendBtn=Button::create();
    sendBtn->loadTextures("btn_sickInfo_send.png", "btn_sickInfo_send.png");
    sendBtn->setPosition(Vec2(38, 15));
    sendBtn->setAnchorPoint(Vec2(0,0));
    sendBtn->setScale(0.87);
    sendBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            this->removeChildByTag(1001);
        default:
            break;
    }
    });
    contentV->addChild(sendBtn);
    
    auto saveBtn=Button::create();
    saveBtn->loadTextures("btn_sickInfo_save.png", "btn_sickInfo_save.png");
    saveBtn->setPosition(Vec2(302, 15));
    saveBtn->setAnchorPoint(Vec2(0,0));
    saveBtn->setScale(0.87);
    saveBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            this->removeChildByTag(1001);
        default:
            break;
    }
    });
    contentV->addChild(saveBtn);
    
//加入二维码
    DrawNode *SQCode=createSQCodeImage("www.baidu.com",Vec2(164, 100));
    contentV->addChild(SQCode);
    return layer;
}

cocos2d::DrawNode * MainScene::createSQCodeImage(std::string content,Vec2 origin){
    char* contentStr=(char*)content.c_str();
    bool bRet = m_QREncode.EncodeData(0, 0, 1, -1, contentStr);
    if(bRet)
    {
        int nSize = 5;
        int originalSize = m_QREncode.m_nSymbleSize + (QR_MARGIN * 2);
        CCDrawNode *pQRNode = CCDrawNode::create();
        
        CCPoint pt[6];
        ccColor4F color;
        
        pt[0] = ccp(0, 0);
        pt[1] = ccp((m_QREncode.m_nSymbleSize + QR_MARGIN * 2)*nSize, (m_QREncode.m_nSymbleSize + QR_MARGIN * 2)*nSize);
        pt[2] = ccp((m_QREncode.m_nSymbleSize + QR_MARGIN * 2)*nSize, 0);
        
        pt[3] = pt[0];
        pt[4] = ccp(0, (m_QREncode.m_nSymbleSize + QR_MARGIN * 2)*nSize);
        pt[5] = pt[1];
        color = ccc4f(1, 1, 1, 1);
        pQRNode->drawPolygon(pt, 6, color, 0, color);
        
        for (int i = 0; i < m_QREncode.m_nSymbleSize; ++i)
        {
            for (int j = 0; j < m_QREncode.m_nSymbleSize; ++j)
            {
                pt[0] = ccp((i + QR_MARGIN)*nSize, (j + QR_MARGIN)*nSize);
                pt[1] = ccp(((i + QR_MARGIN) + 1)*nSize, ((j + QR_MARGIN) + 1)*nSize);
                pt[2] = ccp(((i + QR_MARGIN) + 1)*nSize, ((j + QR_MARGIN) + 0)*nSize);
                
                pt[3] = pt[0];
                pt[4] = ccp(((i + QR_MARGIN) + 0)*nSize, ((j + QR_MARGIN) + 1)*nSize);
                pt[5] = pt[1];
                if (m_QREncode.m_byModuleData[i][j] == 1)
                {
                    color = ccc4f(0, 0, 0, 1);
                }
                else
                {
                    color = ccc4f(1, 1, 1, 1);
                }
                pQRNode->drawPolygon(pt, 6, color, 0, color);
            }
        }
//        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//        pQRNode->setPosition(ccp((winSize.width - nSize*m_QREncode.m_nSymbleSize) / 2, winSize.height - (winSize.height - nSize*m_QREncode.m_nSymbleSize) / 2));
        pQRNode->setAnchorPoint(Vec2(0, 0));
        pQRNode->setPosition(origin);
        pQRNode->setScale(1.70);
//        pQRNode->setScaleY(-1);
        return pQRNode;
}
}



void MainScene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
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

//实现CheckBox回调函数
void MainScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    log("checkBox tag:%d",tag);
    if (type==cocos2d::ui::CheckBox::EventType::SELECTED) {
        if (tag==5||tag==6) {
//临时病床和固定病床
            for (int i=0; i<2; i++) {
                CheckBox *box=boxVec->at(i);
                if (box->getTag()!=tag) {
                    box->setSelected(false);
                }
            }
        }else if(tag>=0&&tag<=4){
//底部切换按钮的高亮
            for (int i=0; i<4; i++) {
                if (i!=tag) {
                    CheckBox * checkBox=(CheckBox*)this->getChildByTag(i);
                    checkBox->setSelected(false);
                }
            }
        }
    }
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
            if (tag==5||tag==6) {
//当tag为5时，表示点击了临时床位
                isTempBed=6-tag;
                pushDataToNetWork();
            }else if(tag>=0&&tag<=4){
                //切换页面
                multLayer->switchTo(tag);
            }
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            if (tag==5||tag==6) {
               item->setSelected(true);
            }
            log("UNSELECTED!");
            break;
        default:
            break;
    }
}

void MainScene::menuBedNumCallback(Ref* pSender)
{
    MenuItem* item = (MenuItem*)pSender;
    int tag= item->getTag();
    log("item tag%d,size %d",tag,infoData["data"].Size());
      rapidjson::Value& data = infoData["data"][tag-100];
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    infoData.Accept(writer);
    CCLOG("%s", buffer.GetString());
    if (data["caseId"].IsNull()||strcmp(data["caseId"].GetString(), "0")==0  ) {
#pragma-没有绑定病人，需要加入病人数据，跳转不同的界面
     auto scene=(UpdateBedScene*)UpdateBedScene::createScene();
        scene->bedInfoData.SetObject();
        rapidjson::Document::AllocatorType& allocator = scene->bedInfoData.GetAllocator();
        scene->bedInfoData.AddMember("data", data, allocator);
     Director::getInstance()->pushScene(scene);
    }else{
    auto sickroomSC=(SickRoomScene*)SickRoomScene::createScene();
    sickroomSC->bedNum=atoi(data["bedNo"].GetString());
    UserDefault::getInstance()->setStringForKey("caseId", data["caseId"].GetString());
    UserDefault::getInstance()->setStringForKey("patientId", data["patientId"].GetString());
    Director::getInstance()->pushScene(sickroomSC);
    }
    
}

#pragma-用于加载网络数据
void MainScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    //当type为2时，删除成员
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/getBeds?doctorId=%s",UserDefault::getInstance()->getStringForKey("id").c_str());
    string memberURL=memberUrl;
    netManeger->sendMessage(memberURL,CC_CALLBACK_2(MainScene::onHttpRequestCompleted, this),nullptr);
}

void MainScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
            rapidjson::Value& object = infoData["data"];
            
  /*          for (int i=0; i<object.Size(); i++) {
                 log("size:%d",infoData["data"].Size());
                if (isTempBed==0) {//固定床位
                    if (!object[i]["patientName"].IsNull()) {
                        log("name:%s",object[i]["patientName"].GetString());}
                    if (strcmp(object[i]["type"].GetString(),"temporary")==0) {
                        infoData["data"].Erase(infoData["data"].Begin()+i);i=0;
                    }
                }else{//临时床位
                    if (strcmp(object[i]["type"].GetString(),"temporary")!=0) {
                        infoData["data"].Erase(infoData["data"].Begin()+i);i=0;
                    }
                }
            }  */
 //获取临时床位和固定床位的数据
            infoData.SetObject();
            rapidjson::Document::AllocatorType& allocator = infoData.GetAllocator();
            rapidjson::Value array(rapidjson::kArrayType);
            for (int i=0; i<object.Size(); i++) {
                if (strcmp(object[i]["type"].GetString(),"temporary")==0) {//临时床位
                    if (isTempBed==1) {
                        array.PushBack(object[i], allocator);}
                }else {//固定床位
                     if (isTempBed==0) {
                array.PushBack(object[i], allocator);
                     }
                }
            }
            infoData.AddMember("data", array, allocator);
            
            log("size:%d",infoData["data"].Size());
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            infoData.Accept(writer);
            CCLOG("%s", buffer.GetString());
            
            auto backV=caseLayer->getChildByTag(501);
            backV->removeChildByTag(502);//删除scrollView
            ScrollView *scrollV=createScrollV(infoData["data"].Size());
            backV->addChild(scrollV);
        }
    }
}





