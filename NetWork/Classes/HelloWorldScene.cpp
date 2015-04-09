#include "HelloWorldScene.h"

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

	MenuItemFont* httpGet = MenuItemFont::create("httpGet", CC_CALLBACK_1(HelloWorld::menuGetCallback, this));
	httpGet->setPosition(Vec2(visibleSize.width / 6, visibleSize.height - httpGet->getContentSize().height));
	MenuItemFont* httpPost = MenuItemFont::create("httpPost", CC_CALLBACK_1(HelloWorld::menuPostCallback, this));
	httpPost->setPosition(Vec2(visibleSize.width / 6, visibleSize.height - httpPost->getContentSize().height*2));
	MenuItemFont* httpPut = MenuItemFont::create("httpPut", CC_CALLBACK_1(HelloWorld::menuPutCallback, this));
	httpPut->setPosition(Vec2(visibleSize.width / 6, visibleSize.height - httpPut->getContentSize().height*3));
	MenuItemFont* httpDelete = MenuItemFont::create("httpDelete", CC_CALLBACK_1(HelloWorld::menuDeleteCallback, this));
	httpDelete->setPosition(Vec2(visibleSize.width / 6, visibleSize.height - httpDelete->getContentSize().height * 4));

	MenuItemFont* openSocket = MenuItemFont::create("Socket Open", CC_CALLBACK_1(HelloWorld::menuOpenSocketCallback, this));
	openSocket->setPosition(Vec2(visibleSize.width * 0.4f, visibleSize.height - openSocket->getContentSize().height * 1));
	MenuItemFont* sendMsg = MenuItemFont::create("SendMsg", CC_CALLBACK_1(HelloWorld::menuSendMsgCallback, this));
	sendMsg->setPosition(Vec2(visibleSize.width * 0.4f, visibleSize.height - sendMsg->getContentSize().height * 2));
	MenuItemFont* sendEvent = MenuItemFont::create("sendEvent", CC_CALLBACK_1(HelloWorld::menuSendEventCallback, this));
	sendEvent->setPosition(Vec2(visibleSize.width * 0.4f, visibleSize.height - sendEvent->getContentSize().height * 3));
	MenuItemFont* closeSocket = MenuItemFont::create("closeSocket", CC_CALLBACK_1(HelloWorld::menuCloseSocketCallback, this));
	closeSocket->setPosition(Vec2(visibleSize.width * 0.4f, visibleSize.height - closeSocket->getContentSize().height * 4));

	MenuItemFont* webSocket = MenuItemFont::create("WebSocket", CC_CALLBACK_1(HelloWorld::menuWebSocketCallback, this));
	webSocket->setPosition(Vec2(visibleSize.width * 0.4f, visibleSize.height - webSocket->getContentSize().height * 6));

	auto menu = Menu::create(
			closeItem, httpGet, httpPost, httpPut, httpDelete,
			openSocket,sendMsg,sendEvent,closeSocket,webSocket,
			NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 - 100));
    this->addChild(label, 1);
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);

    _webSocket = new WebSocket();
    if(!_webSocket->init(*this,"ws://echo.websocket.org")){
    	CC_SAFE_DELETE(_webSocket);
    }
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuGetCallback(Ref* pSender){
	{
		HttpRequest *request = new HttpRequest();
		request->setUrl("http://just-make-this-request-failed.com");
		request->setRequestType(HttpRequest::Type::GET);
		request->setResponseCallback(CC_CALLBACK_2(HelloWorld::onHttpCompletedCallback, this));
		request->setTag("GET failed");
		HttpClient::getInstance()->send(request);
		//HttpClient::getInstance()->sendImmediate(request);
		request->release();
	}

	{
		HttpRequest *request = new HttpRequest();
		request->setUrl("http://httpbin.org/ip");
		request->setRequestType(HttpRequest::Type::GET);
		request->setResponseCallback(CC_CALLBACK_2(HelloWorld::onHttpCompletedCallback, this));
		request->setTag("GET IP");
		HttpClient::getInstance()->send(request);
		request->release();
	}

	{
		HttpRequest *request = new HttpRequest();
		request->setUrl("https://httpbin.org/get");
		request->setRequestType(HttpRequest::Type::GET);
		request->setResponseCallback(CC_CALLBACK_2(HelloWorld::onHttpCompletedCallback, this));
		request->setTag("GET sendImmediate");
		HttpClient::getInstance()->sendImmediate(request);
		request->release();
	}
}

void HelloWorld::menuPostCallback(Ref* pSender){
	{
		HttpRequest *request = new HttpRequest();
		request->setUrl("http://httpbin.org/post");
		request->setRequestType(HttpRequest::Type::POST);
		request->setResponseCallback(CC_CALLBACK_2(HelloWorld::onHttpCompletedCallback, this));
		request->setTag("Post");
		HttpClient::getInstance()->send(request);
		request->release(); }
	{
		HttpRequest *request = new HttpRequest();
		request->setUrl("http://httpbin.org/post");
		request->setRequestType(HttpRequest::Type::POST);
		char param[22] = "binary=hello\0\0cocos2d";
		request->setRequestData(param, 22);
		request->setResponseCallback(CC_CALLBACK_2(HelloWorld::onHttpCompletedCallback, this));
		request->setTag("Post Binary");
		HttpClient::getInstance()->send(request);
		request->release();
	}

	{
		HttpRequest *request = new HttpRequest();
		request->setUrl("http://httpbin.org/post");
		request->setRequestType(HttpRequest::Type::POST);
		std::vector<std::string> headers;
		headers.push_back("Content-Type: application/json; charset=utf-8");
		request->setHeaders(headers);
		char param[22] = "binary=hello\0\0cocos2d";
		request->setRequestData(param, 22);
		request->setResponseCallback(CC_CALLBACK_2(HelloWorld::onHttpCompletedCallback, this));
		request->setTag("Post Binary Set Headers");
		HttpClient::getInstance()->send(request);
		request->release();
	}
}

void HelloWorld::menuPutCallback(Ref* pSender){
	{
		HttpRequest *request = new HttpRequest();
		request->setUrl("http://httpbin.org/put");
		request->setRequestType(HttpRequest::Type::PUT);
		const std::string param = "visitor=cocos2d&TestSuite=Extensions Test/NetworkTest";
		request->setResponseCallback(CC_CALLBACK_2(HelloWorld::onHttpCompletedCallback, this));
		request->setTag("Put");
		HttpClient::getInstance()->send(request);
		request->release();
	}
	{
		HttpRequest *request = new HttpRequest();
		request->setUrl("http://httpbin.org/put");
		request->setRequestType(HttpRequest::Type::PUT);
		std::vector<std::string> headers;
		headers.push_back("Content-Type: application/json; charset=utf-8");
		request->setHeaders(headers);
		const std::string param = "visitor=cocos2d&TestSuite=Extensions Test/NetworkTest";
		request->setResponseCallback(CC_CALLBACK_2(HelloWorld::onHttpCompletedCallback, this));
		request->setTag("Put Set ContentType");
		HttpClient::getInstance()->send(request);
		request->release();
	}
}
void HelloWorld::menuDeleteCallback(Ref* pSender){
	{
		HttpRequest *request = new HttpRequest();
		request->setUrl("http://just-make-this-request-failed.com");
		request->setRequestType(HttpRequest::Type::DELETE);
		request->setResponseCallback(CC_CALLBACK_2(HelloWorld::onHttpCompletedCallback, this));
		request->setTag("Delete failed");
		HttpClient::getInstance()->send(request);
		request->release();
	}

	{
		HttpRequest *request = new HttpRequest();
		request->setUrl("http://httpbin.org/delete");
		request->setRequestType(HttpRequest::Type::DELETE);
		request->setResponseCallback(CC_CALLBACK_2(HelloWorld::onHttpCompletedCallback, this));
		request->setTag("Delete");
		HttpClient::getInstance()->send(request);
		request->release();
	}
}

void HelloWorld::onHttpCompletedCallback(HttpClient *httpClient, HttpResponse *response){
	if (!response){
		return;
	}
	if (0 != strlen(response->getHttpRequest()->getTag())){
		log("\n%s complete", response->getHttpRequest()->getTag());
	}
	long responseCode = response->getResponseCode();
	log("response code %ld",responseCode);
	if (!response->isSucceed()){
		log("response faild");
		log("error msg:%s", response->getErrorBuffer());
		return;
	}
	std::vector<char>* data = response->getResponseData();
	//std::string str = "";
	/*for (std::vector<char>::iterator iterator = data->begin(); iterator != data->end(); ++iterator){
		str += *iterator;
	}*/
	/*for (unsigned int i = 0; i < data->size(); i++){
		str += (*data)[i];
	}*/
	std::string str(data->begin(),data->end());
	log("data:\n%s", str.c_str());

	label->setString(str);
}

void HelloWorld::menuOpenSocketCallback(cocos2d::Ref* pSender){
	_client = SocketIO::connect("10.11.41.43:1987",*this);
	_client->setTag("Socket");
	_client->on("Sendmsg",CC_CALLBACK_2(HelloWorld::sendMsgCallBack,this));
	_client->on("Sendmsg",CC_CALLBACK_2(HelloWorld::sendEventCallBack,this));
}
void HelloWorld::menuSendMsgCallback(cocos2d::Ref* pSender){
	if(_client != nullptr){
		_client->send("Hello,I am cocos2dx client!");
	}

}
void HelloWorld::menuSendEventCallback(cocos2d::Ref* pSender){
	if(_client != nullptr){
		_client->emit("echo","[{\"name\":\"cocos\",\"type\":\"2dx\"}]");
	}
}
void HelloWorld::menuCloseSocketCallback(cocos2d::Ref* pSender){
	if(_client != nullptr){
		_client->disconnect();
		_client = nullptr;
	}
}

void HelloWorld::sendMsgCallBack(SIOClient* client,const std::string data){
	log("sendMsg with data:%s",data.c_str());
	std::stringstream s;
	s << client->getTag() << " received event testevent with data: " << data.c_str();
	label->setString(s.str().c_str());
}
void HelloWorld::sendEventCallBack(SIOClient* client,const std::string data){
	log("sendMsg with data:%s",data.c_str());
	std::stringstream s;
	s << client->getTag() << " received event testevent with data: " << data.c_str();
	label->setString(s.str().c_str());
}

void HelloWorld::onConnect(SIOClient* client){
	log("onConnect");
	std::stringstream s;
	s<<client->getTag()<<" connect!";
	label->setString(s.str().c_str());
}
void HelloWorld::onMessage(SIOClient* client, const std::string& data){
	log("onMessage");
	std::stringstream s;
	s<<client->getTag()<<" receive Message!"<<data.c_str();
	label->setString(s.str().c_str());
}
void HelloWorld::onClose(SIOClient* client){
	log("onMessage");
	std::stringstream s;
	s<<client->getTag()<<" Close!";
	label->setString(s.str().c_str());
	if(client == _client){
		_client = nullptr;
	}
}
void HelloWorld::onError(SIOClient* client, const std::string& data){
	log("onMessage");
	std::stringstream s;
	s<<client->getTag()<<" receive Error!"<<data.c_str();
	label->setString(s.str().c_str());
}
HelloWorld::HelloWorld(void){}
HelloWorld::~HelloWorld(void){}

void HelloWorld::menuWebSocketCallback(Ref* pSender){
	if(!_webSocket){
		return;
	}
	if(_webSocket->getReadyState() == WebSocket::State::OPEN){
		label->setString("sending message...");
		_webSocket->send("Hello WebSocket,I am cocox2dx");
	}else{
		label->setString("WebSocket is not ready...");
	}
}
void HelloWorld::onOpen(WebSocket* ws){
	if(ws == _webSocket){
		label->setString("WebSocket opened");
	}
}
void HelloWorld::onMessage(WebSocket* ws, const WebSocket::Data& data){
	std::string printmsg = std::string("response msg:")+data.bytes;
	label->setString(printmsg.c_str());
}
void HelloWorld::onClose(WebSocket* ws){
	if(ws == _webSocket){
		_webSocket = nullptr;
	}
	CC_SAFE_DELETE(ws);
}
void HelloWorld::onError(WebSocket* ws, const WebSocket::ErrorCode& error){
	if(ws == _webSocket){
		char buf[100] ={0};
		sprintf(buf,"WebSocket error,code:%d",error);
		label->setString(buf);
	}
}
