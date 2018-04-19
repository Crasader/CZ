//
//  ChatViewScene.cpp
//  Chuangzheng-mobile
//
//  Created by lujiawei on 19/01/2018.
//

#include "ChatViewScene.hpp"
#include "cocos2d.h"

using namespace cocos2d::ui;
using namespace std;
using namespace cocos2d;


Scene *ChatViewScene::createScene(){
    return ChatViewScene::create();
}

bool ChatViewScene::init(){
    if (!Scene::init()) {
        return false;
    }
    return true;
};

void ChatViewScene::onEnter()
{
    
    Scene::onEnter();
    createHubView();
    
}

void ChatViewScene::createHubView(){
    
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto bkView=Sprite::create("bk_chat.png");
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    bkView->setPosition(Vec2(0, 0));
    this->addChild(bkView);
    
    webView = cocos2d::experimental::ui::WebView::create();
//    webView->loadURL("http://czapi.looper.pro/web/file.php?cid=22");
    webView->loadURL("http://www.webproject.wang/");
    webView->setContentSize(Size(visibleSize.width, visibleSize.height-145));
    webView->setAnchorPoint(Vec2(0,0));
    webView->setPosition(Vec2(0,0));
    webView->setScalesPageToFit(true);
    bkView->addChild(webView);
    webView->setOnDidFinishLoading([](cocos2d::experimental::ui::WebView *sender, const std::string &url){
        cocos2d::experimental::ui::WebView::ccWebViewCallback content=sender->getOnJSCallback();
       
        log("%s",url.c_str());
    });
    
 /*   auto cameraBtn=Button::create("btn_step3_camera.png");
    cameraBtn->loadTextures("btn_step3_camera.png", "btn_step3_camera.png");
    cameraBtn->setPosition(Vec2(68, visibleSize.height-100));
    cameraBtn->setAnchorPoint(Vec2(0,0));
    cameraBtn->setScale(0.86);
    cameraBtn->setColor(Color3B(240, 240, 240));
    cameraBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:{
//C++调用JS中的方法
            string alertJS="submitSelection()";
            webView->evaluateJS(alertJS);
        }
            break;
    }
    });
    bkView->addChild(cameraBtn);   */
    
   
    
/*    JSContext *context = [webView valueForKeyPath:@"documentView.webView.mainFrame.javaScriptContext"];
    context[@"toCreateOrderForID"] = ^() {
        NSArray *args = [JSContext currentArguments];
        for (JSValue *jsVal in args) {
            NSString *str= [NSString stringWithFormat:@"%@",jsVal];
    };   */
    
    
}




