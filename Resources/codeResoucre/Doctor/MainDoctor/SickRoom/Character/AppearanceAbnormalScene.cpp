//
//  AppearanceAbnormalScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/19.
//

#include "AppearanceAbnormalScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "ChatUserDetailScene.hpp"
#include "SearchScene.hpp"
#include "NetWrokMangerData.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *AppearanceAbnormalScene::createScene(){
    return AppearanceAbnormalScene::create();
}
//用于存储数据
ValueMap map1;

Map<int, Sprite*> wholeDic;

ScrollView *scrollV;
Sprite *moveView;
bool AppearanceAbnormalScene::init(){
    if (!Scene::init()) {
        return false;
    }
#pragma-ValueVector加入数据
    ValueVector vector1;
    vector1.push_back(Value("面部不对称"));
     vector1.push_back(Value("双肩不等高"));
     vector1.push_back(Value("肩胛骨不等高（前屈位）"));
     vector1.push_back(Value("骼棘不等高"));
     vector1.push_back(Value("下肢不等长"));
    log("%ld",vector1.size());
    string key1 = "双侧不对称";
    ValueVector vector2;
    vector2.push_back(Value("鱼际肌"));
    vector2.push_back(Value("掌间肌"));
    vector2.push_back(Value("肱二头肌"));
    vector2.push_back(Value("肱三头肌"));
    vector2.push_back(Value("三角肌"));
    vector2.push_back(Value("股四头肌"));
    vector2.push_back(Value("腓肠肌"));
    string key2 = "肌肉萎缩";
    ValueVector vector3;
    vector3.push_back(Value("变直"));
    vector3.push_back(Value("反曲"));
    vector3.push_back(Value("侧弯"));
    string key3 = "脊柱曲度改变";
#pragma-ValueMap加入数据
    map1["双侧不对称"] = Value(vector1).asValueVector();
    map1["肌肉萎缩"]=Value(vector2).asValueVector();
    map1["脊柱曲度改变"]=Value(vector3).asValueVector();
    
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto bkView=Sprite::create("bk_appearance.png");
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
    sureBtn->loadTextures("btn_step4_sure.png", "btn_step4_sure.png");
    sureBtn->setPosition(Vec2(visibleSize.width-80, visibleSize.height-85));
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            pushDataToNetWork();
        }
            
        default:
            break;
    }
    });
    bkView->addChild(sureBtn);
    
    
   scrollV=createTableView(Vec2(0, visibleSize.height-150), Size(visibleSize.width, visibleSize.height-170));
    this->addChild(scrollV);
    
    return true;
}

ScrollView* AppearanceAbnormalScene::createTableView(Vec2 origin,Size visibleSize){
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(origin.x, origin.y));
    scrollView->setAnchorPoint(Vec2(0, 1));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);//方向
    scrollView->setScrollBarEnabled(true);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, visibleSize.height));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 0, 255));//设置背景颜色
    
    moveView=Sprite::create("alpha.png");
    moveView->setPosition(Vec2(0, scrollView->getInnerContainerSize().height));
    moveView->setAnchorPoint(Vec2(0, 1));
    moveView->setContentSize(visibleSize);
    scrollView->addChild(moveView);
    
    float pointY1 =creatLabelView(Vec2(59, scrollView->getInnerContainerSize().height-70), moveView, "短颈",1);
    float pointY2=creatLabelView(Vec2(59, pointY1-50), moveView, "牛奶咖啡斑",2);
    float pointY3=creatLabelView(Vec2(59, pointY2-50), moveView, "剃刀背",3);
    float pointY4=creatLabelView(Vec2(59, pointY3-50), moveView, "足下垂",4);
    
    float pointY5 =createPopUpView(Vec2(40, pointY4-20), moveView, "双侧不对称",5,1);
     float pointY6 =createPopUpView(Vec2(40, pointY5+60*5), moveView, "肌肉萎缩",10,2);
   float pointY7 = createPopUpView(Vec2(40, pointY6+60*7), moveView, "脊柱曲度改变",17,3);
    
#warning -在这里设置没有用，因为当innerSize<contentSize，以contentSize为准
    if (visibleSize.height>visibleSize.height-20-pointY7) {
        scrollView->setContentSize(Size(visibleSize.width,visibleSize.height-20-pointY7));
        scrollView->setInnerContainerSize(Size(visibleSize.width, visibleSize.height-20-pointY7));
        moveView->setPosition(Vec2(0, scrollView->getInnerContainerSize().height));
    }else{
        scrollView->setContentSize(Size(visibleSize.width,visibleSize.height));
        scrollView->setInnerContainerSize(Size(visibleSize.width, visibleSize.height-20-pointY7));
        moveView->setPosition(Vec2(0, scrollView->getInnerContainerSize().height));
    }
    log("%f",scrollView->getInnerContainerSize().height);
    return scrollView;
}

float AppearanceAbnormalScene::createPopUpView(Vec2 point,Sprite* bkView,string name,int tag,int type){
    Size visibleSize=Director::getInstance()->getVisibleSize();
#pragma-ValueMap取值
     ValueVector vect=map1.at(name).asValueVector();
    long index=vect.size();
    
    auto wholeV=Sprite::create("alpha.png");
    wholeV->setPosition(Vec2(0,0));
    wholeV->setAnchorPoint(Vec2(0, 0));
    wholeV->setContentSize(Size(visibleSize.width, point.y));
    wholeV->setTag(200+tag);
     bkView->addChild(wholeV);
#pragma-Map<int, Sprite*> wholeDic加入字典
    wholeDic.insert(tag, wholeV);
    
    auto whiteV=Sprite::create("usercase_whiterect.png");
    whiteV->setPosition(Vec2(point.x, point.y-60*(index+1)));
    whiteV->setAnchorPoint(Vec2(0, 0));
    whiteV->setContentSize(Size(visibleSize.width-80, 60*(index+1)));
    whiteV->setTag(tag+200);
    whiteV->setVisible(false);
    wholeV->addChild(whiteV);
#pragma-ValueVector取值
    for (int i=0; i<index; i++) {
        auto whiteStr= vect.at(i).asString();
        creatBlueLabelView(Vec2(0,60*i), whiteV,whiteStr,tag+i,type);
    }
    
    auto blueV=Sprite::create("usercase_bluerect.png");
    blueV->setPosition(Vec2(point.x, point.y-60));
    blueV->setAnchorPoint(Vec2(0, 0));
    blueV->setContentSize(Size(visibleSize.width-80, 60));
    wholeV->addChild(blueV);
    auto userName = Label::createWithSystemFont(name,"Arial",35,Size(300,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    userName->setPosition(Vec2(20,0));
    userName->setTextColor(Color4B(255, 255, 255, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    blueV->addChild(userName);
    

//设置选中和未选中的弹出框button
    auto start = MenuItemImage::create("btn_appearance_down.png","");  //显示为on
    auto stop = MenuItemImage::create("btn_appearance_up.png","");  //显示为off
    auto toggle = MenuItemToggle::createWithCallback(
                                                     CC_CALLBACK_1(AppearanceAbnormalScene::menuLoginCallback,this),
                                                     start,
                                                     stop,
                                                     NULL);
     toggle->setPosition(Vec2(blueV->getContentSize().width-60,20));  //设置坐标在屏幕居中
    toggle->setAnchorPoint(Vec2(0, 0));
    toggle->setTag(100+tag);
    auto box = Menu::create(toggle,NULL);
    box->setPosition(Point::ZERO);
    blueV->addChild(box);
    
    return point.y-(index+1)*60-20;
    
}


void AppearanceAbnormalScene::menuLoginCallback(Ref* pSender)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    MenuItemToggle* item=(MenuItemToggle*)pSender;
     int  index=item->getSelectedIndex();
    int tag= item->getTag();
    if (index==1) {
        
#pragma-Map<int, Sprite*> wholeDic取值
        auto wholeV = (Sprite*)wholeDic.at(tag-100);
        auto whiteV=(Sprite*)wholeV->getChildByTag(tag+100);
        whiteV->setVisible(true);
        //判断是否需要移动下方的sprite
        std::vector<int> mapKeyVec;
        mapKeyVec = wholeDic.keys();
        sort(mapKeyVec.begin(), mapKeyVec.end());
        for(int nextTag : mapKeyVec)
        {
            //                    log("%d",nextTag);
            if (nextTag>tag-100) {
                auto nextWholeV = (Sprite*)wholeDic.at(nextTag);
                nextWholeV->setPosition(Vec2(nextWholeV->getPosition().x, nextWholeV->getPosition().y-whiteV->getContentSize().height+60));
            }
        }
        //                log("原先的%f",scrollV->getInnerContainerSize().height);
        scrollV->setInnerContainerSize(Size(visibleSize.width,scrollV->getInnerContainerSize().height+whiteV->getContentSize().height-60));
                        log("现在的%f",scrollV->getInnerContainerSize().height);
        moveView->setPosition(Vec2(0, scrollV->getInnerContainerSize().height));
#pragma -调整scrollView的contentSize
        scrollV->setInnerContainerPosition(Vec2(0, 60-whiteV->getContentSize().height));
        log("%f",scrollV->getInnerContainerPosition().y);

        if (scrollV->getInnerContainerSize().height<visibleSize.height-170) {
            //用于调整scrollView的contentOffset
            scrollV->setContentSize(Size(visibleSize.width, scrollV->getInnerContainerSize().height));
        }else{
            scrollV->setContentSize(Size(visibleSize.width, visibleSize.height-170));
        }
        
    }else if (index==0){
        auto wholeV = (Sprite*)wholeDic.at(tag-100);
        auto whiteV=wholeV->getChildByTag(tag+100);
        whiteV->setVisible(false);
        //判断是否需要移动下方的sprite
        std::vector<int> mapKeyVec;
        mapKeyVec = wholeDic.keys();
        sort(mapKeyVec.begin(), mapKeyVec.end());
        for(int nextTag : mapKeyVec)
        {
            log("%d",nextTag);
            if (nextTag>tag-100) {
                auto nextWholeV = (Sprite*)wholeDic.at(nextTag);
                nextWholeV->setPosition(Vec2(nextWholeV->getPosition().x, nextWholeV->getPosition().y+whiteV->getContentSize().height-60));
            }
        }
        scrollV->setContentSize(Size(visibleSize.width, scrollV->getInnerContainerSize().height-whiteV->getContentSize().height+60));
        scrollV->setInnerContainerSize(Size(visibleSize.width,scrollV->getInnerContainerSize().height-whiteV->getContentSize().height+60));
        moveView->setPosition(Vec2(0, scrollV->getInnerContainerSize().height));
    }
   
}

//实现CheckBox回调函数
void AppearanceAbnormalScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    Size visibleSize=Director::getInstance()->getVisibleSize();
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    log("tag:%d",tag);
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
        {
        
        }
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
            log("UNSELECTED!");
        {
        }
            break;
        default:
            break;
    }
}

float AppearanceAbnormalScene::creatBlueLabelView(Vec2 point,Sprite* bkView,string name,int tag,int type){
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto userName = Label::createWithSystemFont(name,"Arial",35,Size(200,60),TextHAlignment::LEFT,TextVAlignment::CENTER);
    userName->setPosition(Vec2(point.x+20, point.y));
    userName->setTextColor(Color4B(0, 0, 0, 255/2));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    if (type==1) {
    auto box = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    box->setPosition(Vec2(bkView->getContentSize().width-60,point.y+10));
    box->setScale(0.87);
    box->setTag(tag);
    box->setAnchorPoint(Vec2(0, 0));
    //设置CheckBox是否可点击
    box->setTouchEnabled(true);
    box->addEventListener(CC_CALLBACK_2(AppearanceAbnormalScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    bkView->addChild(box);
    boxDic.insert(tag, box);
    }else if (type==2){
        auto box = CheckBox::create("select_circle.png","select_sure.png");
        //设置CheckBox的位置
        box->setPosition(Vec2(bkView->getContentSize().width-60,point.y+10));
        box->setScale(0.87);
        box->setTag(tag);
        box->setAnchorPoint(Vec2(0, 0));
        //设置CheckBox是否可点击
        box->setTouchEnabled(true);
        box->addEventListener(CC_CALLBACK_2(AppearanceAbnormalScene::checkBoxCallback,this));
        //获取checkbox的选中状态
        bkView->addChild(box);
        boxDic.insert(tag, box);
        auto boxName= Label::createWithSystemFont("R","Arial",35,Size(60,60),TextHAlignment::CENTER,TextVAlignment::CENTER);
        boxName->setPosition(Vec2(bkView->getContentSize().width-120, point.y));
        boxName->setTextColor(Color4B(0, 0, 0, 255/2));
        boxName->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(boxName);
        
        auto box2 = CheckBox::create("select_circle.png","select_sure.png");
        //设置CheckBox的位置
        box2->setPosition(Vec2(bkView->getContentSize().width-180,point.y+10));
        box2->setScale(0.87);
        box2->setTag(tag+1000);
        box2->setAnchorPoint(Vec2(0, 0));
        //设置CheckBox是否可点击
        box2->setTouchEnabled(true);
        box2->addEventListener(CC_CALLBACK_2(AppearanceAbnormalScene::checkBoxCallback,this));
        //获取checkbox的选中状态
        bkView->addChild(box2);
        boxDic.insert(tag+1000, box2);
        auto boxName2= Label::createWithSystemFont("L","Arial",35,Size(60,60),TextHAlignment::CENTER,TextVAlignment::CENTER);
        boxName2->setPosition(Vec2(bkView->getContentSize().width-240, point.y));
        boxName2->setTextColor(Color4B(0, 0, 0, 255/2));
        boxName2->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(boxName2);
    }else if (type==3){
        auto box = CheckBox::create("select_circle.png","select_sure.png");
        //设置CheckBox的位置
        box->setPosition(Vec2(bkView->getContentSize().width-60,point.y+10));
        box->setScale(0.87);
        box->setTag(tag);
        box->setAnchorPoint(Vec2(0, 0));
        //设置CheckBox是否可点击
        box->setTouchEnabled(true);
        box->addEventListener(CC_CALLBACK_2(AppearanceAbnormalScene::checkBoxCallback,this));
        //获取checkbox的选中状态
        bkView->addChild(box);
        boxDic.insert(tag, box);
        auto boxName= Label::createWithSystemFont("腰椎","Arial",30,Size(80,60),TextHAlignment::CENTER,TextVAlignment::CENTER);
        boxName->setPosition(Vec2(bkView->getContentSize().width-140, point.y));
        boxName->setTextColor(Color4B(0, 0, 0, 255/3*2));
        boxName->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(boxName);
        
        auto box2 = CheckBox::create("select_circle.png","select_sure.png");
        //设置CheckBox的位置
        box2->setPosition(Vec2(bkView->getContentSize().width-200,point.y+10));
        box2->setScale(0.87);
        box2->setTag(tag+1000);
        box2->setAnchorPoint(Vec2(0, 0));
        //设置CheckBox是否可点击
        box2->setTouchEnabled(true);
        box2->addEventListener(CC_CALLBACK_2(AppearanceAbnormalScene::checkBoxCallback,this));
        //获取checkbox的选中状态
        bkView->addChild(box2);
        boxDic.insert(tag+1000, box2);
        auto boxName2= Label::createWithSystemFont("胸椎","Arial",30,Size(80,60),TextHAlignment::CENTER,TextVAlignment::CENTER);
        boxName2->setPosition(Vec2(bkView->getContentSize().width-280, point.y));
        boxName2->setTextColor(Color4B(0, 0, 0, 255/3*2));
        boxName2->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(boxName2);
        
        auto box3 = CheckBox::create("select_circle.png","select_sure.png");
        //设置CheckBox的位置
        box3->setPosition(Vec2(bkView->getContentSize().width-340,point.y+10));
        box3->setScale(0.87);
        box3->setTag(tag+2000);
        box3->setAnchorPoint(Vec2(0, 0));
        //设置CheckBox是否可点击
        box3->setTouchEnabled(true);
        box3->addEventListener(CC_CALLBACK_2(AppearanceAbnormalScene::checkBoxCallback,this));
        //获取checkbox的选中状态
        bkView->addChild(box3);
        boxDic.insert(tag+2000, box3);
        auto boxName3= Label::createWithSystemFont("颈椎","Arial",30,Size(80,60),TextHAlignment::CENTER,TextVAlignment::CENTER);
        boxName3->setPosition(Vec2(bkView->getContentSize().width-420, point.y));
        boxName3->setTextColor(Color4B(0, 0, 0, 255/3*2));
        boxName3->setAnchorPoint(Vec2(0, 0));
        bkView->addChild(boxName3);
        
    }
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(0, point.y));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.89);
    bkView->addChild(lineV);
    return point.y-20;
}


float AppearanceAbnormalScene::creatLabelView(Vec2 point,Sprite* bkView,string name,int tag){
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto userName = Label::createWithSystemFont(name,"Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userName->setPosition(point);
    userName->setTextColor(Color4B(91, 144, 229, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    auto box = CheckBox::create("select_circle.png","select_sure.png");
    //设置CheckBox的位置
    box->setPosition(Vec2(visibleSize.width-100,point.y+2));
    box->setScale(0.87);
    box->setAnchorPoint(Vec2(0, 0));
    box->setTag(tag);
    //设置CheckBox是否可点击
    box->setTouchEnabled(true);
    box->addEventListener(CC_CALLBACK_2(AppearanceAbnormalScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    bkView->addChild(box);
    boxDic.insert(tag, box);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(51, point.y-10));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setScaleX(0.85);
    bkView->addChild(lineV);
    return point.y-20;
}



std::string AppearanceAbnormalScene::getJsonData(int type)
{
    rapidjson::Document document;
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    if (type==0) {
        document.SetArray();
        for (int i=1; i<5; i++) {
            CheckBox*currentBox=boxDic.at(i);
            if (currentBox->getSelectedState()) {
                document.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
            }
        }
    }else if(type==1){//两侧不对称
        document.SetArray();
        for (int i=5; i<10; i++) {
            CheckBox*currentBox=boxDic.at(i);
            if (currentBox->getSelectedState()) {
                document.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
            }
        }
    }else if(type==2){//肌肉萎缩
        document.SetArray();
        for (int i=10; i<17; i++) {
            CheckBox*currentBox=boxDic.at(i);
            if (currentBox->getSelectedState()) {
                document.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
            }
        }
        for (int i=1010; i<1017; i++) {
            CheckBox*currentBox=boxDic.at(i);
            if (currentBox->getSelectedState()) {
                document.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
            }
        }
    }else if(type==3){
        document.SetArray();
        for (int i=17; i<20; i++) {
            CheckBox*currentBox=boxDic.at(i);
            if (currentBox->getSelectedState()) {
                document.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
            }
        }
    }else if(type==4){
        document.SetArray();
        for (int i=1017; i<1020; i++) {
            CheckBox*currentBox=boxDic.at(i);
            if (currentBox->getSelectedState()) {
                document.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
            }
        }
    }else if(type==5){
        document.SetArray();
        for (int i=2017; i<2020; i++) {
            CheckBox*currentBox=boxDic.at(i);
            if (currentBox->getSelectedState()) {
                document.PushBack(rapidjson::Value(changeNumToString(i).c_str(), allocator),allocator);
            }
        }
    }
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    
    log("buffer:%s",buffer.GetString());
    return buffer.GetString();
}

#pragma-用于加载网络数据
void AppearanceAbnormalScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char jsonStr[1000]={0};
    sprintf(jsonStr,"%s;%s;%s;%s;%s;%s",getJsonData(0).c_str(),getJsonData(1).c_str(),getJsonData(2).c_str(),getJsonData(3).c_str(),getJsonData(4).c_str(),getJsonData(5).c_str());
    char*json=jsonStr;
    char memberUrl[1000]={0};
    sprintf(memberUrl,"recordId=%s&keys=%s&answers=%s",UserDefault::getInstance()->getStringForKey("caseId").c_str(),"tz_wgyc;tz_wgyc_bdc;tz_wgyc_ws;tz_wgyc_gb_bz;tz_wgyc_gb_fq;tz_wgyc_gb_cw",json);
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/updateMedicalRecords";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(AppearanceAbnormalScene::onHttpRequestCompleted, this),url);
}

void AppearanceAbnormalScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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




string AppearanceAbnormalScene::changeNumToString(int num){
    string content="";
    switch (num) {
        case 1:
            content="短颈";
            break;
        case 2:
            content="牛奶咖啡斑";
            break;
        case 3:
            content="剃刀背";break;//神经根型颈椎病
        case 4:
            content="足下垂";break;
//双侧不对称
        case 5:
            content="面部不对称";break;
        case 6:
            content="双肩不等高";break;
        case 7:
            content="肩胛骨不等";break;
        case 8:
            content="骼棘不等高";break;
        case 9:
            content="下肢不等长";break;
//肌肉萎缩
        case 10:
            content="鱼际肌-R";break;
        case 11:
            content="掌间肌-R";break;
        case 12:
            content="肱二头肌-R";break;
        case 13:
            content="肱三头肌-R";break;
        case 14:
            content="三角肌-R";break;
        case 15:
            content="股四头肌-R";break;
        case 16:
            content="腓肠肌-R";break;
        case 1010:
            content="鱼际肌-L";break;
        case 1011:
            content="掌间肌-L";break;
        case 1012:
            content="肱二头肌-L";break;
        case 1013:
            content="肱三头肌-L";break;
        case 1014:
            content="三角肌-L";break;
        case 1015:
            content="股四头肌-L";break;
        case 1016:
            content="腓肠肌-L";break;
//脊柱曲度改变
        case 17:  case 18 :case 19 :
            content="腰椎";break;
        case 1017:  case 1018 :case 1019 :
            content="胸椎";break;
        case 2017:  case 2018 :case 2019 :
            content="颈椎";break;
            
            
        default:
            break;
    }
    return content;
}


