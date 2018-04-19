//
//  SelectBodyScene.hpp
//  Chuangzheng-mobile
//
//  Created by 工作 on 2018/4/3.
//

#ifndef SelectBodyScene_hpp
#define SelectBodyScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"

class SelectBodyScene:public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void onEnter();
    CREATE_FUNC(SelectBodyScene);
    void createHubView();
    std::string webURL;
    std::string contraryURL;
    
    
    void checkBoxCallback(cocos2d::Ref * ref, cocos2d::ui::CheckBox::EventType type);
private:
    cocos2d::experimental::ui::WebView*webView;
    cocos2d::experimental::ui::WebView*webView2;
    cocos2d::LayerMultiplex *multLayer;
};

#endif /* SelectBodyScene_hpp */
