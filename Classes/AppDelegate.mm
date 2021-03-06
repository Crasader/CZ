#include "AppDelegate.h"
#include "LoginScene.h"
#include "WelcomeScene.hpp"

#include "MessageNotificationScene.hpp"
#include "SpineTendernessScene.hpp"
#include "UserCaseScene.hpp"
#include "TreatScene.hpp"
#include "VisitTimeScene.hpp"
#include "DrawLineScene.hpp"
#include "UpdateBedScene.hpp"

#include "ChatViewScene.hpp"
#include "LenkeScene.hpp"


#include "WelcomeScene.hpp"
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
//#import "platform/ios/CCEAGLView-ios.h"


#include "GroupMemberScene.hpp"
#include "CaseHistoryScene.hpp"
#include "RootViewController.h"
#import "QRViewController.h"


#include "SelectDoctorScene.hpp"
static AppDelegate *delegateA;
@interface callBack:NSObject<QRViewDelegate>{
}
@end
@implementation callBack
-(void)imageDelegateUrl:(NSString*)ImageUrl{
     delegateA->ImageSavePath([ImageUrl cStringUsingEncoding: NSUTF8StringEncoding]);
}
-(void)QRWithString:(NSString*)QRStr{
    delegateA->QRWithString([QRStr cStringUsingEncoding: NSUTF8StringEncoding]);
}
@end
#include "DocUserInfoScene.hpp"
#include "CaseHistoryScene.hpp"
#include "TreatScene.hpp"

using namespace std;

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1


#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace
using namespace CocosDenshion;
#endif
USING_NS_CC;
static cocos2d::Size designResolutionSize = cocos2d::Size(640, 1136);
static cocos2d::Size smallResolutionSize = cocos2d::Size(640, 1136);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);
AppDelegate::AppDelegate()
{
    delegateA = this;
}
AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}


class A{
public:
      void  display(){  cout<<"A"<<endl; }
};
class B :  public A{
public:
    void  display(){ cout<<"B"<<endl; }
};
void doDisplay(A *p)
{
    B *P1 = (B*)&(*p);
    P1->display();
    p->display();
    delete p;
}



// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Chuangzheng", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
       glview = GLViewImpl::create("Chuangzheng");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 24);

    // Set the design resolution
   glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    
    
    // director->setContentScaleFactor(designResolutionSize.width/frameSize.width);

    
//    if (frameSize.height > mediumResolutionSize.height)
//    {
//        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
//    }
//    // if the frame's height is larger than the height of small size.
//    else if (frameSize.height > smallResolutionSize.height)
//    {
//        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
//    }
//    // if the frame's height is smaller than the height of medium size.
//    else
//    {
//        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
//    }

    register_all_packages();
    
            auto scene = LoginScene::createScene();
//    auto scene=ChatViewScene::createScene();
//    auto scene=SelectDoctorScene::createScene();
//    auto  scene=LenkeScene::createScene();
    director->runWithScene(scene);
    
//    UIView *view = [[UIView alloc] initWithFrame:CGRectMake(0, 0, [UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height)];
    ///  [[CCEAGLView sharedEGLView] addSubview:view];
//    [view setBackgroundColor:[UIColor blueColor]];
    
    
    
#pragma-陆兄尝试的相机调用
 /*   callBack *callObj = [[callBack alloc] init];
    QRViewController *QRViewC = [[QRViewController alloc] init];
    QRViewC.delegate = callObj;
    auto rootViewController = (RootViewController*) [[[UIApplication sharedApplication] keyWindow] rootViewController];
    [rootViewController.view addSubview:QRViewC.view];
    [QRViewC scanQRImage];
    this->ImageSavePath("dadadadad");
    doDisplay(new B());
    return true;   */
#pragma-生成二维码
    /*
     auto testScene = Scene::create();
     director->runWithScene(testScene);
     bool bRet = m_QREncode.EncodeData(0, 0, 1, -1, "autor:johance qq:421465201");
     if(bRet)
     {
     int nSize = 5;
     int originalSize = m_QREncode.m_nSymbleSize + (QR_MARGIN * 2);
     CCDrawNode *pQRNode = CCDrawNode::create();
     
     CCPoint pt[6];
     ccColor4F color;
     
     pt[0] = ccp(0, 0);
     pt[1] = ccp((m_QREncode.m_nSymbleSize + QR_MARGIN * 2)*nSize, (m_QREncode.m_nSymbleSize + QR_MARGIN * 2)*nSize);
     pt[2] = ccp((m_QREncode.m_nSymbleSize + QR_MARGIN * 2)*nSize, 0);
     
     pt[3] = pt[0];
     pt[4] = ccp(0, (m_QREncode.m_nSymbleSize + QR_MARGIN * 2)*nSize);
     pt[5] = pt[1];
     color = ccc4f(1, 1, 1, 1);
     pQRNode->drawPolygon(pt, 6, color, 0, color);
     
     for (int i = 0; i < m_QREncode.m_nSymbleSize; ++i)
     {
     for (int j = 0; j < m_QREncode.m_nSymbleSize; ++j)
     {
     pt[0] = ccp((i + QR_MARGIN)*nSize, (j + QR_MARGIN)*nSize);
     pt[1] = ccp(((i + QR_MARGIN) + 1)*nSize, ((j + QR_MARGIN) + 1)*nSize);
     pt[2] = ccp(((i + QR_MARGIN) + 1)*nSize, ((j + QR_MARGIN) + 0)*nSize);
     
     pt[3] = pt[0];
     pt[4] = ccp(((i + QR_MARGIN) + 0)*nSize, ((j + QR_MARGIN) + 1)*nSize);
     pt[5] = pt[1];
     if (m_QREncode.m_byModuleData[i][j] == 1)
     {
     color = ccc4f(0, 0, 0, 1);
     }
     else
     {
     color = ccc4f(1, 1, 1, 1);
     }
     pQRNode->drawPolygon(pt, 6, color, 0, color);
     }
     }
     CCSize winSize = CCDirector::sharedDirector()->getWinSize();
     pQRNode->setPosition(ccp((winSize.width - nSize*m_QREncode.m_nSymbleSize) / 2, winSize.height - (winSize.height - nSize*m_QREncode.m_nSymbleSize) / 2));
     pQRNode->setScaleY(-1);
     testScene->addChild(pQRNode);
     }
     */
}
//int main()
//{
//    Base *point=new Derived();
//    point->print();
//}
void AppDelegate::QRWithString(std::string str){
     CCLOG("%s",str.c_str());
}
void AppDelegate::ImageSavePath(std::string str){
    CCLOG("%s",str.c_str());
}
// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    if (UserDefault::getInstance()->getStringForKey("isLock").length()==0||UserDefault::getInstance()->getStringForKey("isLock")=="0") {
        log("islock  %s",UserDefault::getInstance()->getStringForKey("isLock").c_str());
    }else{
    auto  scene=DrawLineScene::createScene();
    Director::getInstance()->pushScene(scene);
    }
#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}

