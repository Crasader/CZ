//
//  TakePhoto.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/3/26.
//

#ifndef TakePhoto_hpp
#define TakePhoto_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
#define kTakePhotoEvent "TakePhotoEvent"
class TakePhoto{
public:
    TakePhoto();
    static TakePhoto* getInstance();
    static void destroyInstance();
    void openCamera(std::function<void(std::string)> callback);
    void openPhoto(std::function<void(std::string)> callback);
    
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //设置AppController iOS平台在AppController.mm里调用把rootViewController传递过来
    void setViewController(void* viewController);
    void *m_viewController;
#endif
    
private:
    static TakePhoto* _instance;
    std::function<void(std::string)> _callback;
};

#endif /* TakePhoto_hpp */
