//
//  ShowImageScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/4/4.
//

#ifndef ShowImageScene_hpp
#define ShowImageScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"

class ShowImageScene:public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void onEnter();
    CREATE_FUNC(ShowImageScene);
    void createHubView();
    std::string imagePath;//FileUtils本地图片路径
    
private:
    cocos2d::Sprite* imgView;
};

#endif /* ShowImageScene_hpp */
