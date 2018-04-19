//
//  SelectBodyScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/4/3.
//

#include "SelectBodyScene.hpp"
#include "cocos2d.h"

using namespace cocos2d::ui;
using namespace std;
using namespace cocos2d;


Scene *SelectBodyScene::createScene(){
    return SelectBodyScene::create();
}

bool SelectBodyScene::init(){
    if (!Scene::init()) {
        return false;
    }
    contraryURL="";
    return true;
};

void SelectBodyScene::onEnter(){
    Scene::onEnter();
    createHubView();
}

void SelectBodyScene::createHubView(){
    
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto bkView=Sprite::create("bk_select_body.png");
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
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
    bkView->addChild(backBtn);
    
    auto titleLB = Label::createWithSystemFont("请选择","Arial",42,Size(200,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
    titleLB->setPosition(Point(visibleSize.width/2,visibleSize.height-110));
    titleLB->setTextColor(Color4B(255, 255, 255, 255));
    titleLB->setAnchorPoint(Vec2(0.5, 0));
    bkView->addChild(titleLB);
    
    
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
    layer->setContentSize(Size(visibleSize.width-40, visibleSize.height-240));
    layer->setPosition(Point(20, 20));
    layer->setAnchorPoint(Vec2(origin.x, origin.y));
    webView = cocos2d::experimental::ui::WebView::create();
    webView->loadURL(webURL);
    webView->setContentSize(Size(visibleSize.width-40, visibleSize.height-240));
    webView->setAnchorPoint(Vec2(0,0));
    webView->setPosition(Vec2(0,0));
    webView->setScalesPageToFit(true);
    layer->addChild(webView);
    webView->setOnDidFinishLoading([](cocos2d::experimental::ui::WebView *sender, const std::string &url){
        cocos2d::experimental::ui::WebView::ccWebViewCallback content=sender->getOnJSCallback();
        log("%s",url.c_str());
    });
    
    if (strcmp(contraryURL.c_str(), "")!=0) {
    auto sickRoomBox = CheckBox::create("btn_positive_unselect.png","btn_positive_select.png");
    //设置CheckBox的位置
    sickRoomBox->setPosition(Vec2(64,visibleSize.height-210));
    sickRoomBox->setTag(0);
    sickRoomBox->setAnchorPoint(Vec2(0, 0));
    sickRoomBox->setScale(0.87);
    //设置CheckBox是否可点击
    sickRoomBox->setTouchEnabled(true);
    sickRoomBox->setSelected(true);
    sickRoomBox->addEventListener(CC_CALLBACK_2(SelectBodyScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(sickRoomBox);
    
    auto outPatientBox = CheckBox::create("btn_contrary_unselect.png","btn_contrary_select.png");
    //设置CheckBox的位置
    outPatientBox->setPosition(Vec2(visibleSize.width-200,visibleSize.height-210));
    outPatientBox->setTag(1);
    outPatientBox->setAnchorPoint(Vec2(0, 0));
    outPatientBox->setScale(0.87);
    //设置CheckBox是否可点击
    outPatientBox->setTouchEnabled(true);
    outPatientBox->addEventListener(CC_CALLBACK_2(SelectBodyScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    addChild(outPatientBox);
    
    auto layer2 = LayerColor::create(Color4B(255, 255, 255, 255));
    layer2->setContentSize(Size(visibleSize.width-40, visibleSize.height-240));
    layer2->setPosition(Point(20, 20));
    layer2->setAnchorPoint(Vec2(origin.x, origin.y));
    webView2 = cocos2d::experimental::ui::WebView::create();
    webView2->loadURL(contraryURL);
    webView2->setContentSize(Size(visibleSize.width-40, visibleSize.height-240));
    webView2->setAnchorPoint(Vec2(0,0));
    webView2->setPosition(Vec2(0,0));
    webView2->setScalesPageToFit(true);
    layer2->addChild(webView2);
    webView2->setOnDidFinishLoading([](cocos2d::experimental::ui::WebView *sender, const std::string &url){
        cocos2d::experimental::ui::WebView::ccWebViewCallback content=sender->getOnJSCallback();
        log("%s",url.c_str());
    });
    multLayer = LayerMultiplex::create(layer, layer2,nullptr);
    addChild(multLayer, 0);
    }else{
        this->addChild(layer);
    }
    
    auto saveBtn=Button::create();
    saveBtn->loadTextures("btn_sickInfo_save.png", "btn_sickInfo_save.png");
    saveBtn->setPosition(Vec2(visibleSize.width-180, visibleSize.height-110));
    saveBtn->setAnchorPoint(Vec2(0,0));
    saveBtn->setScale(0.9);
    saveBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            //C++调用JS中的方法
            string alertJS="submitSelection()";
            webView->evaluateJS(alertJS);
             if (strcmp(contraryURL.c_str(), "")!=0) {
             webView2->evaluateJS(alertJS);
             }
            log("positive url:%s,contrary url:%s",webURL.c_str(),contraryURL.c_str());
            string alertStr="alert(\"保存成功\")";
            webView->evaluateJS(alertStr);
        }
        default:
            break;
    }
    });
    bkView->addChild(saveBtn);
}

void SelectBodyScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    log("checkBox tag:%d",tag);
    if (type==cocos2d::ui::CheckBox::EventType::SELECTED) {
        if(tag>=0&&tag<=1){
            //底部切换按钮的高亮
            for (int i=0; i<2; i++) {
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
             if(tag>=0&&tag<=1){
                //切换页面
                multLayer->switchTo(tag);
            }
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:
        {
           item->setSelected(true);
        }
            log("UNSELECTED!");
            break;
        default:
            break;
    }
}

