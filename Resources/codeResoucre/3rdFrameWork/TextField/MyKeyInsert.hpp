//
//  MyKeyInsert.hpp
//  looper-mobile
//
//  Created by 工作 on 2018/4/8.
//
#pragma once
#include "CursorTextField.hpp"
class KeyInsert : public CursorTextField
{
public:
    
    KeyInsert();
    ~KeyInsert();
    static KeyInsert * getinstence();
    static void destoryinstence();
    void addKeyBordClick(cocos2d::Node * node);
    cocos2d::Node * parentNode;
    cocos2d::EventListenerKeyboard * _keyBordListener;
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode,cocos2d::Event*);
private:
    
};
