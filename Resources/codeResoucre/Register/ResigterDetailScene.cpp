//
//  ResigterDetailScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/13.
//

#include "ResigterDetailScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>

using namespace rapidjson; // 命名空间
#include "NetWrokMangerData.hpp"

using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *RegisterDetailScene::createScene(){
    return RegisterDetailScene::create();
}

//data

bool RegisterDetailScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    bkView=Sprite::create("bk_registerDetail.png");
    bkView->setPosition(Vec2(0, 0));
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(Size(visibleSize.width, visibleSize.height));
    this->addChild(bkView);
    
    auto backBtn=Button::create();
    backBtn->loadTextures("btn_register_return.png", "btn_register_return.png");
    backBtn->setPosition(Vec2(80, visibleSize.height-90));
    backBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            Director::getInstance()->popScene();
        default:
            break;
    }
    });
    this->addChild(backBtn);
    
    auto headBtn=Button::create();
    headBtn->loadTextures("btn_update_head.png", "btn_update_head.png");
    headBtn->setPosition(Vec2(310, visibleSize.height-220));
    headBtn->setScale(0.8);
    headBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            Layer *layer= createAlbumLayer();
            layer->setTag(200);
            this->addChild(layer);
        }
        default:
            break;
    }
    });
    this->addChild(headBtn);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_perfect_sure.png", "btn_perfect_sure.png");
    sureBtn->setPosition(Vec2(visibleSize.width/2-120, 60));
    sureBtn->setAnchorPoint(Vec2(0, 0));
    sureBtn->setScale(0.70);
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            //在这里请求接口
            std::string pass=textfieldPass->getText();
            if (pass.size()<6) {
                auto judgeV = Label::createWithSystemFont("您设置的密码位数少于6位","Arial",35,Size(visibleSize.width,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
                judgeV->setPosition(Vec2(visibleSize.width+300, 568));
                judgeV->setTextColor(Color4B(91, 144, 229, 255));
                judgeV->setAnchorPoint(Vec2(0.5, 0));
                this->addChild(judgeV,10);
                judgeV->runAction(Sequence::create(DelayTime::create(0.5),FadeOut::create(0.5), NULL));
            }else if(strcmp(textfieldPass->getText(), textfieldSurePass->getText())){
                auto judgeV = Label::createWithSystemFont("您输入的密码前后不一样","Arial",35,Size(visibleSize.width,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
                judgeV->setPosition(Vec2(visibleSize.width+300, 568));
                judgeV->setTextColor(Color4B(91, 144, 229, 255));
                judgeV->setAnchorPoint(Vec2(0.5, 0));
                this->addChild(judgeV,10);
                judgeV->runAction(Sequence::create(DelayTime::create(0.5),FadeOut::create(0.5), NULL));
            }else{
                pushDataToNetWork(textfieldName->getText(),textfieldPass->getText(),textfieldName->getText(),sexLB,"",textfieldTel->getText(),textfieldCaseTel2->getText(),"",textfieldCaseAddress->getText(),"","");
            }
        }
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    
    auto scanBtn=Button::create();
    scanBtn->loadTextures("alpha.png", "alpha.png");
    scanBtn->setTitleText("点击扫描");
    scanBtn->setTitleColor(Color3B(51, 145, 233/2));
    scanBtn->setTitleFontSize(33);
    scanBtn->setPosition(Vec2(visibleSize.width-90, 215));
    scanBtn->setAnchorPoint(Vec2(1, 0));
    scanBtn->setScale9Enabled(true);
    scanBtn->setContentSize(Size(100, 40));
    scanBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            //扫描二维码
        }
        default:
            break;
    }
    });
    bkView->addChild(scanBtn);
    
    return true;
}

void RegisterDetailScene::onEnter(){
    Scene::onEnter();
    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> writer(buffer);
    userData["data"].Accept(writer);
    CCLOG("%s", buffer.GetString());
    
    rapidjson::Value&data=userData["data"][0];
    string name=""; if(!data["name"].IsNull()){name=data["name"].GetString();}
     string phone=""; if(!data["phone"].IsNull()){phone=data["phone"].GetString();}
     string phone1=""; if(!data["phone1"].IsNull()){phone1=data["phone1"].GetString();}
     string address=""; if(!data["address"].IsNull()){address=data["address"].GetString();}
    string sex="男"; if(!data["sex"].IsNull()){  if(strcmp(data["sex"].GetString(), "F")==0)sex="女";}
    textfieldName=createBasicData(bkView, Vec2(59, 768), "姓名：", "未填写");
    textfieldPass=createBasicData(bkView, Vec2(59, 688), "密码：", "未填写");
    textfieldPass->setInputFlag(cocos2d::ui::EditBox::InputFlag::PASSWORD);
    textfieldSurePass=createBasicData(bkView, Vec2(59, 608), "确认密码：", "未填写");
    textfieldSurePass->setInputFlag(cocos2d::ui::EditBox::InputFlag::PASSWORD);
    textfieldTel=createBasicData(bkView, Vec2(59, 448), "联系电话：", "未填写");
    textfieldTel->setInputMode(cocos2d::ui::EditBox::InputMode::PHONE_NUMBER);
    textfieldCaseTel2=createBasicData(bkView, Vec2(59, 368), "手机：", "未填写");
    textfieldCaseTel2->setInputMode(cocos2d::ui::EditBox::InputMode::PHONE_NUMBER);
    textfieldCaseAddress=createBasicData(bkView, Vec2(59, 288), "家庭住址：", "未填写");
    textfieldCaseRefer=createBasicData(bkView, Vec2(59, 208), "推荐人：", "");
    
    auto Sex = Label::createWithSystemFont("性别","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    Sex->setPosition(Vec2(59, 528));
    Sex->setTextColor(Color4B(91, 144, 229, 255));
    Sex->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(Sex);
    auto Star = Label::createWithSystemFont("*","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    Star->setPosition(30,523);
    Star->setTextColor(Color4B(205, 133, 147, 255));
    Star->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(Star);
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(51,522));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.85);
    bkView->addChild(lineV);
    
    auto manCheckBox = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    manCheckBox->setPosition(Vec2(340, 530));
    manCheckBox->setAnchorPoint(Vec2(0, 0));
    manCheckBox->setTag(50);
    //设置CheckBox是否可点击
    manCheckBox->setTouchEnabled(true);
    //获取checkbox的选中状态
    //selected 值为true 时 checkbox 为选中状态, 为false 则不会
    if (strcmp(sex.c_str(), "男")==0) {
        manCheckBox->setSelectedState(true);sexLB="M";
    }
    manCheckBox->addEventListener(CC_CALLBACK_2(RegisterDetailScene::checkBoxCallback,this));
    addChild(manCheckBox);
    auto manLB= Label::createWithSystemFont("男","Arial",35,Size(50,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    manLB->setPosition(Vec2(380, 530));
    manLB->setTextColor(Color4B::GRAY);
    manLB->setAnchorPoint(Vec2(0, 0));
    this->addChild(manLB);
    
    auto womanCheckBox = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    womanCheckBox->setPosition(Vec2(460, 530));
    womanCheckBox->setTag(51);
    womanCheckBox->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    womanCheckBox->setTouchEnabled(true);
    if (strcmp(sex.c_str(), "女")==0) {
        manCheckBox->setSelectedState(true);sexLB="F";
    }
    womanCheckBox->addEventListener(CC_CALLBACK_2(RegisterDetailScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(womanCheckBox);
    auto womanLB= Label::createWithSystemFont("女","Arial",35,Size(50,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    womanLB->setPosition(Vec2(500, 530));
    womanLB->setTextColor(Color4B::GRAY);
    womanLB->setAnchorPoint(Vec2(0, 0));
    this->addChild(womanLB);
}


EditBox*  RegisterDetailScene::createBasicData(Sprite* bkView,Vec2 point,string name1,string name2){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto userName = Label::createWithSystemFont(name1,"Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userName->setPosition(point);
    userName->setTextColor(Color4B(91, 144, 229, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    auto Star = Label::createWithSystemFont("*","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    Star->setPosition(30,point.y-5);
    Star->setTextColor(Color4B(205, 133, 147, 255));
    Star->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(Star);
    
    auto   textFieldName = EditBox::create(Size(360,50), Scale9Sprite::create("alpha.png"));
    if (strcmp(name2.c_str(), "")!=0) {
    textFieldName->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFieldName->setAnchorPoint(Vec2(1, 0));
    textFieldName->setPosition(Vec2(visibleSize.width-70,point.y));
    textFieldName->setFontName("Arial");
    textFieldName->setFontSize(33);
    textFieldName->setPlaceholderFontSize(33);
    textFieldName->setFontColor(Color3B::BLACK);
    string placeHolder="                                      ";
    placeHolder.append(name2);
    textFieldName->setPlaceHolder(placeHolder.c_str());
    textFieldName->setPlaceholderFontColor(Color3B(240, 240, 240));
    textFieldName->setReturnType(EditBox::KeyboardReturnType::DONE);
    textFieldName->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);//可以输入任何，但是不包括换行
    addChild(textFieldName);
    }
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(51, point.y-6));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.85);
    bkView->addChild(lineV);
    
    return textFieldName;
}



//实现CheckBox回调函数
void RegisterDetailScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    MenuItem* item = (MenuItem*)ref;
    int tag= item->getTag();
    CheckBox *checkBox;
    if (tag==50) {
        checkBox=(CheckBox*)this->getChildByTag(51);
    }else{
        checkBox=(CheckBox*)this->getChildByTag(50);
    }
    //     bool selected  = checkBox->getSelectedState();
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            if (tag==50) {sexLB="M";}     else{sexLB="F";}
            log("SELECTED!");
            checkBox->setSelected(false);
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED!");
            break;
        default:
            break;
    }
}


Layer* RegisterDetailScene::createAlbumLayer(){
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
    auto contentV = Sprite::create("update_album.png");
    contentV->setAnchorPoint(Vec2(0,1));
    contentV->setPosition(Vec2(57,visibleSize.height-300));
    contentV->setContentSize(Size(508,349));
    layer->addChild(contentV);
    
    auto cameraBtn=Button::create();
    cameraBtn->setScale9Enabled(true);
    cameraBtn->setPosition(Vec2(0, 88));
    cameraBtn->setAnchorPoint(Vec2(0,0));
    cameraBtn->setContentSize(Size(contentV->getContentSize().width, 80));
    cameraBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            break;
    }
    });
    contentV->addChild(cameraBtn);
    
    auto albumBtn=Button::create();
    albumBtn->setScale9Enabled(true);
    albumBtn->setPosition(Vec2(0, 168));
    albumBtn->setAnchorPoint(Vec2(0,0));
    albumBtn->setContentSize(Size(contentV->getContentSize().width, 80));
    albumBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            break;
    }
    });
    contentV->addChild(albumBtn);
    
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_message_cancel.png", "btn_message_cancel.png");
    deleteBtn->setPosition(Vec2(111, 15));
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
    
    return layer;
}


#pragma-用于加载网络数据

void RegisterDetailScene::pushDataToNetWork(string username,string passwd,string name,string sex,string age,string phone,string phone1,string idCardNo,string address,string headUrl,string caseNo){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char memberUrl[1000]={0};
sprintf(memberUrl,"userId=%s&passwd=%s&name=%s&sex=%s&phone=%s&phone1=%s&address=%s",username.c_str(),passwd.c_str(),name.c_str(),sex.c_str(),phone.c_str(),phone1.c_str(),address.c_str());
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/updatePersonalInfo";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(RegisterDetailScene::onHttpRequestCompleted, this),url);
}

void RegisterDetailScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
    if(this->loginData.HasMember("status")&&loginData["status"].GetInt()==0){
        log("注册成功");
        Director::getInstance()->popToRootScene();
    }else{
        Size visibleSize=Director::getInstance()->getVisibleSize();
        auto judgeV = Label::createWithSystemFont("用户名重复","Arial",35,Size(visibleSize.width,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
        judgeV->setPosition(Vec2(visibleSize.width/2+100, 268));
        judgeV->setTextColor(Color4B(91, 144, 229, 255));
        judgeV->setAnchorPoint(Vec2(0, 0));
        this->addChild(judgeV);
        judgeV->runAction(Sequence::create(DelayTime::create(0.5),FadeOut::create(0.5), NULL));
    }
    
}



