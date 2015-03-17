#include "GuideScene.h"
#include "GameScene.h"

static std::string getStringByKey(const char* key){
	Dictionary *strings = Dictionary::createWithContentsOfFile("fonts/strings.xml");
	return ((String*)strings->objectForKey(key))->getCString();
}

Scene* GuideScene::createScene(){
	Scene* scene = Scene::create();
	Layer* layer = GuideScene::create();
	scene->addChild(layer);
	return scene;
}

bool GuideScene::init(){
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getWinSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/*
	Label* guideStart = Label::createWithTTF(getStringByKey("GuideStart"), "res/fangzheng.ttf", 20);
	guideStart->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - guideStart->getContentSize().height));
	this->addChild(guideStart, 1);
	*/
	
	jiang = Sprite::create("res/bkg1.png");
	jiang->setPosition(Vec2(visibleSize.width / 2 - jiang->getContentSize().width * 2, visibleSize.height / 2));

	this->addChild(jiang);
	shuai = Sprite::create("res/bkg2.png");
	shuai->setPosition(Vec2(visibleSize.width / 2 + shuai->getContentSize().width * 2, visibleSize.height / 2));
	this->addChild(shuai);

	EventListenerTouchOneByOne* touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GuideScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GuideScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GuideScene::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(GuideScene::onTouchCancelled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, jiang);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener->clone(), shuai);

	return true;
}

bool GuideScene::onTouchBegan(Touch* mTouch, Event* mEvent){
	return true;
}

void GuideScene::onTouchMoved(Touch* mTouch, Event* mEvent){
}
void GuideScene::onTouchCancelled(Touch* mTouch, Event* mEvent){
}
void GuideScene::onTouchEnded(Touch* mTouch, Event* mEvent){
	Vec2 touchLocation = mTouch->getLocation();
	bool isClicked = false;
	if (jiang->getBoundingBox().containsPoint(touchLocation) 
		|| shuai->getBoundingBox().containsPoint(touchLocation)){
		isClicked = true;
		clickRed = shuai->getBoundingBox().containsPoint(touchLocation) ? true : false;//判断，点击的是黑棋还是红棋
	}
	else{
		isClicked = false;
	}
	if (isClicked){
		int duration = 1;
		Size winSize = Director::getInstance()->getWinSize();
		MoveTo* moveTo = MoveTo::create(duration, Vec2(winSize.width / 2, winSize.height / 2));
		RotateBy* rotateBy = RotateBy::create(duration, 360);

		Spawn* jiangAction = Spawn::create(moveTo, rotateBy, NULL);
		Spawn* shuaiAction = Spawn::create(moveTo->clone(), rotateBy->clone()->reverse(), NULL);

		jiang->runAction(jiangAction);
		shuai->runAction(shuaiAction);

		scheduleUpdate();
	}
}

void GuideScene::update(float delta){
	float jiang_x = jiang->getPositionX();
	float shuai_x = shuai->getPositionX();
	if (abs(jiang_x - shuai_x) < jiang->getContentSize().width){
		Director::getInstance()->replaceScene(GameScene::createScene(clickRed));
	}
}