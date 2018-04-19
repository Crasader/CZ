//
//  UpdateCasePhotoScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/4/3.
//

#include "UpdateCasePhotoScene.hpp"
#include "cocos2d.h"

using namespace cocos2d::ui;
using namespace std;
using namespace cocos2d;


Scene *UpdateCasePhotoScene::createScene(){
    return UpdateCasePhotoScene::create();
}

bool UpdateCasePhotoScene::init(){
    if (!Scene::init()) {
        return false;
    }
    return true;
};

void UpdateCasePhotoScene::onEnter()
{
    
    Scene::onEnter();
    createHubView();
    
}

void UpdateCasePhotoScene::createHubView(){
    
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
    
    auto titleLB = Label::createWithSystemFont("上传影像","Arial",42,Size(200,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
    titleLB->setPosition(Point(visibleSize.width/2,visibleSize.height-110));
    titleLB->setTextColor(Color4B(255, 255, 255, 255));
    titleLB->setAnchorPoint(Vec2(0.5, 0));
    bkView->addChild(titleLB);
    
    webView = cocos2d::experimental::ui::WebView::create();
    webView->loadURL(webURL);
    webView->setContentSize(Size(visibleSize.width, visibleSize.height-145));
    webView->setAnchorPoint(Vec2(0,0));
    webView->setPosition(Vec2(0,0));
    webView->setScalesPageToFit(true);
    bkView->addChild(webView);
    webView->setOnDidFinishLoading([](cocos2d::experimental::ui::WebView *sender, const std::string &url){
//        cocos2d::experimental::ui::WebView::ccWebViewCallback content=sender->getOnJSCallback();
        log("%s",url.c_str());
    });
    
}
