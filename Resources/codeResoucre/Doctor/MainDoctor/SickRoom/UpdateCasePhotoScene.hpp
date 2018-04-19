//
//  UpdateCasePhotoScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/4/3.
//

#ifndef UpdateCasePhotoScene_hpp
#define UpdateCasePhotoScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"

class UpdateCasePhotoScene:public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void onEnter();
    CREATE_FUNC(UpdateCasePhotoScene);
    void createHubView();
    std::string webURL;
private:
    cocos2d::experimental::ui::WebView*webView;
};

#endif /* UpdateCasePhotoScene_hpp */
