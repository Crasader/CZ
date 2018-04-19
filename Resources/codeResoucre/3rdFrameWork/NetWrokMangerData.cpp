//
//  NetWrokMangerData.cpp
//  Chuangzheng-mobile
//
//  Created by lujiawei on 29/11/2017.
//

#include "NetWrokMangerData.hpp"
#include "cocos2d.h"
#include "network/HttpClient.h"
#include <iostream>
#include "json/rapidjson.h"

#include "json/document.h"

#include "json/writer.h"

#include "json/stringbuffer.h"




using namespace rapidjson; // 命名空间
using namespace std;
using namespace cocos2d::network;
using namespace cocos2d;

NetWorkManger::NetWorkManger()
{
    
    
    
}

NetWorkManger::~NetWorkManger()
{
    

}
NetWorkManger * NetWorkManger::sharedWorkManger()
{
    static NetWorkManger instance;
    return  &instance;
}


void NetWorkManger::upLoadData(string UrlStr,const ccHttpRequestCallback& callback,char *requestData)
{
    HttpRequest* request = new  HttpRequest();
    request->setRequestType(HttpRequest::Type::GET);
    request->setUrl(UrlStr.c_str());
    request->setTag(tag);
    request->setResponseCallback(callback);
    HttpClient::getInstance()->send(request);
    request->release();
}


void NetWorkManger::sendMessage(string UrlStr,const ccHttpRequestCallback& callback,char *requestDataStr)
{
    
    HttpRequest* request = new  HttpRequest();
    
    request->setUrl(UrlStr);
    request->setRequestType(HttpRequest::Type::POST);
    request->setResponseCallback(callback);
     if (requestDataStr!=nullptr) {
    const  char* postData = requestDataStr;
    request->setRequestData(postData,strlen(postData) );
     }
    request->setTag(tag);
    
    HttpClient::getInstance()->send(request);
     request->release();
     
}

//当传送json数据时需要使用此方法
void NetWorkManger::postHttpRequest(string UrlStr,const ccHttpRequestCallback& callback,char* requestDataStr){
    HttpRequest* request = new (std::nothrow) HttpRequest();
    request->setUrl(UrlStr);
    request -> setRequestType(HttpRequest::Type::POST);
     request->setResponseCallback(callback);
    auto postData = requestDataStr;
    std::vector<std::string> headers;
    headers.push_back("Content-Type: application/json; charset=utf-8");
    // 设置请求头，如果数据为键值对则不需要设置
//    request -> setHeaders(headers);
    // 传入发送的数据及数据ch n g
     if (requestDataStr!=nullptr) {
    request -> setRequestData(postData, strlen(postData));
     }
    request -> setTag("POST TEST");
    HttpClient::getInstance() -> send(request);
    request -> release();
}


void NetWorkManger::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
    if (!response)
    {
        return;
    }
    if (0 != strlen(response->getHttpRequest()->getTag())) {
        log("%s compeled",response->getHttpRequest()->getTag());
    }
    
    if (!response->isSucceed()) {
        log("response failed");
        log("error buffer:%s",response->getErrorBuffer());
        return;
    }
    
    std::vector<char> *data = response->getResponseData();
    std::string recieveData;
    recieveData.assign(data->begin(), data->end());
    cout<<recieveData.length()<<endl;
    cout<<recieveData<<endl;
    
    rapidjson::Document d;
    
    d.Parse<rapidjson::kParseDefaultFlags>(recieveData.c_str());
    
    if (d.HasParseError()) {
        
        return;
    }

    if(d.HasMember("data")){
        for(int i = 0; i < d["data"].Size(); i++) {
            
            rapidjson::Value& object = d["data"][i];
            
            CCLOG("%s", object["artistheaderimageurl"].GetString());
        }
    }
}

//读取网络图片
void NetWorkManger::onHttpRequestCompletedForImage(HttpClient* sender, HttpResponse* response){
    if (!response)
    {
        return;
    }
    std::vector<char> *data = response->getResponseData();
//加载到本地
    /*   char * buf=(char *)malloc(data->size());
     std::copy(data->begin(),data->end(),buf);
     std::string sFileName="smile.png";
     std::string path = FileUtils::getInstance()->getWritablePath()+sFileName;
     FILE *fp=fopen(path.c_str(),"wb+");//读写打开或建立一个二进制文件，允许读和写
     fwrite(buf,1,data->size(),fp);
     fclose(fp);     */
//读取本地数据
    /*   Sprite* sp=Sprite::create(path.c_str());
     sp->setPosition(Vec2(0,0));
     addChild(sp);   */
//清除数据
    /*   TextureCache *textureCache = TextureCache::getInstance();
     textureCache->reloadTexture(path);    */
//读取网络图片
    Image* image = new Image;
    image->initWithImageData((unsigned char*)data->data(),data->size());
    auto texture = new Texture2D();
    bool isImage = texture->initWithImage(image);
    if(isImage){
        log("Texture2D 初始化!");
    }
    auto sprite=Sprite::createWithTexture(texture);
    sprite->setContentSize(Size(100, 100));
    sprite->setPosition(Vec2(100, 100));
    //    this->addChild(sprite);
    image->release();
}



/*string NetWorkManger::changeUTF8ToUnicode(string str){
 size_t sSize=str.length();
 wchar_t * dBuf=NULL;
 //    <SPAN style="COLOR: #ff0000">//注意：需要多分配一个空间，以存放终止符</SPAN>
 int dSize=mbstowcs(dBuf, str.c_str(), 0)+1;
 dBuf=new wchar_t[dSize];
 wmemset(dBuf, 0, dSize);
 int nRet=mbstowcs(dBuf, str.c_str(), sSize);
 if(nRet<=0){
 printf("转换失败\n");}
 else{
 printf("转换成功%d字符\n", nRet);
 wprintf(L"%ls\n", dBuf);
 //wchar_t转化为char
 int len = wcstombs(NULL,dBuf,0);
 char* buf = new char[len+1];
 wcstombs(buf,dBuf,len);
 buf[len] = 0;
 return buf;
 }
 return str;
 }*/
