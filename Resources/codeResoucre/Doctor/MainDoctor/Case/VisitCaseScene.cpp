//
//  VisitCaseScene.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/1/10.
//

#include "VisitCaseScene.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "MarkScene.hpp"
#include "DocUserInfoScene.hpp"
#include "ImpressionScene.hpp"
#include "TreatScene.hpp"
#include "NetWrokMangerData.hpp"
#include "UpdateCasePhotoScene.hpp"
#include "ShowImageScene.hpp"
using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;
Scene *VisitCaseScene::createScene(){
    return VisitCaseScene::create();
}
bool VisitCaseScene::init(){
    if (!Scene::init()) {
        return false;
    }
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto bkView=Sprite::create("bk_visit_case.png");
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
    
    lv = ListView::create();
    lv->setDirection(ui::ScrollView::Direction::VERTICAL);//设置方向为垂直方向
    lv->setBounceEnabled(true);
    lv->setBackGroundImage("alpha.png");//设置图片为九宫格格式。其实就和9图一个意思。只是安卓中要自己制作。这里程序会帮你生成
    lv->setBackGroundImageScale9Enabled(true);
    lv->setContentSize(Size(visibleSize.width-40, visibleSize.height-190));
    lv->setAnchorPoint(Point(0,0));
    lv->setPosition(Point(20,40));
    lv->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(VisitCaseScene::selectedItemEvent, this));//添加监听函数
    lv->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(VisitCaseScene::selectedItemEventScrollView, this));
    this->addChild(lv);
    return true;
}

void VisitCaseScene::onEnter(){
    Scene::onEnter();
    Size visibleSize=Director::getInstance()->getVisibleSize();
    lv->removeAllItems();
    auto layer1 = createMessageLayout(0,"张牧之   男  60       856","");
    lv->insertCustomItem(layer1,0);
    auto layer2 = createMessageLayout(1,"印象","");
    lv->insertCustomItem(layer2,1);
    auto layer3 = createMessageLayout(2,"影像","");
    lv->insertCustomItem(layer3,2);
    auto layer4 = createMessageLayout(3,"评分","");
    lv->insertCustomItem(layer4,3);
    auto layer5 = createMessageLayout(4,"治疗方式","");
    lv->insertCustomItem(layer5,4);
    
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    layout->setTouchEnabled(true);
    auto textFieldTop=Sprite::create("textfield_top.png");
    textFieldTop->setPosition(Vec2(0,0));
    textFieldTop->setContentSize(Size(visibleSize.width-40, 30));
    textFieldTop->setAnchorPoint(Vec2(0, 0));
    layout->addChild(textFieldTop);
    auto titleLB = Label::createWithSystemFont("说明","Arial",38,Size(300,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    titleLB->setPosition(Point(37,10+textFieldTop->getContentSize().height));
    titleLB->setTextColor(Color4B(91, 144, 229, 255));
    titleLB->setAnchorPoint(Vec2(0, 0));
    layout->addChild(titleLB);
    layout->setContentSize(Size(visibleSize.width, textFieldTop->getContentSize().height+70));
    lv->insertCustomItem(layout,5);
    
    auto layout2 = Layout::create();
    layout2->setBackGroundImageScale9Enabled(true);
    layout2->setBackGroundImage("textfield_center.png");
    layout2->setTouchEnabled(true);
    
    auto textFieldContent = EditBox::create(Size(visibleSize.width-80,300), Scale9Sprite::create("alpha.png"));
    textFieldContent->setTextHorizontalAlignment(TextHAlignment::LEFT);
    textFieldContent->setAnchorPoint(Vec2(0, 0));
    textFieldContent->setPosition(Vec2(20,0));
    textFieldContent->setFontName("Arial");
    textFieldContent->setFontSize(35);
    textFieldContent->setPlaceholderFontSize(35);
    textFieldContent->setFontColor(Color3B::BLACK);
    textFieldContent->setPlaceHolder("100字以内");
    textFieldContent->setPlaceholderFontColor(Color3B(240, 240, 240));
    textFieldContent->setTag(110);
    textFieldContent->setMaxLength(100);
    textFieldContent->setReturnType(EditBox::KeyboardReturnType::DONE);
    textFieldContent->setInputMode(cocos2d::ui::EditBox::InputMode::ANY);//可以输入任何，但是不包括换行
    layout2->addChild(textFieldContent);
 /*   auto textFieldContent= TextField::create("一百字以内","Arial",35);
    textFieldContent->setMaxLength(240);
    //用于多行输入
    textFieldContent->ignoreContentAdaptWithSize(false);
    textFieldContent->setTouchSize(Size(visibleSize.width-80,300));
    textFieldContent->setPosition(Vec2(20,0));
    textFieldContent->setAnchorPoint(Vec2(0,0));
    textFieldContent->setContentSize(Size(visibleSize.width-80,300));
    textFieldContent->setTextColor(Color4B::BLACK);
    textFieldContent->setPlaceHolderColor(Color4B::GRAY);
    textFieldContent->setTextHorizontalAlignment(TextHAlignment::LEFT);
    textFieldContent->setTag(110);
    textFieldContent->addEventListener(CC_CALLBACK_2(VisitCaseScene::eventCallBack, this));
    layout2->addChild(textFieldContent);   */
    layout2->setContentSize(Size(visibleSize.width-40, 300));
    lv->insertCustomItem(layout2,6);
    
    auto layout3 = Layout::create();
    layout3->setBackGroundImageScale9Enabled(true);
    layout3->setBackGroundImage("alpha.png");
    layout3->setTouchEnabled(true);
    auto textFieldBottom=Sprite::create("textfield_bottom.png");
    textFieldBottom->setPosition(Vec2(0, 0));
    textFieldBottom->setAnchorPoint(Vec2(0, 0));
    textFieldBottom->setContentSize(Size(visibleSize.width-40, 30));
    layout3->addChild(textFieldBottom);
    layout3->setContentSize(Size(visibleSize.width, textFieldBottom->getContentSize().height));
    lv->insertCustomItem(layout3,7);
    getCaseInfoToNetWork();
    getUserDataToNetWork();
    
}
void VisitCaseScene::createTextFieldView(Layout* contentV){
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto textFieldBottom=Sprite::create("textfield_bottom.png");
    textFieldBottom->setPosition(Vec2(23, 0));
    textFieldBottom->setAnchorPoint(Vec2(0, 0));
    textFieldBottom->setScale(0.87);
    contentV->addChild(textFieldBottom);
}


Layout *VisitCaseScene::createMessageLayout(int i,string title,string content){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    //Data
    auto layout = Layout::create();
    layout->setBackGroundImageScale9Enabled(true);
    layout->setBackGroundImage("alpha.png");
    layout->setTouchEnabled(true);
    layout->setTag(i);
    
    float height=10;
    if (content.c_str()!=nullptr) {
        auto contentLB = Label::createWithSystemFont(content,"Arial",35,Size(visibleSize.width-150,0),TextHAlignment::LEFT,TextVAlignment::BOTTOM);
        height=contentLB->getContentSize().height+10;
        contentLB->setPosition(Point(37,10));
        contentLB->setTextColor(Color4B(0,0,0, 255/3*2));
        contentLB->setAnchorPoint(Vec2(0, 0));
        layout->addChild(contentLB);
    }
    if (i==2) {
        //影像
        height=createVideoLayerForListView(20, layout);
    }
    
    auto titleLB = Label::createWithSystemFont(title,"Arial",38,Size(visibleSize.width-150,50),TextHAlignment::LEFT,TextVAlignment::TOP);
    titleLB->setPosition(Point(37,height));
    titleLB->setTextColor(Color4B(91, 144, 229, 255));
    titleLB->setAnchorPoint(Vec2(0, 0));
    layout->addChild(titleLB);
    
    auto lineV=Sprite::create("userInfo_line.png");
    lineV->setPosition(Vec2(30, 0));
    lineV->setAnchorPoint(Vec2(0, 0));
    lineV->setContentSize(Size(visibleSize.width-100, 1.5));
    layout->addChild(lineV);
    //必须执行一下允许点击
    layout->setTouchEnabled(true);
    layout->setContentSize(Size(visibleSize.width, height+70));
    
    auto judgeBtn=Sprite::create("btn_doctor_judge.png");
    judgeBtn->setAnchorPoint(Vec2(0, 0));
    judgeBtn->setPosition(Vec2(visibleSize.width-90, height+10));
    layout->addChild(judgeBtn);
    
    
    return layout;
}


ScrollView* VisitCaseScene::createImageScroll(Vec2 origin,Size visibleSize){
    auto scrollView=cocos2d::ui::ScrollView::create();
    scrollView->setPosition(Vec2(origin.x, origin.y));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);//方向
    scrollView->setScrollBarEnabled(false);//是否显示滚动条
    scrollView->setContentSize(Size(visibleSize.width, visibleSize.height));//设置窗口大小
    scrollView->setBackGroundColor(Color3B(255, 0, 255));//设置背景颜色
    
    for (int i=0; i<10; i++) {
#pragma-修改影像的图片
        auto imageV1=Sprite::create("HelloWorld.png");
        imageV1->setPosition(Vec2((visibleSize.height+20)*i, 0));
        imageV1->setAnchorPoint(Vec2(0, 0));
        imageV1->setContentSize(Size(visibleSize.height, visibleSize.height));
        scrollView->addChild(imageV1);
    }
    scrollView->setInnerContainerSize(Size((visibleSize.height+20)*10, visibleSize.height));
    
    return scrollView;
}

void VisitCaseScene::selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type)
{
    switch (type)
    {
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child start index = %ld", listView->getCurSelectedIndex());
            break;
        }
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child end index = %ld", listView->getCurSelectedIndex());
            long index=listView->getCurSelectedIndex();
            if (dataIsFalse!=1) {
            if (index==3) {//评分
                auto markSC=MarkScene::createScene();
                Director::getInstance()->pushScene(markSC);
            }else if(index==0){
                auto SC=DocUserInfoScene::createScene();
                Director::getInstance()->pushScene(SC);
            }else if(index==1){
                auto SC=ImpressionScene::createScene();
                Director::getInstance()->pushScene(SC);
            }else if(index==4){
                auto SC=TreatScene::createScene();
                Director::getInstance()->pushScene(SC);
            }
            
            break;
        }
        }
        default:
            break;
    }
}
void VisitCaseScene::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
{
    switch (type) {
        case ui::ScrollView::EventType::SCROLL_TO_BOTTOM://滑动到底部
            CCLOG("SCROLL_TO_BOTTOM");
            break;
        case ui::ScrollView::EventType::SCROLL_TO_TOP://滑动到头部
            CCLOG("SCROLL_TO_TOP");
            break;
        default:
            break;
    }
}
void VisitCaseScene::eventCallBack(Ref* pSender,cocos2d::ui::TextField::EventType type)
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    TextField*textField=(TextField*)pSender;
    string  text=textField->getString();
    Size size=calculateFontSize(text.c_str());
    switch (type){
        case cocos2d::ui::TextField::EventType::INSERT_TEXT:{
            CCLOG("INSERT_TEXT");
            if (size.height>=300) {
#pragma-调整输入框的高度
            Layout*  layout=(Layout*)lv->getItem(6);
                layout->setContentSize(Size(visibleSize.width-40, size.height));
               textField->setContentSize(Size(visibleSize.width-80,size.height));
                onEnter();
            }
        }
            break;
        case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
            CCLOG("DELETE_BACKWARD");
        case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
            CCLOG("DETACH_WITH_IME");
            
            break;
    }
}
Size VisitCaseScene::calculateFontSize(const char *str )
{
    auto visibleSize=Director::getInstance()->getVisibleSize();
    std::string tempString = str;
    log("tempString = %s",tempString.c_str());
    size_t computeCount = tempString.size();       //如果字符串很长每次抽取100个字符来计算size；
    Size size = Size(0,0);
    for (int i = 0; i<computeCount ;)  
    {
        std::string substring =  tempString.substr(i,1);
        if ((substring.c_str()[0] & 0x80 )!=0) //是汉字
        {
            substring = tempString.substr(i , 3);
            i += 3;
        }
        else
        {
            i++;
        }
        //CCLog("subString  = %s ",substring.c_str());
        auto tempLabel = LabelTTF::create(substring.c_str(),"",25);
        tempLabel->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
        Size tmpLsize = tempLabel->getContentSize();
        size.width+=tmpLsize.width;
    }
    
    float fHeight= 0;
    float chartWidth=visibleSize.width-80;
    if( size.width > chartWidth)//大于容器的宽度
    {
        fHeight = (size.width / 200 );//计算需要多少行
    }
    int nHeight =  ceil(fHeight);
    
    if (nHeight == 0)
    {
        nHeight = 1;
    }
    
    Size labelSize ;
    if (size.width < chartWidth)
    {
        labelSize = Size(size.width,nHeight*32);//计算容器的Size
    }
    else
    {
        labelSize = Size(chartWidth,nHeight*28);
    }
    
    //CCLog("labelSize = (%f, %f)",labelSize.width ,labelSize.height);
    //CCLog("fHeight = %f  nHeight = %d " ,fHeight ,nHeight);
    return labelSize;
}


#pragma-个人资料界面
void VisitCaseScene::getUserDataToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    //当type为2时，删除成员
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/getUserById?patientId=%s",UserDefault::getInstance()->getStringForKey("patientId").c_str());
    string memberURL=memberUrl;
    netManeger->sendMessage(memberURL,CC_CALLBACK_2(VisitCaseScene::onHttpRequestCompleted2, this),nullptr);
}

void VisitCaseScene::onHttpRequestCompleted2(HttpClient* sender, HttpResponse* response)
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
    userData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    if (this->userData.HasParseError()) {
        return;
    }
    if(this->userData.HasMember("status")){
        if (this->userData["status"].GetInt()==0) {
            rapidjson::Value& object = userData["data"];
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            userData.Accept(writer);
            CCLOG("病人个人资料：  %s", buffer.GetString());
            string name="";
            if (!object["name"].IsNull()) {
                name=object["name"].GetString();
            }
            string contentStr="男";
            if (!object["sex"].IsNull()) {
                if (strcmp(object["sex"].GetString(), "F")==0) {contentStr="女";}
            }
            if (!object["age"].IsNull()) {
                contentStr.append("  ");
                contentStr.append(object["age"].GetString());
            }
            if (!object["caseNo"].IsNull()) {
                contentStr.append("  ");
                contentStr.append(object["caseNo"].GetString());
            }
            lv->removeChildByTag(0);
            auto layer1 = createMessageLayout(0,name,contentStr);
            lv->insertCustomItem(layer1,0);
        }
    }
}


#pragma-网络数据
void VisitCaseScene::getCaseInfoToNetWork(){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    char memberUrl[500]={0};
    sprintf(memberUrl,"http://czapi.looper.pro/web/getCaseById?caseId=%s",UserDefault::getInstance()->getStringForKey("caseId").c_str());
    netManeger->postHttpRequest(memberUrl,CC_CALLBACK_2(VisitCaseScene::onHttpRequestCompleted, this),nullptr);
}

void VisitCaseScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
    
    // rapidjson::Document Jsondata;
    
    this->infoData.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (this->infoData.HasParseError()) {
        
        return;
    }
    if(this->infoData.HasMember("status")){
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        infoData.Accept(writer);
        CCLOG("%s", buffer.GetString());
        
        if (infoData["data"]==false) {
            log("错误数据");
            dataIsFalse=1;
        }else{
            dataIsFalse=0;
        if (this->infoData["status"].GetInt()==0) {
            if(infoData["data"].HasMember("yx_tb")){
                const rapidjson::Value& val_form = infoData["data"];
                if(val_form.IsObject()){
                    string content="";
                    if (!val_form["yx_tb"].IsNull()) {
                        log("   yx_tb: %s", val_form["yx_tb"].GetString());
                        impressData.Parse<rapidjson::kParseDefaultFlags>(val_form["yx_tb"].GetString());
                        content=searchContentForInfoData(content, "退变（",impressData);        //遍历数据
                    }
                    if (!val_form["yx_jx"].IsNull()) {
                        formationData.Parse<rapidjson::kParseDefaultFlags>(val_form["yx_jx"].GetString());
                        content=searchContentForInfoData(content, "畸形（",formationData);
                    }
                    if (!val_form["yx_gr"].IsNull()) {
                        infectData.Parse<rapidjson::kParseDefaultFlags>(val_form["yx_gr"].GetString());
                        content=searchContentForInfoData(content, "感染（",infectData);
                    }
                    if (!val_form["yx_ws"].IsNull()) {
                        injuryData.Parse<rapidjson::kParseDefaultFlags>(val_form["yx_ws"].GetString());
                        content=searchContentForInfoData(content, "外伤（",injuryData);
                    }
                    lv->removeChildByTag(1);
                    auto layer3 = createMessageLayout(1,"印象",content);
                    lv->insertCustomItem(layer3,1);
                    
#pragma-将影像图片存入数组
                    videoArr.clear();
                    string imageURL="http://czapi.looper.pro/web/data/13bad01452b34b43995cc7d4bf8266d2.png";
                    if (!val_form["picUrl"].IsNull()) {
                        imageURL=val_form["picUrl"].GetString();
                    }
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
                        sprintf(tagStr,"medicalImage%d_%d.png",atoi(infoData["data"]["id"].GetString()),i);
                        string path=FileUtils::getInstance()->getWritablePath()+tagStr;
                        FileUtils::getInstance()->removeFile(path);
                    }
                    //加载网络图片
                    getImageFromNetWork(videoArr.at(0).asString(),0);
                }
            }
        }
      }
    }
}

#pragma-获取网络图片
void VisitCaseScene::getImageFromNetWork(std::string url,int photoTag){
    NetWorkManger* netManeger =NetWorkManger::sharedWorkManger();
    netManeger->tag=to_string(photoTag);
    netManeger->upLoadData(url.c_str(),CC_CALLBACK_2(VisitCaseScene::onHttpRequestImageCompleted, this),nullptr);
}
void VisitCaseScene::onHttpRequestImageCompleted(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response)
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
        sprintf(tagStr,"medicalImage%d_%d.png",atoi(infoData["data"]["id"].GetString()),atoi(tag));
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
            lv->removeChildByTag(2);
            auto layer3 = createMessageLayout(2,"影像","");
            lv->insertCustomItem(layer3,2);
        }else{
            getImageFromNetWork(videoArr.at(atoi(tag)+1).asString(),atoi(tag)+1);
        }
    }
}

float VisitCaseScene::createVideoLayerForListView(float height,Layout*bkView){
    auto visibleSize=Director::getInstance()->getVisibleSize();
    float size=videoArr.size()+1;
    int numberForRow=floor((visibleSize.width-80)/150.0);//向下取整     图形140*160
    int row=ceil((float)size/numberForRow);
    
    for (int i=0; i<size; i++) {
        if (i==size-1) {
            auto imageBtn1=ImageView::create("btn_chat_userImage.png");
            int width=40+(140+20)*(i+1)+40;
            if (width<visibleSize.width) {
                imageBtn1->setPosition(Vec2(40+(140+20)*i, height+20+(160+10)*(row-1)));
                log("width:%f,height:%f",imageBtn1->getPosition().x,imageBtn1->getPosition().y);
            }else{
                imageBtn1->setPosition(Vec2(40+(140+20)*(i%numberForRow),height+20+(160+10)*(row-1)-(10+160)*(i/numberForRow)));
                log("width:%f,height:%f",imageBtn1->getPosition().x,imageBtn1->getPosition().y);
            }
            imageBtn1->setAnchorPoint(Vec2(0, 0));
            imageBtn1->setTouchEnabled(true);
            imageBtn1->setScale(0.87);
            bkView->addChild(imageBtn1);
            imageBtn1->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
                if (type == Widget::TouchEventType::ENDED){
#pragma-上传照片
                    char positiveUrl[1000]={0};//正面   type=1则住院病历 type=2则自述病例
                    sprintf(positiveUrl,"http://czapi.looper.pro/web/file.php?cid=%s&type=1",UserDefault::getInstance()->getStringForKey("caseId").c_str());
                    string url=positiveUrl;
                    auto   updateSC=(UpdateCasePhotoScene*)UpdateCasePhotoScene::createScene();
                    updateSC->webURL=url;
                    Director::getInstance()->pushScene(updateSC);
                }
            });
        }else{
            char tagStr[50];
            sprintf(tagStr,"medicalImage%d_%d.png",atoi(infoData["data"]["id"].GetString()),i);
            string path=FileUtils::getInstance()->getWritablePath()+tagStr;
            auto imageBtn1=ImageView::create(path.c_str());
            //        auto imageBtn1=ImageView::create("bk_headIV.png");
            int width=40+(140+20)*(i+1)+40;
            if (width<visibleSize.width) {
                imageBtn1->setPosition(Vec2(40+(140+20)*i, height+(160+10)*(row-1)));
                log("width:%f,height:%f",imageBtn1->getPosition().x,imageBtn1->getPosition().y);
            }else{
                imageBtn1->setPosition(Vec2(40+(140+20)*(i%numberForRow),height+(160+10)*(row-1)-(10+160)*(i/numberForRow)));
                log("width:%f,height:%f",imageBtn1->getPosition().x,imageBtn1->getPosition().y);
            }
            imageBtn1->setAnchorPoint(Vec2(0, 0));
            imageBtn1->setTouchEnabled(true);
            imageBtn1->setTag(i);
            float height3=imageBtn1->getContentSize().height;
            float width3=imageBtn1->getContentSize().width;
            imageBtn1->setScaleX(125.0/width3);
            imageBtn1->setScaleY(150.0/height3);
            bkView->addChild(imageBtn1);
            imageBtn1->addTouchEventListener([this](Ref* pSender,Widget::TouchEventType type){
                if (type == Widget::TouchEventType::ENDED){
                    auto btn=(ImageView *)pSender;
#pragma-查看照片
                    auto showSC=(ShowImageScene*)ShowImageScene::createScene();
                    char tagStr[50];
                    sprintf(tagStr,"medicalImage%d_%d.png",atoi(infoData["data"]["id"].GetString()),btn->getTag());
                    showSC->imagePath=tagStr;
                    Director::getInstance()->pushScene(showSC);
                }
            });
        }
    }
    
    if (size==1) {
        return 150;
    }
    return (10+160)*row;
}



std::string VisitCaseScene::searchContentForInfoData(std::string content,std::string title,rapidjson::Document& data){
    content.append(title);
    
    if (data.IsObject()) {
        for (auto j=data.MemberBegin(); j!=data.MemberEnd(); ++j) {
            auto key = (j->name).GetString();
            if (data[key].Size()) {
                content.append(key);
                content.append(":");
            }
            log("key:%s", key);
            for(auto i = 0; i < data[key].Size(); ++i){
                content.append(data[key][i].GetString());
                if (i==data[key].Size()-1&&j==data.MemberEnd()-1) {}else{content.append(" ");}
                log("%s", data[key][i].GetString());
            }
        }
    }else if(data.IsArray()){
        for(auto i = 0; i < data.Size(); ++i){
            content.append(data[i].GetString());
            content.append(" ");
            log("%s", data[i].GetString());
        }
    }
    content.append("）");
    log("%s",content.c_str());
    return content;
}




