//
//  AccountManageScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2017/12/28.
//

#include "AccountManageScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "LoginScene.h"
#include "NetWrokMangerData.hpp"
#include "DrawLineScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *AccountManageScene::createScene(){
    return AccountManageScene::create();
}
bool AccountManageScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    
    bkView=Sprite::create("bk_accountManage.png");
    bkView->setPosition(Vec2(0, 0));
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(visibleSize);
    this->addChild(bkView);
    auto backBtn=Button::create();
    backBtn->loadTextures("btn_register_return.png", "btn_register_return.png");
    backBtn->setPosition(Vec2(80, visibleSize.height-85));
    backBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            updateDataToNetWork();
            backBtnType=1;
        }
        default:
            break;
    }
    });
    this->addChild(backBtn);
     pushDataToNetWork();
    return true;
}

void AccountManageScene::createMainView(){
    Size visibleSize=Director::getInstance()->getVisibleSize();
    
    auto headBtn=Button::create();
    headBtn->loadTextures("btn_update_head.png", "btn_update_head.png");
    headBtn->setAnchorPoint(Vec2(0, 0));
    headBtn->setPosition(Vec2(220, 820));
    headBtn->setScale(1.0);
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
    
    //密码修改
    auto judgeBtn=Button::create();
    judgeBtn->loadTextures("userInfo_judge.png", "userInfo_judge.png");
    judgeBtn->setPosition(Vec2(visibleSize.width-100, 375));
    judgeBtn->setAnchorPoint(Vec2(0, 0));
    judgeBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            auto chageLayer=createChangeKeyLayer();
            chageLayer->setTag(1050);
            this->addChild(chageLayer);
        }
        default:
            break;
    }
    });
    bkView->addChild(judgeBtn);
    //手势锁
    keyCheckBox = CheckBox::create("btn_userInfo_OFF.png","btn_userInfo_ON.png");
    //设置CheckBox的位置
    keyCheckBox->setPosition(Vec2(visibleSize.width-200, 535));
    keyCheckBox->setTag(10);
    keyCheckBox->setAnchorPoint(Vec2(0, 0));
    keyCheckBox->setSelectedState(atoi(infoData["data"]["isLock"].GetString()));
    //设置CheckBox是否可点击
    keyCheckBox->setTouchEnabled(true);
    keyCheckBox->addEventListener(CC_CALLBACK_2(AccountManageScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    bkView->addChild(keyCheckBox);
    
    //手势锁
    keyAccompanyBox = CheckBox::create("btn_userInfo_OFF.png","btn_userInfo_ON.png");
    //设置CheckBox的位置
    keyAccompanyBox->setPosition(Vec2(visibleSize.width-200, 455));
    keyAccompanyBox->setTag(11);
    keyAccompanyBox->setAnchorPoint(Vec2(0, 0));
    keyAccompanyBox->setSelectedState(atoi(infoData["data"]["isRecieve"].GetString()));
    //设置CheckBox是否可点击
    keyAccompanyBox->setTouchEnabled(true);
    keyAccompanyBox->addEventListener(CC_CALLBACK_2(AccountManageScene::checkBoxCallback,this));
    //获取checkbox的选中状态
    bkView->addChild(keyAccompanyBox);
    
    
    auto exitBtn=Button::create();
    exitBtn->loadTextures("btn_userInfo_back.png", "btn_userInfo_back.png");
    exitBtn->setPosition(Vec2(visibleSize.width/2-120, 214));
    exitBtn->setAnchorPoint(Vec2(0, 0));
    exitBtn->setScale(0.87);
    exitBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            auto exitLayer=createExitLayer();
            exitLayer->setTag(2001);
            this->addChild(exitLayer);
            break;
        }
        default:
            break;
    }
    });
    bkView->addChild(exitBtn);
    
    textfieldName=createBasicData(bkView, Vec2(86, 768), "真实姓名：", infoData["data"]["name"].GetString());
    
    
    auto roleStr = Label::createWithSystemFont("身份：","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    roleStr->setPosition(Vec2(86, 688));
    roleStr->setTextColor(Color4B(91, 144, 229, 255));
    roleStr->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(roleStr);
    roleNum="";
    auto roleBtn = Label::createWithSystemFont(getEducationFromRole(infoData["data"]["role"].GetString()),"Arial",35,Size(400,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    roleBtn->setTag(40);
    roleBtn->setPosition(Vec2(visibleSize.width-86,688));
    roleBtn->setTextColor(Color4B(40, 40, 40, 255));
    roleBtn->setAnchorPoint(Vec2(1, 0));
    bkView->addChild(roleBtn);
    //label添加监听
    auto listenter = EventListenerTouchOneByOne::create();
    listenter->onTouchBegan = [roleBtn](Touch* t, Event * e) {
        if (roleBtn->getBoundingBox().containsPoint(t->getLocation())) {
            auto target = static_cast<AccountManageScene*>(e->getCurrentTarget());
            auto layer=target->createChangeRoleLayer();
            target->addChild(layer);
            layer->setTag(2002);
        }
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenter, this);
    
    auto lineV2=Sprite::create("userInfo_line.png");
    lineV2->setPosition(Vec2(70, 682));
    lineV2->setAnchorPoint(Vec2(0, 0));
    lineV2->setContentSize(Size(visibleSize.width-140, 1.5));
    bkView->addChild(lineV2);
    
    
    auto userName = Label::createWithSystemFont("用户名：","Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userName->setPosition(Vec2(86, 608));
    userName->setTextColor(Color4B(91, 144, 229, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    auto userName2 = Label::createWithSystemFont(infoData["data"]["userId"].GetString(),"Arial",35,Size(400,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    userName2->setPosition(Vec2(visibleSize.width-86,608));
    userName2->setTextColor(Color4B(40, 40, 40, 255));
    userName2->setAnchorPoint(Vec2(1, 0));
    bkView->addChild(userName2);
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(70, 602));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setContentSize(Size(visibleSize.width-140, 1.5));
    bkView->addChild(lineV);
    
    createLabelWithoutField(bkView, Vec2(86, 528), "手势锁");
    createLabelWithoutField(bkView, Vec2(86, 448), "随访提醒");
    createLabelWithoutField(bkView, Vec2(86, 368), "密码修改");
}
/*
1 => '带组教授',
2 => '主治医生',
3 => '住院医生',
4 => '研究生',*/
string AccountManageScene::getEducationFromRole(std::string role){
    if (role=="1") {
        return "带组教授";
    }else if(role=="2"){
        return "主治医生";
    }else if (role=="3"){
        return "住院医生";
    }else{
        return "研究生";
    }
    return "医生";
}

void AccountManageScene::createRoleLabel(){
    bkView->removeChildByTag(40);
    auto  visibleSize=Director::getInstance()->getVisibleSize();
    auto roleBtn = Label::createWithSystemFont(getEducationFromRole(infoData["data"]["role"].GetString()),"Arial",35,Size(400,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    if (roleNum!="") {
        roleBtn->setString(getEducationFromRole(roleNum.c_str()));
    }
    roleBtn->setPosition(Vec2(visibleSize.width-86,688));
    roleBtn->setTextColor(Color4B(40, 40, 40, 255));
    roleBtn->setAnchorPoint(Vec2(1, 0));
    bkView->addChild(roleBtn);
    //label添加监听
    auto listenter = EventListenerTouchOneByOne::create();
    listenter->onTouchBegan = [roleBtn](Touch* t, Event * e) {
        if (roleBtn->getBoundingBox().containsPoint(t->getLocation())) {
            auto target = static_cast<AccountManageScene*>(e->getCurrentTarget());
            auto layer=target->createChangeRoleLayer();
            target->addChild(layer);
            layer->setTag(2002);
        }
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenter, this);
}


EditBox*  AccountManageScene::createBasicData(Sprite* bkView,Vec2 point,string name1,string name2){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto userName = Label::createWithSystemFont(name1,"Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userName->setPosition(point);
    userName->setTextColor(Color4B(91, 144, 229, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    auto   textFieldUser = EditBox::create(Size(360,50), Scale9Sprite::create("alpha.png"));
    textFieldUser->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    textFieldUser->setAnchorPoint(Vec2(1, 0));
    textFieldUser->setPosition(Vec2(visibleSize.width-86,point.y));
    textFieldUser->setFontName("Arial");
    textFieldUser->setFontSize(35);
    textFieldUser->setPlaceholderFontSize(35);
    textFieldUser->setFontColor(Color3B::BLACK);
    string placeHolder="                                      ";
    placeHolder.append(name2);
    textFieldUser->setPlaceHolder(placeHolder.c_str());
    textFieldUser->setPlaceholderFontColor(Color3B(240, 240, 240));
    textFieldUser->setReturnType(EditBox::KeyboardReturnType::DONE);
    textFieldUser->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);//可以输入任何，但是不包括换行
    bkView->addChild(textFieldUser);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(70, point.y-6));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setContentSize(Size(visibleSize.width-140, 1.5));
    bkView->addChild(lineV);
    
    return textFieldUser;
}

void  AccountManageScene::createLabelWithoutField(Sprite* bkView,Vec2 point,string name){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto userName = Label::createWithSystemFont(name,"Arial",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    userName->setPosition(point);
    userName->setTextColor(Color4B(91, 144, 229, 255));
    userName->setAnchorPoint(Vec2(0, 0));
    bkView->addChild(userName);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(70, point.y-6));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setContentSize(Size(visibleSize.width-140, 1.5));
    bkView->addChild(lineV);
}



Layer* AccountManageScene::createAlbumLayer(){
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

//退出账号
Layer* AccountManageScene::createExitLayer(){
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
    auto contentV = Sprite::create("bk_sureExit.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(0,0));
    contentV->setContentSize(visibleSize);
    layer->addChild(contentV);
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_sureExit_sure.png", "btn_sureExit_sure.png");
    sureBtn->setPosition(Vec2(160, 541));
    sureBtn->setAnchorPoint(Vec2(0,0));
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            this->removeChildByTag(2001);
            auto loginnSC=LoginScene::createScene();
            Director::getInstance()->replaceScene(loginnSC);
            break;
        }
        default:
            break;
    }
    });
    contentV->addChild(sureBtn);
    
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_QRCode_close.png", "btn_QRCode_close.png");
    deleteBtn->setPosition(Vec2(visibleSize.width-115, 730));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            this->removeChildByTag(2001);
            break;
    }
    });
    contentV->addChild(deleteBtn);
    
    
    
    return layer;
    
}



//修改密码
Layer* AccountManageScene::createChangeKeyLayer(){
    passWordIsDestory=1;
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
    auto contentV = Sprite::create("bk_change_password.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(0,0));
    contentV->setContentSize(visibleSize);
    layer->addChild(contentV);
    
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_QRCode_close.png", "btn_QRCode_close.png");
    deleteBtn->setPosition(Vec2(visibleSize.width-110, 700));
    deleteBtn->setAnchorPoint(Vec2(0,0));
    deleteBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        default:
            passWordIsDestory=0;
            this->removeChildByTag(1050);
            break;
    }
    });
    contentV->addChild(deleteBtn);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_change_password_save.png", "btn_change_password_save.png");
    sureBtn->setPosition(Vec2(225, 361));
    sureBtn->setAnchorPoint(Vec2(0,0));
    sureBtn->cocos2d::Node::setScale(0.87);
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            string pass=newPassword->getText();
            if (pass.size()<6) {
                auto judgeV = Label::createWithSystemFont("您设置的密码位数少于6位","Arial",35,Size(visibleSize.width,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
                judgeV->setPosition(Vec2(visibleSize.width/2+100, 268));
                judgeV->setTextColor(Color4B(91, 144, 229, 255));
                judgeV->setAnchorPoint(Vec2(0, 0));
                this->addChild(judgeV);
                judgeV->runAction(Sequence::create(DelayTime::create(0.5),FadeOut::create(0.5), NULL));
            }else if(strcmp(newPassword->getText(), surePassword->getText())){
                auto judgeV = Label::createWithSystemFont("您输入的密码前后不一样","Arial",35,Size(visibleSize.width,50),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
                judgeV->setPosition(Vec2(visibleSize.width/2+100, 268));
                judgeV->setTextColor(Color4B(91, 144, 229, 255));
                judgeV->setAnchorPoint(Vec2(0, 0));
                this->addChild(judgeV);
                judgeV->runAction(Sequence::create(DelayTime::create(0.5),FadeOut::create(0.5), NULL));
            }else{
                updateDataToNetWork();
                this->removeChildByTag(1050);
            }
            break;
        }
        default:
            break;
    }
    });
    contentV->addChild(sureBtn);
    
    originalPassword = EditBox::create(Size(295, 50), Scale9Sprite::create("alpha.png"));
    originalPassword->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    originalPassword->setAnchorPoint(Vec2(1, 0));
    originalPassword->setPosition(Vec2(visibleSize.width-100,585));
    originalPassword->setFontName("Arial");
    originalPassword->setFontSize(35);
    originalPassword->setPlaceholderFontSize(35);
    originalPassword->setFontColor(Color3B::BLACK);
    originalPassword->setPlaceHolder("未填写");
    originalPassword->setPlaceholderFontColor(Color3B::GRAY);
    originalPassword->setReturnType(EditBox::KeyboardReturnType::DONE);
    originalPassword->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);//可以输入任何，但是不包括换行
    originalPassword->setInputFlag(cocos2d::ui::EditBox::InputFlag::PASSWORD);
    originalPassword->setTag(1000);
    originalPassword->setMaxLength(15);
    //    textFieldUser->setDelegate(this);
    contentV->addChild(originalPassword);
    
    newPassword = EditBox::create(Size(295, 50), Scale9Sprite::create("alpha.png"));
    newPassword->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    newPassword->setAnchorPoint(Vec2(1, 0));
    newPassword->setPosition(Vec2(visibleSize.width-100,520));
    newPassword->setFontName("Arial");
    newPassword->setFontSize(35);
    newPassword->setPlaceholderFontSize(35);
    newPassword->setFontColor(Color3B::BLACK);
    newPassword->setPlaceHolder("最多15位");
    newPassword->setPlaceholderFontColor(Color3B::GRAY);
    newPassword->setReturnType(EditBox::KeyboardReturnType::DONE);
    newPassword->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);//可以输入任何，但是不包括换行
    newPassword->setInputFlag(cocos2d::ui::EditBox::InputFlag::PASSWORD);
    newPassword->setTag(1001);
    newPassword->setMaxLength(15);
    //    textFieldUser->setDelegate(this);
    contentV->addChild(newPassword);
    
    surePassword = EditBox::create(Size(295, 50), Scale9Sprite::create("alpha.png"));
    surePassword->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    surePassword->setAnchorPoint(Vec2(1, 0));
    surePassword->setPosition(Vec2(visibleSize.width-100,450));
    surePassword->setFontName("Arial");
    surePassword->setFontSize(35);
    surePassword->setPlaceholderFontSize(35);
    surePassword->setFontColor(Color3B::BLACK);
    surePassword->setPlaceHolder("最多15位");
    surePassword->setPlaceholderFontColor(Color3B::GRAY);
    surePassword->setReturnType(EditBox::KeyboardReturnType::DONE);
    surePassword->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);//可以输入任何，但是不包括换行
    surePassword->setInputFlag(cocos2d::ui::EditBox::InputFlag::PASSWORD);
    surePassword->setTag(1002);
    surePassword->setMaxLength(15);
    //    textFieldUser->setDelegate(this);
    
    return layer;
}

CCLabelTTF* AccountManageScene::showServerMessage( string ch )
{
#if 0
    static int index = 0;
    if (index >10)
    {
        index = 0;
    }
    CCLabelTTF* _label = CCLabelTTF::create(ch.c_str(),"", 30);
    _label->setPosition(WINSIZE/2+CCPoint(0,200-index*40));
    _label->runAction(CCSequence::create(CCDelayTime::create(5), CCFadeOut::create(1),CCRemoveSelf::create(true),NULL));
    index++;
#endif
    
}

//修改身份
Layer* AccountManageScene::createChangeRoleLayer(){
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
    auto contentV = Sprite::create("bk_chage_role.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(66,352));
    contentV->setContentSize(Size(508, 510));
    layer->addChild(contentV);
    auto cancelBtn=Button::create();
    cancelBtn->loadTextures("btn_addCase_cancel.png", "btn_addCase_cancel.png");
    cancelBtn->setPosition(Vec2(120, 15));
    cancelBtn->setAnchorPoint(Vec2(0,0));
    cancelBtn->setScale(0.87);
    cancelBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            this->removeChildByTag(2002);
        }
            break;
        default:
            break;
    }
    });
    contentV->addChild(cancelBtn);
    
    //role1
    auto role1Btn=Button::create();
    role1Btn->loadTextures("alpha.png", "alpha.png");
    role1Btn->setPosition(Vec2(visibleSize.width/2, 478));
    role1Btn->setScale9Enabled(true);
    role1Btn->setContentSize(Size(508, 42));
    role1Btn->setTitleText("带组教授");
    role1Btn->setTitleColor(Color3B(40, 40, 40));
    role1Btn->setTitleFontSize(40);
    role1Btn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            roleNum="1";
            createRoleLabel();
            this->removeChildByTag(2002);
        }
        default:
            break;
    }
    });
    layer->addChild(role1Btn);
    
    //role2
    auto role2Btn=Button::create();
    role2Btn->loadTextures("alpha.png", "alpha.png");
    role2Btn->setPosition(Vec2(visibleSize.width/2, 563));
    role2Btn->setScale9Enabled(true);
    role2Btn->setContentSize(Size(508, 42));
    role2Btn->setTitleText("主治医生");
    role2Btn->setTitleColor(Color3B(40, 40, 40));
    role2Btn->setTitleFontSize(40);
    role2Btn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            roleNum="2";
            createRoleLabel();
            this->removeChildByTag(2002);
        }
        default:
            break;
    }
    });
    layer->addChild(role2Btn);
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(visibleSize.width/2, 520));
    lineV->setAnchorPoint(Vec2(0.5, 0));
    lineV->setContentSize(Size(508, 1.5));
    layer->addChild(lineV);
    
    //role3
    auto role3Btn=Button::create();
    role3Btn->loadTextures("alpha.png", "alpha.png");
    role3Btn->setPosition(Vec2(visibleSize.width/2, 648));
    role3Btn->setScale9Enabled(true);
    role3Btn->setContentSize(Size(508, 42));
    role3Btn->setTitleText("住院医生");
    role3Btn->setTitleColor(Color3B(40, 40, 40));
    role3Btn->setTitleFontSize(40);
    role3Btn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            roleNum="3";
            createRoleLabel();
            this->removeChildByTag(2002);
        }
        default:
            break;
    }
    });
    layer->addChild(role3Btn);
    auto lineV2=Sprite::create("userInfo_line.png");
    lineV2->setPosition(Vec2(visibleSize.width/2, 605));
    lineV2->setAnchorPoint(Vec2(0.5, 0));
    lineV2->setContentSize(Size(508, 1.5));
    layer->addChild(lineV2);
    
    //role4
    auto role4Btn=Button::create();
    role4Btn->loadTextures("alpha.png", "alpha.png");
    role4Btn->setPosition(Vec2(visibleSize.width/2, 733));
    role4Btn->setScale9Enabled(true);
    role4Btn->setContentSize(Size(508, 42));
    role4Btn->setTitleText("研究生");
    role4Btn->setTitleColor(Color3B(40, 40, 40));
    role4Btn->setTitleFontSize(40);
    role4Btn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            roleNum="4";
            createRoleLabel();
            this->removeChildByTag(2002);
        }
        default:
            break;
    }
    });
    layer->addChild(role4Btn);
    auto lineV3=Sprite::create("userInfo_line.png");
    lineV3->setPosition(Vec2(visibleSize.width/2, 690));
    lineV3->setAnchorPoint(Vec2(0.5, 0));
    lineV3->setContentSize(Size(508, 1.5));
    layer->addChild(lineV3);

    return layer;
}

void AccountManageScene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
{
    TextField*textField=(TextField*)pSender;
    string  text=textField->getString();
    switch (type){
        case cocos2d::ui::TextField::EventType::INSERT_TEXT:{
            CCLOG("INSERT_TEXT");
        }
            break;
        case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
            CCLOG("DELETE_BACKWARD");
        case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
            CCLOG("DETACH_WITH_IME");
            break;
    }
}
void AccountManageScene::checkBoxCallback(cocos2d::Ref * ref, CheckBox::EventType type)
{
    CheckBox* item = (CheckBox*)ref;
    int tag= item->getTag();
    if (type==cocos2d::ui::CheckBox::EventType::SELECTED) {
        if (tag==10||tag==11) {
            //手势锁
        }
    }
    switch (type)
    {
        case cocos2d::ui::CheckBox::EventType::SELECTED:
            log("SELECTED!");
            if (tag==10||tag==11) {
                //手势锁
                log("手势锁%s",UserDefault::getInstance()->getStringForKey("DrawPassWord").c_str());
                if (tag==10) {
                    UserDefault::getInstance()->setStringForKey("isLock", "1");
//                if (!(UserDefault::getInstance()->getStringForKey("DrawPassWord").length()>0)) {
                    log("第一次设置手势锁");
                    auto drawLineSC=(DrawLineScene*)DrawLineScene::createScene();
                    drawLineSC->type=1;
                    Director::getInstance()->pushScene(drawLineSC);
                }
//                }
            }
            break;
        case cocos2d::ui::CheckBox::EventType::UNSELECTED:{
            UserDefault::getInstance()->setStringForKey("isLock", "0");
            log("UNSELECTED!");
        }
            break;
        default:
            break;
    }
}

#pragma-用于加载网络数据
void AccountManageScene::pushDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    //当type为2时，删除成员
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/getDocterById?userId=%s&doctorId=%s",UserDefault::getInstance()->getStringForKey("userId").c_str(),UserDefault::getInstance()->getStringForKey("id").c_str());
    string memberURL=memberUrl;
    netManeger->sendMessage(memberURL,CC_CALLBACK_2(AccountManageScene::onHttpRequestCompleted, this),nullptr);
}

void AccountManageScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    if (!response)
    {
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    
    // rapidjson::Document Jsondata;
    
    this->infoData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (this->infoData.HasParseError()) {
        
        return;
    }
    if(this->infoData.HasMember("status")){
        if (this->infoData["status"].GetInt()==0) {
            createMainView();
        }
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        infoData.Accept(writer);
        CCLOG("%s", buffer.GetString());
    }
}

#pragma-用于更新网络数据
void AccountManageScene::updateDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    //当type为2时，删除成员
    char memberUrl[500]={0};
    auto passwd=UserDefault::getInstance()->getStringForKey("passwd");
    
    if (surePassword!=nullptr&&passWordIsDestory==1) {
         string pass=surePassword->getText();
#pragma-怎么判断一个对象已经被销毁,我选择设置passWordIsDestory记录，真的坑
        log("%d,%d,%d",pass.size(),surePassword!=nullptr,surePassword!=NULL);
        passwd=pass;
    }
    auto name=UserDefault::getInstance()->getStringForKey("name");
    if (strcmp(textfieldName->getText(), "")!=0 ) {
        name=textfieldName->getText();
    }
    auto role=UserDefault::getInstance()->getStringForKey("role");
    if (roleNum!="") {
        role=roleNum;
    }
    sprintf(memberUrl,"doctorId=%s&name=%s&passwd=%s&role=%d&isLock=%d&isRecieve=%d",UserDefault::getInstance()->getStringForKey("id").c_str(),name.c_str(),passwd.c_str(),atoi(role.c_str()),keyCheckBox->getSelectedState(),keyAccompanyBox->getSelectedState());
    string memberURL="http://czapi.looper.pro/web/updateDoctorInfo";
     char* url=memberUrl;
    
    
    netManeger->sendMessage(memberURL,CC_CALLBACK_2(AccountManageScene::onHttpRequestCompleted2, this),url);
}

void AccountManageScene::onHttpRequestCompleted2(HttpClient* sender, HttpResponse* response)
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    if (!response)
    {
        return;
    }
    if (0 != strlen(response->getHttpRequest()->getTag())) {
        log("%s compeled",response->getHttpRequest()->getTag());
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    
    // rapidjson::Document Jsondata;
    
    this->infoData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (this->infoData.HasParseError()) {
        
        return;
    }
    if(this->infoData.HasMember("status")){
        if (this->infoData["status"].GetInt()==0) {
            log("修改成功");
            bkView->removeAllChildren();
            if (backBtnType==1) {
                backBtnType=0;
                Director::getInstance()->popScene();
            }else{
            pushDataToNetWork();
            }
        }
        
        //        for(int i = 0; i < this->loginData["data"].Size(); i++) {
        //            rapidjson::Value& object = this->loginData["data"];
    }
}


