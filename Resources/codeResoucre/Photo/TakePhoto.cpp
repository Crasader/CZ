//
//  TakePhoto.cpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/3/26.
//

#include "TakePhoto.hpp"
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import "ImagePickerViewController.h"
#import "RootViewController.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#define JAVA_CLASS "org/cocos2dx/cpp/ImageCrop"
#define JAVA_FUNC_OPEN_PHOTO    "openPhoto"
#define JAVA_FUNC_OPEN_CAMERA   "openCamera"
#endif

TakePhoto::TakePhoto()
:_callback(nullptr)
{
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(kTakePhotoEvent, [=](EventCustom *event)
                                                                          {
                                                                              std::string *imgPath = (std::string*)event->getUserData();
                                                                              _callback(*imgPath);
                                                                          });
}

TakePhoto* TakePhoto::_instance = nullptr;
TakePhoto* TakePhoto::getInstance()
{
    if (!_instance)
    {
        _instance = new (std::nothrow) TakePhoto();
    }
    return _instance;
}

void TakePhoto::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
}

void TakePhoto::openCamera(std::function<void (std::string)> callback)
{
    _callback = callback;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ImagePickerViewController * imagePickerViewController = [[ImagePickerViewController alloc]initWithNibName:nil bundle:nil];
    
    RootViewController *_viewController = (RootViewController*)m_viewController;
    [_viewController.view addSubview:imagePickerViewController.view];
    [imagePickerViewController takePhoto];
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo info;
    bool ret = JniHelper::getStaticMethodInfo(info,JAVA_CLASS,JAVA_FUNC_OPEN_CAMERA,"()V");
    if (ret)
    {
        info.env->CallStaticVoidMethod(info.classID,info.methodID);
    }
#endif
}

void TakePhoto::openPhoto(std::function<void (std::string)> callback)
{
    _callback = callback;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ImagePickerViewController * imagePickerViewController = [[ImagePickerViewController alloc]initWithNibName:nil bundle:nil];
    
    RootViewController *_viewController = (RootViewController*)m_viewController;
    [_viewController.view addSubview:imagePickerViewController.view];
    [imagePickerViewController localPhoto];
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo info;
    bool ret = JniHelper::getStaticMethodInfo(info,JAVA_CLASS,JAVA_FUNC_OPEN_PHOTO,"()V");
    if (ret)
    {
        info.env->CallStaticVoidMethod(info.classID,info.methodID);
    }
#endif
    
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
void ImageCrop::setViewController(void *viewController)
{
    m_viewController = viewController;
}
#endif


//--------Java回调C++--------native 方法
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

extern "C"
{
    void Java_org_cocos2dx_cpp_ImageCrop_onImageSaved(JNIEnv *env,jobject thiz,jstring path)
    {
        std::string strPath = JniHelper::jstring2string(path);
        //必须这样，否则由于线程问题会显示黑块无法正常创建精灵
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=,strPath]()mutable{
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(kTakePhotoEvent,&strPath);
        });
    }
}

#endif


