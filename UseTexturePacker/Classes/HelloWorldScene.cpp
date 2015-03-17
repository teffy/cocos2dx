#include "HelloWorldScene.h"
#include <SimpleAudioEngine.h>

using namespace CocosDenshion;

USING_NS_CC;

#define BG_MUSIC "bgmusic.mp3"
#define DOG_WANGWANG "dog.wav"


Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));




	auto playBgMusic = MenuItemFont::create("Paly BgMusic", CC_CALLBACK_1(HelloWorld::menuPlayBgMusicCallback, this));
	playBgMusic->setPosition(Vec2(visibleSize.width / 5, visibleSize.height / 6));

	auto playEffect = MenuItemFont::create("Paly Effect", CC_CALLBACK_1(HelloWorld::menuPlayEffectCallback, this));
	playEffect->setPosition(Vec2(visibleSize.width / 5, visibleSize.height *2/ 6));
	
	auto pause = MenuItemFont::create("Pause", CC_CALLBACK_1(HelloWorld::menuPauseCallback, this));
	pause->setPosition(Vec2(visibleSize.width / 5, visibleSize.height * 3 / 6));

	auto resume = MenuItemFont::create("Resume", CC_CALLBACK_1(HelloWorld::menuResumeCallback, this));
	resume->setPosition(Vec2(visibleSize.width * 2 / 5, visibleSize.height * 3 / 6));

	auto stop = MenuItemFont::create("Stop", CC_CALLBACK_1(HelloWorld::menuStopCallback, this));
	stop->setPosition(Vec2(visibleSize.width * 3 / 5, visibleSize.height * 3 / 6));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, playBgMusic, playEffect, pause,resume,stop, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	auto xiaopao = Sprite::create("res/xiaobing.png");
	xiaopao->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(xiaopao);
	SpriteFrameCache* cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("res/xiaobing.plist", "res/xiaobing.png");
	Animation* anim = AnimationCreator::createAnimWithFrameNameAndNum("xiaobing", 8, 0.1f, -1);
	xiaopao->runAction(Animate::create(anim));
	

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BG_MUSIC);
	SimpleAudioEngine::getInstance()->preloadEffect(DOG_WANGWANG);

	return true;
}

void HelloWorld::menuPlayEffectCallback(Ref* pSender){
	dog_wangwang = SimpleAudioEngine::getInstance()->playEffect(DOG_WANGWANG);
}

void HelloWorld::menuPlayBgMusicCallback(Ref* pSender){
	SimpleAudioEngine::getInstance()->playBackgroundMusic(BG_MUSIC,true);
}

void HelloWorld::menuResumeCallback(Ref* pSender){
	log("%d", dog_wangwang);
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

		SimpleAudioEngine::getInstance()->resumeEffect(dog_wangwang);
	
}

void HelloWorld::menuPauseCallback(Ref* pSender){
	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	if (dog_wangwang > 0){
		SimpleAudioEngine::getInstance()->pauseEffect(dog_wangwang);
	}
}

void HelloWorld::menuStopCallback(Ref* pSender){
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	SimpleAudioEngine::getInstance()->stopAllEffects();
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
bool HelloWorld::onTouchBegan(Touch *pTouch, Event *pEvent) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	log("visibleSize：w=%f,h=%f,", visibleSize.width, visibleSize.height);
	Vec2 v1 = pTouch->getLocation();//获取单击坐标，该坐标是基于3D的
	Vec2 v2 = pTouch->getLocationInView();//获取单击坐标，该坐标基于2D  以左上角为原点
	Vec2 v3 = Director::getInstance()->convertToUI(v2);//获取基于2d-x的坐标，也就是笛卡尔坐标
	
	log("click postion：x=%f,y=%f,", v1.x, v1.y);
	log("left up is ：x=%f,y=%f,", v2.x, v2.y);
	log("di ka er ：x=%f,y=%f,", v3.x, v3.y);
	log("HelloWorld::onTouchBegan");
	return true;
}
void HelloWorld::onTouchMoved(Touch *pTouch, Event *pEvent) {
	log("HelloWorld::onTouchMoved");
}
void HelloWorld::onTouchEnded(Touch *pTouch, Event *pEvent) {
	log("HelloWorld::onTouchEnded");
}
void HelloWorld::onTouchCancelled(Touch *touch, Event *unused_event) {
	log("HelloWorld::onTouchCancelled");
}