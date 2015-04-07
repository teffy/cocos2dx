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
	httpGet->setPosition(Vec2(visibleSize.width / 2 -100, visibleSize.height / 2 + httpGet->getContentSize().height * 2));

	MenuItemFont* httpPost = MenuItemFont::create("httpPost", CC_CALLBACK_1(HelloWorld::menuPostCallback, this));
	httpPost->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 + httpPost->getContentSize().height));


	MenuItemFont* httpPut = MenuItemFont::create("httpPut", CC_CALLBACK_1(HelloWorld::menuPutCallback, this));
	httpPut->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 - httpPut->getContentSize().height));

	MenuItemFont* httpDelete = MenuItemFont::create("httpDelete", CC_CALLBACK_1(HelloWorld::menuDeleteCallback, this));
	httpDelete->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 - httpDelete->getContentSize().height * 2));


	auto menu = Menu::create(closeItem, httpGet, httpPost, httpPut, httpDelete, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    label->setPosition(Vec2(origin.x + visibleSize.width/2+200,
                            origin.y + visibleSize.height/2));
    this->addChild(label, 1);
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    
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