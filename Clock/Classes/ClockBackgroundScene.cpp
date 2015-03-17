#include "ClockBackgroundScene.h"

Scene* ClockBackgroundScene::createScene() {
	auto scene = Scene::create();
	auto layer = ClockBackgroundScene::create();
	scene->addChild(layer);
	return scene;
}
bool ClockBackgroundScene::init() {
	if (!Layer::init()) {
		return true;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto closeItem = MenuItemImage::create("res/CloseNormal.png","res/CloseSelected.png",CC_CALLBACK_1(ClockBackgroundScene::menuCloseCallback,this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width,
		origin.y + closeItem->getContentSize().height));
	auto menu = Menu::create(closeItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,1);

	auto clockbg = Sprite::create("res/background.jpg");
	clockbg->setPosition(Vec2((origin.x + visibleSize.width) / 2, (origin.y + visibleSize.height) / 2));
	clockbg->setScale(0.5f);
	this->addChild(clockbg,1);

	m_hour = ClockHand::create();
	m_hour->bindSprite(Sprite::create("res/shi.png"));
	m_hour->setPosition(Vec2((origin.x + visibleSize.width) / 2, (origin.y + visibleSize.height) / 2));
	this->addChild(m_hour,1);

	m_minute = ClockHand::create();
	m_minute->bindSprite(Sprite::create("res/fen.png"));
	m_minute->setPosition(Vec2((origin.x + visibleSize.width) / 2, (origin.y + visibleSize.height) / 2));
	this->addChild(m_minute,1);

	m_second = ClockHand::create();
	m_second->bindSprite(CCSprite::create("res/miao.png"));
	m_second->setPosition(Vec2((origin.x + visibleSize.width) / 2, (origin.y + visibleSize.height) / 2));
	this->addChild(m_second,1);

	this->schedule(schedule_selector(ClockBackgroundScene::updateTime), 1);
	// http://tonybai.com/2014/04/23/changes-in-cocos2dx-3-rc2-for-android/
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ClockBackgroundScene::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(ClockBackgroundScene::onTouchMoved,this);
	listener->onTouchCancelled = CC_CALLBACK_2(ClockBackgroundScene::onTouchCancelled,this);
	listener->onTouchEnded = CC_CALLBACK_2(ClockBackgroundScene::onTouchEnded,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
	return true;
}

void ClockBackgroundScene::menuCloseCallback(Ref* pSender)
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
void ClockBackgroundScene::getCurrentTime() {
	struct tm *tm;
	time_t timep;
	time(&timep);
	tm = localtime(&timep);
	hour = tm->tm_hour;
	minute = tm->tm_min;
	second = tm->tm_sec;
}

void ClockBackgroundScene::updateTime(float t) {
	getCurrentTime();
	log("time is %d:%d:%d", hour, minute, second);
	static int mRotation = minute * 6;
	static int sRotation = second * 6;
	static int hRotation;
	if (hour > 12) {
		hRotation = (hour - 12) * 5 * 6 + (mRotation / 72) * 6;
	} else {
		hRotation = hour * 5 * 6 + (mRotation / 72) * 6;
	}

	m_second->setRotation(sRotation);
	m_minute->setRotation(mRotation);
	m_hour->setRotation(hRotation);

	if (sRotation > 360) {
		sRotation = 0;
		mRotation += 6;
		m_minute->setRotation(mRotation);
		if (mRotation % 72 == 0) {
			hRotation += 6;
			m_hour->setRotation(hRotation);
			if (mRotation >= 360) {
				mRotation = 0;
			}
		}
	}
	sRotation += 6;
}

bool ClockBackgroundScene::onTouchBegan(Touch *pTouch, Event *pEvent) {
	log("ClockBackgroundScene::onTouchBegan");
	return true;
}
void ClockBackgroundScene::onTouchMoved(Touch *pTouch, Event *pEvent) {
	log("ClockBackgroundScene::onTouchMoved");
}
void ClockBackgroundScene::onTouchEnded(Touch *pTouch, Event *pEvent) {
	log("ClockBackgroundScene::onTouchEnded");
}
void ClockBackgroundScene::onTouchCancelled(Touch *touch, Event *unused_event) {
	log("ClockBackgroundScene::onTouchCancelled");
}
