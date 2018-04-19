//
//  ChatViewScene.hpp
//  Chuangzheng-mobile
//
//  Created by lujiawei on 19/01/2018.
//

#ifndef ChatViewScene_hpp
#define ChatViewScene_hpp

#include <stdio.h>
#include "ui/CocosGUI.h"

class ChatViewScene:public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void onEnter();
    CREATE_FUNC(ChatViewScene);
    void createHubView();
    std::string webURL;
private:
    cocos2d::experimental::ui::WebView*webView;
};







#endif /* ChatViewScene_hpp */
