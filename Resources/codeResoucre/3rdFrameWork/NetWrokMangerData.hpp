//
//  NetWrokMangerData.hpp
//  Chuangzheng-mobile
//
//  Created by lujiawei on 29/11/2017.
//

#ifndef NetWrokMangerData_hpp
#define NetWrokMangerData_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "network/HttpClient.h"
#include <iostream>
#include "iconv.h"
using namespace cocos2d::network;
using namespace std;
using namespace cocos2d;

class NetWorkManger:public cocos2d::Ref
{


public:
    
    ~NetWorkManger();
    
    static NetWorkManger* sharedWorkManger();
    
    void sendMessage(string UrlStr,const ccHttpRequestCallback& callback,char *requestDataStr);
    
    void postHttpRequest(string UrlStr,const ccHttpRequestCallback& callback,char* requestDataStr);
    
    void upLoadData(string UrlStr,const ccHttpRequestCallback& callback,char *requestData);
    
    void onHttpRequestCompleted(HttpClient* sender,HttpResponse* response);
    
    void onHttpRequestCompletedForImage(HttpClient* sender,HttpResponse* response);
    
    string changeUTF8ToUnicode(string str);
    
    string tag;
    
private:

    NetWorkManger();

    
};


#endif 





