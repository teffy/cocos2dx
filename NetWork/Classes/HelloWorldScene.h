#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "network\HttpClient.h"
#include "network\HttpClient.h"
#include "network\HttpRequest.h"

USING_NS_CC;
using namespace cocos2d::network;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuGetCallback(cocos2d::Ref* pSender);
	void menuPostCallback(cocos2d::Ref* pSender);
	void menuPutCallback(cocos2d::Ref* pSender);
	void menuDeleteCallback(cocos2d::Ref* pSender);
	
	void onHttpCompletedCallback(HttpClient *httpClient, HttpResponse *response);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	Label *label;
};

#endif // __HELLOWORLD_SCENE_H__
