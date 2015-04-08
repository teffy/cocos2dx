#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "network/HttpClient.h"
#include "network/HttpClient.h"
#include "network/HttpRequest.h"
#include "network/SocketIO.h"
#include "network/WebSocket.h"

USING_NS_CC;
using namespace cocos2d::network;

class HelloWorld : public cocos2d::Layer,public SocketIO::SIODelegate,public WebSocket::Delegate
{
public:
	HelloWorld(void);
    virtual ~HelloWorld(void);
	virtual void onConnect(SIOClient* client);
	virtual void onMessage(SIOClient* client, const std::string& data);
	virtual void onClose(SIOClient* client);
	virtual void onError(SIOClient* client, const std::string& data);

	virtual void onOpen(WebSocket* ws);
	virtual void onMessage(WebSocket* ws, const WebSocket::Data& data);
	virtual void onClose(WebSocket* ws);
	virtual void onError(WebSocket* ws, const WebSocket::ErrorCode& error);

    static cocos2d::Scene* createScene();
    virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);

	void menuGetCallback(cocos2d::Ref* pSender);
	void menuPostCallback(cocos2d::Ref* pSender);
	void menuPutCallback(cocos2d::Ref* pSender);
	void menuDeleteCallback(cocos2d::Ref* pSender);
	void onHttpCompletedCallback(HttpClient *httpClient, HttpResponse *response);

	void menuOpenSocketCallback(cocos2d::Ref* pSender);
	void menuSendMsgCallback(cocos2d::Ref* pSender);
	void menuSendEventCallback(cocos2d::Ref* pSender);
	void menuCloseSocketCallback(cocos2d::Ref* pSender);
	void menuWebSocketCallback(cocos2d::Ref* pSender);

	void sendMsgCallBack(SIOClient* client,const std::string data);
	void sendEventCallBack(SIOClient* client,const std::string data);

    CREATE_FUNC(HelloWorld);
private:
	Label *label;
	SIOClient* _client;
	WebSocket* _webSocket;
};

#endif // __HELLOWORLD_SCENE_H__
