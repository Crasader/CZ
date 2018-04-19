//
//  ShowImageScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/4/4.
//

#include "ShowImageScene.hpp"
#include "cocos2d.h"

using namespace cocos2d::ui;
using namespace std;
using namespace cocos2d;


Scene *ShowImageScene::createScene(){
    return ShowImageScene::create();
}

bool ShowImageScene::init(){
    if (!Scene::init()) {
        return false;
    }
    imagePath="";
    return true;
};

void ShowImageScene::onEnter(){
    Scene::onEnter();
    createHubView();
}

void ShowImageScene::createHubView(){
    
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto bkView=Sprite::create("alpha.png");//bk_select_body.png
    bkView->setAnchorPoint(Vec2(0.5, 0.5));
    bkView->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    bkView->setContentSize(visibleSize);
    this->addChild(bkView);
    
    string path=FileUtils::getInstance()->getWritablePath()+imagePath;
    imgView=Sprite::create(path);
    imgView->setAnchorPoint(Vec2(0.5, 0.5));
    imgView->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    float height3=imgView->getContentSize().height;
    imgView->setScale(visibleSize.width/height3);
    bkView->addChild(imgView);
    
    
    
    
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
    
    auto titleLB = Label::createWithSystemFont("影像","Arial",42,Size(200,50),TextHAlignment::CENTER,TextVAlignment::BOTTOM);
    titleLB->setPosition(Point(visibleSize.width/2,visibleSize.height-110));
    titleLB->setTextColor(Color4B(255, 255, 255, 255));//91, 144, 229, 255
    titleLB->setAnchorPoint(Vec2(0.5, 0));
    bkView->addChild(titleLB);
    
    auto loadBtn=Button::create();
    loadBtn->loadTextures("alpha.png", "alpha.png");
    loadBtn->setPosition(Vec2(40, 40));
    loadBtn->setScale9Enabled(true);
    loadBtn->setContentSize(Size(160, 42));
    loadBtn->setTitleText("下载");
    loadBtn->setTitleColor(Color3B(91, 144, 229));
    loadBtn->setTitleFontSize(40);
    loadBtn->setAnchorPoint(Vec2(0, 0));
    loadBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            auto pic = utils::captureNode(Director::getInstance()->getRunningScene());
            std::string filePath;
            time_t customTime = time(NULL);
            
#if  (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            filePath = "/private/var/mobile/Media/DCIM" + StringUtils::toString(customTime) + ".png";///private/var/root/Media/DCIM
            pic->saveToFile(filePath);
#elif (CC_PLATFORM_ANDROID==CC_TARGET_PLATFORM)
            filePath = "/sdcard/DCIM/Camera/" + StringUtils::toString(customTime) + ".png";
            pic->saveToFile(filePath);
#else
            filePath = FileUtils::getInstance()->getWritablePath() +StringUtils::toString(customTime) + ".png";
            pic->saveToFile(filePath);
#endif
            log("下载");
        }
        default:
            break;
    }
    });
    bkView->addChild(loadBtn);
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("alpha.png", "alpha.png");
    deleteBtn->setPosition(Vec2(visibleSize.width-200, 40));
    deleteBtn->setScale9Enabled(true);
    deleteBtn->setContentSize(Size(160, 42));
    deleteBtn->setTitleText("删除");
    deleteBtn->setTitleColor(Color3B(91, 144, 229));
    deleteBtn->setTitleFontSize(40);
    deleteBtn->setAnchorPoint(Vec2(0, 0));
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            log("删除");
            Director::getInstance()->popScene();
        }
        default:
            break;
    }
    });
    bkView->addChild(deleteBtn);
    
}
