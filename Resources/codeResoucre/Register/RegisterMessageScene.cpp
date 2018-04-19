
#include "RegisterMessageScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>

using namespace rapidjson; // 命名空间
#include "NetWrokMangerData.hpp"

using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *RegisterMessageScene::createScene(){
    return RegisterMessageScene::create();
}

//data
bool RegisterMessageScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    bkView=Sprite::create("bk_register_message.png");
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
    
    textFieldUser = EditBox::create(Size(360,50), Scale9Sprite::create("alpha.png"));
    textFieldUser->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFieldUser->setAnchorPoint(Vec2(1, 0));
    textFieldUser->setPosition(Vec2(560,795));
    textFieldUser->setFontName("Arial");
    textFieldUser->setFontSize(33);
    textFieldUser->setPlaceholderFontSize(33);
    textFieldUser->setFontColor(Color3B::BLACK);
    textFieldUser->setPlaceHolder("                                      未填写");
    textFieldUser->setPlaceholderFontColor(Color3B(240, 240, 240));
    textFieldUser->setReturnType(EditBox::KeyboardReturnType::DONE);
    textFieldUser->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);//可以输入任何，但是不包括换行
    addChild(textFieldUser);
    
    textFieldPass = EditBox::create(Size(360,50), Scale9Sprite::create("alpha.png"));
    textFieldPass->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFieldPass->setAnchorPoint(Vec2(1, 0));
    textFieldPass->setPosition(Vec2(560,710));
    textFieldPass->setFontName("Arial");
    textFieldPass->setFontSize(33);
    textFieldPass->setPlaceholderFontSize(33);
    textFieldPass->setFontColor(Color3B::BLACK);
    textFieldPass->setPlaceHolder("                                      未填写");
    textFieldPass->setPlaceholderFontColor(Color3B(240, 240, 240));
    textFieldPass->setReturnType(EditBox::KeyboardReturnType::DONE);
    textFieldPass->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);//可以输入任何，但是不包括换行
    addChild(textFieldPass);
    
    textFieldSurePass = EditBox::create(Size(350,50), Scale9Sprite::create("alpha.png"));
    textFieldSurePass->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFieldSurePass->setAnchorPoint(Vec2(1, 0));
    textFieldSurePass->setPosition(Vec2(560,627));
    textFieldSurePass->setFontName("Arial");
    textFieldSurePass->setFontSize(33);
    textFieldSurePass->setPlaceholderFontSize(33);
    textFieldSurePass->setFontColor(Color3B::BLACK);
    textFieldSurePass->setPlaceHolder("                                      未填写");
    textFieldSurePass->setPlaceholderFontColor(Color3B(240, 240, 240));
    textFieldSurePass->setReturnType(EditBox::KeyboardReturnType::DONE);
    textFieldSurePass->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);//可以输入任何，但是不包括换行
    addChild(textFieldSurePass);
    
    textFieldName = EditBox::create(Size(360,50), Scale9Sprite::create("alpha.png"));
    textFieldName->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFieldName->setAnchorPoint(Vec2(1, 0));
    textFieldName->setPosition(Vec2(560,545));
    textFieldName->setFontName("Arial");
    textFieldName->setFontSize(33);
    textFieldName->setPlaceholderFontSize(33);
    textFieldName->setFontColor(Color3B::BLACK);
    textFieldName->setPlaceHolder("                                      未填写");
    textFieldName->setPlaceholderFontColor(Color3B(240, 240, 240));
    textFieldName->setReturnType(EditBox::KeyboardReturnType::DONE);
    textFieldName->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);//可以输入任何，但是不包括换行
    addChild(textFieldName);
    
    textFieldAge = EditBox::create(Size(360,50), Scale9Sprite::create("alpha.png"));
    textFieldAge->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFieldAge->setAnchorPoint(Vec2(1, 0));
    textFieldAge->setPosition(Vec2(560,380));
    textFieldAge->setFontName("Arial");
    textFieldAge->setFontSize(33);
    textFieldAge->setPlaceholderFontSize(33);
    textFieldAge->setFontColor(Color3B::BLACK);
    textFieldAge->setPlaceHolder("                                      未填写");
    textFieldAge->setPlaceholderFontColor(Color3B(240, 240, 240));
    textFieldAge->setReturnType(EditBox::KeyboardReturnType::DONE);
    textFieldAge->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);//可以输入任何，但是不包括换行
    addChild(textFieldAge);
    
    textFieldNum = EditBox::create(Size(350,50), Scale9Sprite::create("alpha.png"));
    textFieldNum->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFieldNum->setAnchorPoint(Vec2(1, 0));
    textFieldNum->setPosition(Vec2(560,300));
    textFieldNum->setFontName("Arial");
    textFieldNum->setFontSize(33);
    textFieldNum->setPlaceholderFontSize(33);
    textFieldNum->setFontColor(Color3B::BLACK);
    textFieldNum->setPlaceHolder("                                      未填写");
    textFieldNum->setPlaceholderFontColor(Color3B(240, 240, 240));
    textFieldNum->setReturnType(EditBox::KeyboardReturnType::DONE);
    textFieldNum->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);//
    addChild(textFieldNum);
    
    textFieldCard = EditBox::create(Size(350,50), Scale9Sprite::create("alpha.png"));
    textFieldCard->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFieldCard->setAnchorPoint(Vec2(1, 0));
    textFieldCard->setPosition(Vec2(560,220));
    textFieldCard->setFontName("Arial");
    textFieldCard->setFontSize(33);
    textFieldCard->setPlaceholderFontSize(33);
    textFieldCard->setFontColor(Color3B::BLACK);
    textFieldCard->setPlaceHolder("                                      未填写");
    textFieldCard->setPlaceholderFontColor(Color3B(240, 240, 240));
    textFieldCard->setReturnType(EditBox::KeyboardReturnType::DONE);
    textFieldCard->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);//
    addChild(textFieldCard);
    
    auto manCheckBox = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    manCheckBox->setPosition(Vec2(340, 470));
    manCheckBox->setAnchorPoint(Vec2(0, 0));
    manCheckBox->setTag(50);
    //设置CheckBox是否可点击
    manCheckBox->setTouchEnabled(true);
    //获取checkbox的选中状态
    //selected 值为true 时 checkbox 为选中状态, 为false 则不会
    auto bool selected  = manCheckBox->getSelectedState();
    manCheckBox->addEventListener(CC_CALLBACK_2(RegisterMessageScene::checkBoxCallback,this));
    addChild(manCheckBox);
    auto manLB= Label::createWithSystemFont("男","Arial",35,Size(50,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    manLB->setPosition(Vec2(380, 470));
    manLB->setTextColor(Color4B::GRAY);
    manLB->setAnchorPoint(Vec2(0, 0));
    this->addChild(manLB);
    
    auto womanCheckBox = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    womanCheckBox->setPosition(Vec2(460, 470));
    womanCheckBox->setTag(51);
    womanCheckBox->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    womanCheckBox->setTouchEnabled(true);
     womanCheckBox->addEventListener(CC_CALLBACK_2(RegisterMessageScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(womanCheckBox);
    auto womanLB= Label::createWithSystemFont("女","Arial",35,Size(50,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    womanLB->setPosition(Vec2(500, 470));
    womanLB->setTextColor(Color4B::GRAY);
    womanLB->setAnchorPoint(Vec2(0, 0));
    this->addChild(womanLB);
    

        auto referrer = Label::createWithSystemFont("推荐人","Arial",32,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        referrer->setPosition(Vec2(80, 140));
        referrer->setTextColor(Color4B(51, 145, 233, 255));
        referrer->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(referrer);
        
        auto lineV=Sprite::create("userInfo_line.png");
        lineV->setPosition(Vec2(70, 140-6));
        lineV->setAnchorPoint(Vec2(0, 0));
        lineV->setScaleX(0.78);
        bkView->addChild(lineV);
    
    auto scanBtn=Button::create();
    scanBtn->loadTextures("alpha.png", "alpha.png");
    scanBtn->setTitleText("点击扫描");
    scanBtn->setTitleColor(Color3B(51, 145, 233/2));
    scanBtn->setTitleFontSize(33);
    scanBtn->setPosition(Vec2(visibleSize.width-90, 150));
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
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_perfect_sure.png", "btn_perfect_sure.png");
    sureBtn->setPosition(Vec2(visibleSize.width/2-115, 50));
    sureBtn->setAnchorPoint(Vec2(0, 0));
    sureBtn->setScale(0.70);
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            //在这里请求接口
            string pass=textFieldPass->getText();
            string surePass=textFieldSurePass->getText();
            if (pass.size()<6) {
                auto judgeV = Label::createWithSystemFont("您设置的密码位数少于6位","Arial",35,Size(visibleSize.width,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
                judgeV->setPosition(Vec2(visibleSize.width/2, 568));
                judgeV->setTextColor(Color4B(91, 144, 229, 255));
                judgeV->setAnchorPoint(Vec2(0.5, 0));
                this->addChild(judgeV,10);
                judgeV->runAction(Sequence::create(DelayTime::create(0.5),FadeOut::create(0.5), NULL));
            }else if(strcmp(pass.c_str(), surePass.c_str())){
                auto judgeV = Label::createWithSystemFont("您输入的密码前后不一样","Arial",35,Size(visibleSize.width,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
                judgeV->setPosition(Vec2(visibleSize.width/2, 568));
                judgeV->setTextColor(Color4B(91, 144, 229, 255));
                judgeV->setAnchorPoint(Vec2(0.5, 0));
                this->addChild(judgeV,10);
                judgeV->runAction(Sequence::create(DelayTime::create(0.5),FadeOut::create(0.5), NULL));
            }else{
                    pushDataToNetWork(textFieldUser->getText(),textFieldSurePass->getText(),textFieldName->getText(),sex,textFieldAge->getText(),textFieldNum->getText(),"",textFieldCard->getText(),"","","");
            }
        }
        default:
            break;
    }
    });
    this->addChild(sureBtn);
    
    getTimeForSystem();
    return true;
}



//实现CheckBox回调函数
void RegisterMessageScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
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
            log("SELECTED!");
            if (tag==50) {sex="M";}else{sex="F";}
            checkBox->setSelected(false);
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED!");
            break;
        default:
            break;
    }
}


Layer* RegisterMessageScene::createAlbumLayer(){
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
std::string RegisterMessageScene::getTimeForSystem(){
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
void RegisterMessageScene::pushDataToNetWork(string username,string passwd,string name,string sex,string age,string phone,string phone1,string idCardNo,string address,string headUrl,string caseNo){
     NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char memberUrl[1000]={0};
sprintf(memberUrl,"userId=%s&passwd=%s&name=%s&sex=%s&number=%s&phone=%s&idCardNo=%s&caseNo=%s",username.c_str(),passwd.c_str(),name.c_str(),sex.c_str(),age.c_str(),phone.c_str(),idCardNo.c_str(),getTimeForSystem().c_str());
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/createUser";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(RegisterMessageScene::onHttpRequestCompleted, this),url);
}

void RegisterMessageScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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




/*
 auto man=Sprite::create("message_select_man.png");
 man->setPosition(Vec2(350, 470));
 man->setAnchorPoint(Vec2(0, 0));
 this->addChild(man);
 
 auto manBtn=Button::create();
 manBtn->loadTextures("select_sure.png", "select_sure.png");
 manBtn->setPosition(Vec2(380, 500));
 manBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
 case ui::Widget::TouchEventType::BEGAN: break;
 case ui::Widget::TouchEventType::ENDED:
 
 default:
 break;
 }
 });
 this->addChild(manBtn);
 
 auto woman=Sprite::create("message_select_woman.png");
 woman->setPosition(Vec2(460, 470));
 woman->setAnchorPoint(Vec2(0, 0));
 this->addChild(woman);
 
 auto womanBtn=Button::create();
 womanBtn->loadTextures("select_sure.png", "select_sure.png");
 womanBtn->setPosition(Vec2(490, 500));
 womanBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
 case ui::Widget::TouchEventType::BEGAN: break;
 case ui::Widget::TouchEventType::ENDED:
 default:
 break;
 }
 });
 this->addChild(womanBtn);
 */
