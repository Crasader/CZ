//
//  WaitChatDetailScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/3.
//

#include "WaitChatDetailScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "SelectStep3Scene.hpp"
#include "SelectStep4Scene.hpp"
#include "NetWrokMangerData.hpp"
#include "UpdateCasePhotoScene.hpp"
#include "ShowImageScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *WaitChatDetailScene::createScene(){
    return WaitChatDetailScene::create();
}
bool WaitChatDetailScene::init(){
    if (!Scene::init()) {
        return false;
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    refuseReason="";
    return true;
};

void WaitChatDetailScene::onEnter()
{
    
    log("%d",type);
    Scene::onEnter();
    this->removeAllChildren();
    rapidjson::Value& data =this->infoData["data"][indexForData];
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    data.Accept(writer);
    CCLOG("%s", buffer.GetString());
    if (data.HasMember("patientId")) {
        UserDefault::getInstance()->setStringForKey("patientId",data["patientId"].GetString());
        getInfoDataToNetWork();
    }else{
        UserDefault::getInstance()->setStringForKey("patientId",data["id"].GetString());
        getInfoDataToNetWork();
    }
    auto visibleSize=Director::getInstance()->getVisibleSize();
    bkView=Sprite::create("bk_chat_userdetail.png");
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
}

void WaitChatDetailScene::createBKView(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(0, 30));
    scrollView->setAnchorPoint(Vec2(0, 0));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);//方向
    scrollView->setScrollBarEnabled(true);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, 950));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 255, 255));//设置背景颜色
    createScrollDetailView(scrollView);
    bkView->addChild(scrollView);
}

void WaitChatDetailScene::createScrollDetailView(ScrollView* superV){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    
    bkViewForPhoto=Sprite::create("alpha.png");
    bkViewForPhoto->setPosition(Vec2(0, 0));
    bkViewForPhoto->setAnchorPoint(Vec2(0, 0));
    bkViewForPhoto->setContentSize(Size(visibleSize.width, 950));
    superV->addChild(bkViewForPhoto);
    
//data
     rapidjson::Value& data =this->infoData["data"][indexForData];
    
    auto headBtn=ImageView::create("bk_headIV.png");
    headBtn->setPosition(Vec2(244, 815));
    headBtn->setAnchorPoint(Vec2(0, 0));
    headBtn->setTouchEnabled(true);
     float height2=headBtn->getContentSize().height;
    headBtn->setScale(151.0/height2);
    bkViewForPhoto->addChild(headBtn);
    headBtn->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
        if (type == Widget::TouchEventType::ENDED){
            log("点击上传头像");
            Layer *layer= createAlbumLayer();
            layer->setTag(200);
            this->addChild(layer);
        }
    });
    string name="";
    if (data["name"].IsNull()) {}else{
        name=data["name"].GetString();
    }
    string caseNo="";
    if (data["caseNo"].IsNull()) {}else{
        caseNo=data["caseNo"].GetString();
    }
    createLabel(Vec2(0, 758), "真实姓名：", name, bkViewForPhoto);
    createLabel(Vec2(0, 678), "病历号：", caseNo, bkViewForPhoto);
    string sex="男";
    if (data["sex"].IsNull()) {
    }else{
        if (strcmp(data["sex"].GetString(),"F")==0||strcmp(data["sex"].GetString(),"女")==0) {  sex="女"; }
    }
    createLabel(Vec2(0, 598), "性别：", sex, bkViewForPhoto);
    
    string age="";
    if (data["age"].IsNull()) {
    }else{
        age=data["age"].GetString();
    }
    createLabel(Vec2(0, 518), "年龄：",age , bkViewForPhoto);
   
    float height=10;
if (type==1) {//通过病人信息的infoData，字段不同，不同的处理
    if (data["step2"].IsNull()) {
        height= createLabel(Vec2(0, 438), "自述症状：", "暂时不清楚", bkViewForPhoto);
    }else{
        log("自述症状%s",data["step2"].GetString());
        height= createLabel(Vec2(0, 438), "自述症状：", data["step2"].GetString(), bkViewForPhoto);
    }
}else{
    if (data["answers"].IsNull()) {
       height= createLabel(Vec2(0, 438), "自述症状：", "暂时不清楚", bkViewForPhoto);
    }else{
        log("自述症状%s",data["answers"].GetString());
       height= createLabel(Vec2(0, 438), "自述症状：", data["answers"].GetString(), bkViewForPhoto);
    }
}
    createLabel(Vec2(0, 400-height), "介绍人：", "无", bkViewForPhoto);
    createLabel(Vec2(0, 320-height), "推荐人：", "无", bkViewForPhoto);
    
    contentHeight=height;
    
}

void WaitChatDetailScene::createPhotoSpriteArr(float height){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    auto imageLB = Label::createWithSystemFont("影像：","fonts/Marker Felt.ttf",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    imageLB->setPosition(Point(56,240-height));
    imageLB->setTextColor(Color4B(91,144,230, 255));
    imageLB->setAnchorPoint(Vec2(0, 0));
    bkViewForPhoto->addChild(imageLB);
    float currentHeight=0;
    for (int i=0; i<videoArr.size(); i++) {
        if (i==videoArr.size()-1) {
            auto imageBtn1=ImageView::create("btn_chat_userImage.png");
            int width=154+150*i+125;
            if (width<visibleSize.width) {
                imageBtn1->setPosition(Vec2(154+150*i, 160-height+10));
            }else{
                imageBtn1->setPosition(Vec2(154+150*(i%3), 160-height-(int)((width-154)/(visibleSize.width-154))*150+10));
            }
            imageBtn1->setAnchorPoint(Vec2(0, 0));
            imageBtn1->setTouchEnabled(true);
            imageBtn1->setScale(0.87);
            bkViewForPhoto->addChild(imageBtn1);
            imageBtn1->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
                if (type == Widget::TouchEventType::ENDED){
#pragma-上传自述病例的影像
                    char positiveUrl[1000]={0};//正面   type=1则住院病历 type=2则自述病例
                    
                   if ( infoData["data"][indexForData].HasMember("patientId")) {
                    sprintf(positiveUrl,"http://czapi.looper.pro/web/file.php?cid=%s&type=2",infoData["data"][indexForData]["patientId"].GetString());
                   }else{
                       sprintf(positiveUrl,"http://czapi.looper.pro/web/file.php?cid=%s&type=2",infoData["data"][indexForData]["id"].GetString());
                   }
                    string url=positiveUrl;
                    auto   updateSC=(UpdateCasePhotoScene*)UpdateCasePhotoScene::createScene();
                    updateSC->webURL=url;
                    Director::getInstance()->pushScene(updateSC);
                }
            });
            currentHeight=975-(160-height-(int)((width-154)/(visibleSize.width-154))*150);
        }else{
            char tagStr[50];
            sprintf(tagStr,"medicalImage%s_%d.png",userData["data"]["id"].GetString(),i);
            string path=FileUtils::getInstance()->getWritablePath()+tagStr;
            auto imageBtn1=ImageView::create(path.c_str());
            int width=154+150*i+125;
            if (width<visibleSize.width) {
                imageBtn1->setPosition(Vec2(154+150*i, 160-height));
                //                 log("width:%d,height:%f i的值%d,屏幕宽度%f",154+150*(i%3),320-height-(int)(width/(int)visibleSize.width)*150,i,visibleSize.width);
            }else{
                imageBtn1->setPosition(Vec2(154+150*(i%3), 160-height-(int)((width-154)/(visibleSize.width-154))*150));
                //                log("width:%d,height:%f i的值%d,总长度:%d",154+150*(i%3),320-height-(int)((width-154)/(visibleSize.width-154))*150,i,width);
            }
            imageBtn1->setAnchorPoint(Vec2(0, 0));
            imageBtn1->setTouchEnabled(true);
            float height3=imageBtn1->getContentSize().height;
            float width3=imageBtn1->getContentSize().width;
            imageBtn1->setScaleX(115.0/width3);
            imageBtn1->setScaleY(140.0/height3);
            bkViewForPhoto->addChild(imageBtn1);
            imageBtn1->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
                if (type == Widget::TouchEventType::ENDED){
                    auto btn=(ImageView *)pSender;
#pragma-查看照片
                    auto showSC=(ShowImageScene*)ShowImageScene::createScene();
                    char tagStr[50];
                    sprintf(tagStr,"medicalImage%d_%d.png",atoi(userData["data"]["id"].GetString()),btn->getTag());
                    showSC->imagePath=tagStr;
                    Director::getInstance()->pushScene(showSC);
                }
            });
        }
    }
    if (type==1) {
        scrollView->setInnerContainerSize(Size(visibleSize.width, currentHeight+30));
        if (scrollView->getInnerContainerSize().height>950) {
            bkViewForPhoto->setPosition(Vec2(0, currentHeight-960));
        }else{ bkViewForPhoto->setPosition(Vec2(0, -20));}
    }else if(type==2){
        scrollView->setInnerContainerSize(Size(visibleSize.width, currentHeight+210));
        bkViewForPhoto->setPosition(Vec2(0, currentHeight-960+185));
        auto acceptBtn=Button::create();
        acceptBtn->loadTextures("btn_wait_accept.png", "btn_wait_accept.png");
        acceptBtn->setPosition(Vec2(188, 105-bkViewForPhoto->getPosition().y));
        acceptBtn->setAnchorPoint(Vec2(0, 0));
        acceptBtn->setScale(0.87);
        acceptBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
            case ui::Widget::TouchEventType::BEGAN: break;
            case ui::Widget::TouchEventType::ENDED:{
                auto layer=createPromptLayer("确认接诊该病人？");
                layer->setTag(2001);
                this->addChild(layer);
            }
            default:
                break;
        }
        });
        bkViewForPhoto->addChild(acceptBtn);
        
        auto recommendBtn=Button::create();
        recommendBtn->loadTextures("btn_waitDetail_recommend.png", "btn_waitDetail_recommend.png");
        recommendBtn->setPosition(Vec2(188, 10-bkViewForPhoto->getPosition().y));
        recommendBtn->setScale(0.87);
        recommendBtn->setAnchorPoint(Vec2(0, 0));
        recommendBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
            case ui::Widget::TouchEventType::BEGAN: break;
            case ui::Widget::TouchEventType::ENDED:{
                log("推荐给别人");
                auto select4SC=(SelectStep4Scene*)SelectStep4Scene::createScene();
                select4SC->commandType=2;
                Director::getInstance()->pushScene(select4SC);
            }
            default:
                break;
        }
        });
        bkViewForPhoto->addChild(recommendBtn);
        
        auto refuseBtn=Button::create();
        refuseBtn->loadTextures("btn_wait_accept_refuse.png", "btn_wait_accept_refuse.png");
        refuseBtn->setPosition(Vec2(visibleSize.width-100, visibleSize.height-85));
        refuseBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
            case ui::Widget::TouchEventType::BEGAN: break;
            case ui::Widget::TouchEventType::ENDED:{
                auto layer=createRefuseLayer();
                layer->setTag(2002);
                this->addChild(layer);
            }
                
            default:
                break;
        }
        });
        this->addChild(refuseBtn);
        
    }else if(type==3){
        scrollView->setInnerContainerSize(Size(visibleSize.width, currentHeight+210));
        bkViewForPhoto->setPosition(Vec2(0, currentHeight-960+185));
        auto acceptBtn=Button::create();
        acceptBtn->loadTextures("btn_accept_again.png", "btn_accept_again.png");
        acceptBtn->setPosition(Vec2(188, 105-bkViewForPhoto->getPosition().y));
        acceptBtn->setAnchorPoint(Vec2(0, 0));
        acceptBtn->setScale(0.87);
        acceptBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
            case ui::Widget::TouchEventType::BEGAN: break;
            case ui::Widget::TouchEventType::ENDED:{
                auto layer=createPromptLayer("确认重新接诊该病人？");
                layer->setTag(2001);
                this->addChild(layer);
            }
            default:
                break;
        }
        });
        bkViewForPhoto->addChild(acceptBtn);
        
        auto recommendBtn=Button::create();
        recommendBtn->loadTextures("btn_waitDetail_recommend.png", "btn_waitDetail_recommend.png");
        recommendBtn->setPosition(Vec2(188, 10-bkViewForPhoto->getPosition().y));
        recommendBtn->setScale(0.87);
        recommendBtn->setAnchorPoint(Vec2(0, 0));
        recommendBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
            case ui::Widget::TouchEventType::BEGAN: break;
            case ui::Widget::TouchEventType::ENDED:{
                auto select4SC=(SelectStep4Scene*)SelectStep4Scene::createScene();
                select4SC->commandType=2;
                Director::getInstance()->pushScene(select4SC);
                log("推荐给别人");
            }
            default:
                break;
        }
        });
        bkViewForPhoto->addChild(recommendBtn);
    }
}

Layer* WaitChatDetailScene::createRefuseLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(0, 0, 0, 255));
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
    auto contentV = Sprite::create("bk_refuse_layer.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(0,0));
    contentV->setContentSize(visibleSize);
    layer->addChild(contentV);
    
    auto backBtn=Button::create();
    backBtn->loadTextures("btn_register_return.png", "btn_register_return.png");
    backBtn->setPosition(Vec2(80, visibleSize.height-85));
    backBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
            this->removeChildByTag(2002);
        default:
            break;
    }
    });
    contentV->addChild(backBtn);
    auto nameLB = Label::createWithSystemFont("请填写拒绝理由：","fonts/Marker Felt.ttf",40,Size(400,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    nameLB->setPosition(Point(39,923));
    nameLB->setTextColor(Color4B(0,0,0, 220));
    nameLB->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(nameLB);
    
    auto textFieldBottom=Sprite::create("textfield_bottom.png");
    textFieldBottom->setPosition(Vec2(23, 623));
    textFieldBottom->setAnchorPoint(Vec2(0, 0));
    textFieldBottom->setScale(0.87);
    contentV->addChild(textFieldBottom);
    
    auto textFieldCenter=Sprite::create("textfield_center.png");
    textFieldCenter->setPosition(Vec2(23, 623+textFieldBottom->getContentSize().height*0.87));
    textFieldCenter->setScale(0.87);
    textFieldCenter->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(textFieldCenter);
    
    auto textFieldTop=Sprite::create("textfield_top.png");
    textFieldTop->setPosition(Vec2(23, textFieldCenter->getContentSize().height*0.87+textFieldCenter->getPosition().y));
    textFieldTop->setScale(0.87);
    textFieldTop->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(textFieldTop);
    
    
    auto   textFieldContent = EditBox::create(Size(visibleSize.width-80,300), Scale9Sprite::create("alpha.png"));
    textFieldContent->setTextHorizontalAlignment(TextHAlignment::LEFT);
    textFieldContent->setAnchorPoint(Vec2(0, 0));
    textFieldContent->setPosition(Vec2(45,605));
    textFieldContent->setFontName("Arial");
    textFieldContent->setFontSize(35);
    textFieldContent->setPlaceholderFontSize(35);
    textFieldContent->setFontColor(Color3B::BLACK);
    textFieldContent->setPlaceHolder("一百字以内");
    textFieldContent->setPlaceholderFontColor(Color3B(240, 240, 240));
    textFieldContent->setReturnType(EditBox::KeyboardReturnType::DONE);
    textFieldContent->setMaxLength(100);
    textFieldContent->setInputMode(cocos2d::ui::EditBox::InputMode::ANY);//可以输入任何，但是不包括换行
    contentV->addChild(textFieldContent);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_step2_sure.png", "btn_step2_sure.png");
    sureBtn->setPosition(Vec2(185, 500));
    sureBtn->setScale(0.87);
    sureBtn->setAnchorPoint(Vec2(0, 0));
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:{
            this->removeChildByTag(2002);
            log("替换成拒绝列表,同时请求数据");
            pushDataToNetWork("refused");
        }
        default:
            break;
    }
    });
    contentV->addChild(sureBtn);
    
    return layer;
}



Layer* WaitChatDetailScene::createAlbumLayer(){
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

Layer* WaitChatDetailScene::createUpdateImageLayer(){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
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
    
    
    auto bkView=Sprite::create("bk_updateImageLayer.png");
    bkView->setPosition(0,0);
    bkView->setAnchorPoint(Vec2(0, 0));
    bkView->setContentSize(Size(visibleSize.width, visibleSize.height));
    layer->addChild(bkView);
    
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
    
    auto updateBtn=Button::create();
    updateBtn->loadTextures("btn_updateImage.png", "btn_updateImage.png");
    updateBtn->setPosition(Vec2(visibleSize.width/2, 486));
    updateBtn->setScale(0.87);
    updateBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            auto step3SC=SelectStep3Scene::create();
            Director::getInstance()->pushScene(step3SC);
        }
            
        default:
            break;
    }
    });
    bkView->addChild(updateBtn);
    
    return layer;
    
}

float WaitChatDetailScene::createLabel(Vec2 point,string name1,string name2,Sprite* superV){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    auto nameLB = Label::createWithSystemFont(name1,"fonts/Marker Felt.ttf",35,Size(200,50),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
    nameLB->setPosition(Point(56,point.y));
    nameLB->setTextColor(Color4B(91,144,230, 255));
    nameLB->setAnchorPoint(Vec2(0, 0));
    superV->addChild(nameLB);
    
    auto nameLB2 = Label::createWithSystemFont(name2,"Arial",35,Size(visibleSize.width-265,0),TextHAlignment::RIGHT,TextVAlignment::BOTTOM);
    float height=nameLB2->getContentSize().height;
    nameLB2->setPosition(Point(218,point.y+41-height));
    nameLB2->setTextColor(Color4B(0,0,0, 255/3*2));
    nameLB2->setAnchorPoint(Vec2(0, 0));
    superV->addChild(nameLB2);
    
    return height;
}



cocos2d::Layer* WaitChatDetailScene::createPromptLayer(std::string content){
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
    auto contentV = Sprite::create("bk_wait_accept.png");
    contentV->setAnchorPoint(Vec2(0,0));
    contentV->setPosition(Vec2(66,431));
    contentV->setContentSize(Size(508,349));
    layer->addChild(contentV);
    
    auto sureBtn=Button::create();
    sureBtn->loadTextures("btn_sureExit_sure.png", "btn_sureExit_sure.png");
    sureBtn->setPosition(Vec2(120, 15));
    sureBtn->setAnchorPoint(Vec2(0,0));
    sureBtn->setScale(0.87);
    sureBtn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){ switch (type){
        case ui::Widget::TouchEventType::BEGAN: break;
        case ui::Widget::TouchEventType::ENDED:
        {
            pushDataToNetWork("accepted");
            this->removeChildByTag(2001);
            log("确认接诊");
            break;
        }
        default:
            break;
    }
    });
    contentV->addChild(sureBtn);
    
    auto deleteBtn=Button::create();
    deleteBtn->loadTextures("btn_QRCode_close.png", "btn_QRCode_close.png");
    deleteBtn->setPosition(Vec2(450, 290));
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
    
    auto contentLB=Label::createWithSystemFont(content,"Arial",36,Size(contentV->getContentSize().width-40,120),TextHAlignment::CENTER,TextVAlignment::CENTER);
    contentLB->setPosition(Vec2(20,120));
    contentLB->setTextColor(Color4B(0, 0, 0, 255/3*2));
    contentLB->setAnchorPoint(Vec2(0, 0));
    contentV->addChild(contentLB);
    
    return layer;
}

void WaitChatDetailScene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
{
     TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
    switch (type){
            
        case cocos2d::ui::TextField::EventType::INSERT_TEXT:
            refuseReason=textField->getString();
            log("%s",textField->getString().c_str());
            break;
        case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
            refuseReason=textField->getString();
            log("%s",textField->getString().c_str());
            break;
        case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
//            CCLOG("DETACH_WITH_IME");
            
            break;
    }
}

void WaitChatDetailScene::getInfoDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/getUserById?patientId=%s",UserDefault::getInstance()->getStringForKey("patientId").c_str());
    string memberURL=memberUrl;
    netManeger->sendMessage(memberURL,CC_CALLBACK_2(WaitChatDetailScene::onHttpRequestCompleted2, this),nullptr);
}
void WaitChatDetailScene::onHttpRequestCompleted2(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    if (!response)
    {
        return;
    }
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    userData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    if (userData.HasParseError()) {
        return;
    }
    if(userData.HasMember("status")){
        if (userData["status"].GetInt()==0) {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            userData.Accept(writer);
            CCLOG("userData:%s", buffer.GetString());
#pragma-将影像图片存入数组
            createBKView();
           if (!userData["data"]["picURL"].IsNull()){
          videoArr.clear();
            string imageURL=userData["data"]["picURL"].GetString();
#pragma-截取字符串
         string currentStr="";
            for(int i =0; i < imageURL.length(); i++){
                if(imageURL.at(i) == ','){
                    log("%s",currentStr.c_str());
                    videoArr.push_back(cocos2d::Value(currentStr));
                    currentStr="";
                }else{
                    currentStr+=imageURL.at(i);
                    if( i==imageURL.length()-1){
                        videoArr.push_back(cocos2d::Value(currentStr));
                        log("%s",currentStr.c_str());
                    }
                }
            }
#pragma-释放内存
            for (int i=0; i<videoArr.size(); i++) {
                char tagStr[50];
                sprintf(tagStr,"medicalImage%s_%d.png",userData["data"]["id"].GetString(),i);
                string path=FileUtils::getInstance()->getWritablePath()+tagStr;
                FileUtils::getInstance()->removeFile(path);
            }
            //加载网络图片
            getImageFromNetWork(videoArr.at(0).asString(),0);
           }else{
               videoArr.push_back(cocos2d::Value("btn_chat_userImage.png"));
               createPhotoSpriteArr(contentHeight);
           }
        }
    }
}


void WaitChatDetailScene::getImageFromNetWork(std::string url,int photoTag){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    netManeger->tag=to_string(photoTag);
    netManeger->upLoadData(url.c_str(),CC_CALLBACK_2(WaitChatDetailScene::onHttpRequestImageCompleted, this),nullptr);
}
void WaitChatDetailScene::onHttpRequestImageCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response)
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    char tagStr[50];
    if (!response)
    {
        return;
    }
    const char* tag  =  response->getHttpRequest()->getTag();
    if (0 != strlen(tag)&&videoArr.size()!=0)
    {
        log("%s completed", response->getHttpRequest()->getTag());
        sprintf(tagStr,"medicalImage%s_%d.png",userData["data"]["id"].GetString(),atoi(tag));
        std::vector<char> *data = response->getResponseData();
        //加载到本地
        char * buf=(char *)malloc(data->size());
        std::copy(data->begin(),data->end(),buf);    //vector<char>*  ->char*
        std::string sFileName=tagStr;
        std::string path = FileUtils::getInstance()->getWritablePath()+sFileName;
        FILE *fp=fopen(path.c_str(),"wb+");//读写打开或建立一个二进制文件，允许读和写
        fwrite(buf,1,data->size(),fp);
        fclose(fp);
        if (atoi(tag)==videoArr.size()-1) {
          createPhotoSpriteArr(contentHeight);
        }else{
            getImageFromNetWork(videoArr.at(atoi(tag)+1).asString(),atoi(tag)+1);
        }
    }
}   
 

#pragma-用于加载网络数据处理门诊申请
void WaitChatDetailScene::pushDataToNetWork(string applicationType){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
     rapidjson::Value& data =this->infoData["data"][indexForData];
    char memberUrl[1000]={0};
sprintf(memberUrl,"requestId=%d&type=%s&refuseReason=%s",atoi(data["requestId"].GetString()),applicationType.c_str(),refuseReason.c_str());
    char* url=memberUrl;
    string memberURL="http://czapi.looper.pro/web/updateOutpatient";
    netManeger->postHttpRequest(memberURL,CC_CALLBACK_2(WaitChatDetailScene::onHttpRequestCompleted, this),url);
}

void WaitChatDetailScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
    
    this->networkData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (this->networkData.HasParseError()) {
        
        return;
    }
    if(this->networkData.HasMember("status")){
        if (this->networkData["status"].GetInt()==0) {
            auto chatSC=(WaitChatDetailScene*)WaitChatDetailScene::createScene();
            chatSC->type=3;
            chatSC->indexForData=indexForData;
            
            chatSC->infoData.SetObject();
            rapidjson::Document::AllocatorType& allocator = chatSC->infoData.GetAllocator();
            rapidjson::Value array(rapidjson::kArrayType);
            array=this->infoData["data"];
            chatSC->infoData.AddMember("data", array, allocator);
            
            this->removeChildByTag(2002);
            Director::getInstance()->replaceScene(chatSC);
            Director::getInstance()->popScene();
        }
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        networkData.Accept(writer);
        CCLOG("%s", buffer.GetString());
    }
}
