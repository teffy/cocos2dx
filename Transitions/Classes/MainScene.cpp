#include "MainScene.h"

USING_NS_CC;

/*-------------------------------Transition-----------------------------------------*/
class MTransitionCrossFade : TransitionCrossFade{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionCrossFade::create(duration, scene);
	}
};

class MTransitionFade : TransitionFade{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionFade::create(duration, scene);
	}
};

class MTransitionFadeTR : TransitionFadeTR{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionFadeTR::create(duration, scene);
	}
};

class MTransitionFadeBL : TransitionFadeBL{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionFadeBL::create(duration, scene);
	}
};

class MTransitionFadeDown : TransitionFadeDown{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionFadeDown::create(duration, scene);
	}
};

class MTransitionFadeUp : TransitionFadeUp{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionFadeUp::create(duration, scene);
	}
};

class MTransitionJumpZoom : TransitionJumpZoom{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionJumpZoom::create(duration, scene);
	}
};
class MTransitionFlipAngular_DOWN : TransitionFlipAngular{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionFlipAngular::create(duration, scene,
			TransitionScene::Orientation::DOWN_OVER);
	}
};
class MTransitionFlipAngular_LEFT : TransitionFlipAngular{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionFlipAngular::create(duration, scene,
			TransitionScene::Orientation::LEFT_OVER);
	}
};
class MTransitionFlipAngular_RIGHT : TransitionFlipAngular{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionFlipAngular::create(duration, scene,
			TransitionScene::Orientation::RIGHT_OVER);
	}
};
class MTransitionFlipAngular_UP : TransitionFlipAngular{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionFlipAngular::create(duration, scene,
			TransitionScene::Orientation::UP_OVER);
	}
};

class MTransitionFlipX_DOWN : TransitionFlipX{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionFlipX::create(duration, scene,
			TransitionScene::Orientation::DOWN_OVER);
	}
};
class MTransitionFlipX_LEFT : TransitionFlipX{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionFlipX::create(duration, scene,
			TransitionScene::Orientation::LEFT_OVER);
	}
};
class MTransitionFlipX_RIGHT : TransitionFlipX{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionFlipX::create(duration, scene,
			TransitionScene::Orientation::RIGHT_OVER);
	}
};
class MTransitionFlipX_UP : TransitionFlipX{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionFlipX::create(duration, scene,
			TransitionScene::Orientation::UP_OVER);
	}
};

class MTransitionFlipY_DOWN : TransitionFlipY{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionFlipY::create(duration, scene,
			TransitionScene::Orientation::DOWN_OVER);
	}
};
class MTransitionFlipY_LEFT : TransitionFlipY{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionFlipY::create(duration, scene,
			TransitionScene::Orientation::LEFT_OVER);
	}
};
class MTransitionFlipY_RIGHT : TransitionFlipY{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionFlipY::create(duration, scene,
			TransitionScene::Orientation::RIGHT_OVER);
	}
};
class MTransitionFlipY_UP : TransitionFlipY{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionFlipY::create(duration, scene,
			TransitionScene::Orientation::UP_OVER);
	}
};
class MTransitionZoomFlipAngular : TransitionZoomFlipAngular{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionZoomFlipAngular::create(duration, scene);
	}
};

class MTransitionZoomFlipX_DOWN : TransitionZoomFlipX{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionZoomFlipX::create(duration, scene,
			TransitionScene::Orientation::DOWN_OVER);
	}
};
class MTransitionZoomFlipX_LEFT : TransitionZoomFlipX{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionZoomFlipX::create(duration, scene,
			TransitionScene::Orientation::LEFT_OVER);
	}
};
class MTransitionZoomFlipX_RIGHT : TransitionZoomFlipX{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionZoomFlipX::create(duration, scene,
			TransitionScene::Orientation::RIGHT_OVER);
	}
};
class MTransitionZoomFlipX_UP : TransitionZoomFlipX{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionZoomFlipX::create(duration, scene,
			TransitionScene::Orientation::UP_OVER);
	}
};

class MTransitionZoomFlipY_DOWN : TransitionZoomFlipY{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionZoomFlipY::create(duration, scene,
			TransitionScene::Orientation::DOWN_OVER);
	}
};
class MTransitionZoomFlipY_LEFT : TransitionZoomFlipY{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionZoomFlipY::create(duration, scene,
			TransitionScene::Orientation::LEFT_OVER);
	}
};
class MTransitionZoomFlipY_RIGHT : TransitionZoomFlipY{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionZoomFlipY::create(duration, scene,
			TransitionScene::Orientation::RIGHT_OVER);
	}
};
class MTransitionZoomFlipY_UP : TransitionZoomFlipY{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionZoomFlipY::create(duration, scene,
			TransitionScene::Orientation::UP_OVER);
	}
};
class MTransitionShrinkGrow : TransitionShrinkGrow{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionShrinkGrow::create(duration, scene);
	}
};
class MTransitionSlideInL : TransitionSlideInL{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionSlideInL::create(duration, scene);
	}
};
class MTransitionSlideInB : TransitionSlideInB{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionSlideInB::create(duration, scene);
	}
};
class MTransitionSlideInR : TransitionSlideInR{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionSlideInR::create(duration, scene);
	}
};
class MTransitionSlideInT : TransitionSlideInT{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionSlideInT::create(duration, scene);
	}
};
class MTransitionSplitCols : TransitionSplitCols{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionSplitCols::create(duration, scene);
	}
};
class MTransitionSplitRows : TransitionSplitRows{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionSplitRows::create(duration, scene);
	}
};
class MTransitionTurnOffTiles : TransitionTurnOffTiles{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionTurnOffTiles::create(duration, scene);
	}
};

class MTransitionProgressHorizontal : TransitionProgressHorizontal{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionProgressHorizontal::create(duration, scene);
	}
};

class MTransitionProgressInOut : TransitionProgressInOut{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionProgressInOut::create(duration, scene);
	}
};

class MTransitionProgressOutIn : TransitionProgressOutIn{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionProgressOutIn::create(duration, scene);
	}
};

class MTransitionProgressRadialCCW : TransitionProgressRadialCCW{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionProgressRadialCCW::create(duration, scene);
	}
};

class MTransitionProgressRadialCW : TransitionProgressRadialCW{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionProgressRadialCW::create(duration, scene);
	}
};

class MTransitionProgressVertical : TransitionProgressVertical{
public:
	static TransitionScene* create(float duration, Scene* scene){
		return TransitionProgressVertical::create(duration, scene);
	}
};

#define DURATION 1.5f
#define STRINGIFY(x) #x
#define TRANS(__classname__){\
[](float t, Scene* s){ return __classname__::create(t,s);},\
STRINGIFY(__classname__),\
}

struct  transitions{
	std::function<TransitionScene*(float t, Scene* s)> function;
	const char* name;
}transitions[] = {
	TRANS(MTransitionCrossFade),
	TRANS(MTransitionFade),
	TRANS(MTransitionFadeTR),
	TRANS(MTransitionFadeBL),
	TRANS(MTransitionFadeDown),
	TRANS(MTransitionFadeUp),
	TRANS(MTransitionJumpZoom),
	TRANS(MTransitionFlipAngular_DOWN),
	TRANS(MTransitionFlipAngular_LEFT),
	TRANS(MTransitionFlipAngular_RIGHT),
	TRANS(MTransitionFlipAngular_UP),
	TRANS(MTransitionFlipX_DOWN),
	TRANS(MTransitionFlipX_LEFT),
	TRANS(MTransitionFlipX_RIGHT),
	TRANS(MTransitionFlipX_UP),
	TRANS(MTransitionFlipY_DOWN),
	TRANS(MTransitionFlipY_LEFT),
	TRANS(MTransitionFlipY_RIGHT),
	TRANS(MTransitionFlipY_UP),
	TRANS(MTransitionZoomFlipAngular),
	TRANS(MTransitionZoomFlipX_DOWN),
	TRANS(MTransitionZoomFlipX_LEFT),
	TRANS(MTransitionZoomFlipX_RIGHT),
	TRANS(MTransitionZoomFlipX_UP),
	TRANS(MTransitionZoomFlipY_DOWN),
	TRANS(MTransitionZoomFlipY_LEFT),
	TRANS(MTransitionZoomFlipY_RIGHT),
	TRANS(MTransitionZoomFlipY_UP),
	TRANS(MTransitionShrinkGrow),
	TRANS(MTransitionSlideInL),
	TRANS(MTransitionSlideInB),
	TRANS(MTransitionSlideInR),
	TRANS(MTransitionSplitCols),
	TRANS(MTransitionSplitRows),
	TRANS(MTransitionTurnOffTiles),
	TRANS(MTransitionProgressHorizontal),
	TRANS(MTransitionProgressInOut),
	TRANS(MTransitionProgressOutIn),
	TRANS(MTransitionProgressRadialCCW),
	TRANS(MTransitionProgressRadialCW),
	TRANS(MTransitionProgressVertical),
};

static int transition_index = 0;

#define MAX_TRANSITION_COUNT (sizeof(transitions)/sizeof(transitions[0]))

TransitionScene* createTranstion(int _index,float t,Scene* s){
	//Director::getInstance()->setDepthTest(false);
	return transitions[_index].function(t, s);
}
/*-------------------------------Transition-----------------------------------------*/

/*-------------------------------MainScene-----------------------------------------*/
Scene* MainScene::createScene(){
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}
bool MainScene::init(){
	if (!Layer::init()) {
		return false;
	}
	log("index->%d,max->%d",transition_index, MAX_TRANSITION_COUNT);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto closeItem = MenuItemImage::create(
		"res/CloseNormal.png",
		"res/CloseSelected.png",
		CC_CALLBACK_1(MainScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	MenuItemImage* restart = MenuItemImage::create("res/r1.png", "res/r2.png", CC_CALLBACK_1(MainScene::menuRestartCallback, this));
	restart->setPosition(Vec2(visibleSize.width / 2 + 100, visibleSize.height / 2 - 100));
	auto menu = Menu::create(closeItem, restart, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto sprite = Sprite::create("res/HelloWorld.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);
	return true;
}

void MainScene::menuCloseCallback(Ref* pSender)
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

void MainScene::menuRestartCallback(Ref* pSender){
	Scene* s = MainScene::createScene();
	Layer* layer = new LayerOne();
	s->addChild(layer);
	auto scene = createTranstion(transition_index, DURATION, s);
	if (scene){
		Director::getInstance()->replaceScene(scene);
	}
}
/*-------------------------------MainScene-----------------------------------------*/

/*-------------------------------LayerOne-----------------------------------------*/
LayerOne::LayerOne(){
	init();
}
LayerOne::~LayerOne(){}
bool LayerOne::init(){
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	MenuItemImage* restart = MenuItemImage::create("res/r1.png", "res/r2.png", CC_CALLBACK_1(LayerOne::menuRestartCallback, this));
	restart->setPosition(Vec2(visibleSize.width / 2, restart->getContentSize().height));
	MenuItemImage* back = MenuItemImage::create("res/b1.png", "res/b2.png", CC_CALLBACK_1(LayerOne::menuBackCallback, this));
	back->setPosition(Vec2(visibleSize.width / 2 - restart->getContentSize().width*1.5, back->getContentSize().height));
	MenuItemImage* forward = MenuItemImage::create("res/f1.png", "res/f2.png", CC_CALLBACK_1(LayerOne::menuForwardCallback, this));
	forward->setPosition(Vec2(visibleSize.width / 2 + restart->getContentSize().width*1.5, forward->getContentSize().height));
	auto menu = Menu::create(restart, back, forward, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto label = Label::createWithTTF("LayerOne", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);
	auto transitionName = Label::createWithTTF(transitions[transition_index].name, "fonts/Marker Felt.ttf", 24);
	transitionName->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - transitionName->getContentSize().height * 2));
	this->addChild(transitionName, 1);
	auto sprite = Sprite::create("res/background1.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);
	return true;
}

void LayerOne::menuRestartCallback(Ref* pSender){
	Scene* s = MainScene::createScene();
	Layer* layer = new LayerTwo();
	s->addChild(layer);
	auto scene = createTranstion(transition_index, DURATION, s);
	if (scene){
		Director::getInstance()->replaceScene(scene);
	}
}

void LayerOne::menuBackCallback(Ref* pSender){
	transition_index--;
	if (transition_index < 0){
		transition_index += MAX_TRANSITION_COUNT;
	}
	Scene* s = MainScene::createScene();
	Layer* layer = new LayerTwo();
	s->addChild(layer);
	auto scene = createTranstion(transition_index, DURATION, s);
	if (scene){
		Director::getInstance()->replaceScene(scene);
	}
}

void LayerOne::menuForwardCallback(Ref* pSender){
	transition_index++;
	transition_index = transition_index % MAX_TRANSITION_COUNT;
	Scene* s = MainScene::createScene();
	Layer* layer = new LayerTwo();
	s->addChild(layer);
	auto scene = createTranstion(transition_index, DURATION, s);
	if (scene){
		Director::getInstance()->replaceScene(scene);
	}
}
/*-------------------------------LayerOne-----------------------------------------*/


/*-------------------------------LayerTwo-----------------------------------------*/
LayerTwo::LayerTwo(){
	init();
}
LayerTwo::~LayerTwo(){

}
bool LayerTwo::init(){
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	MenuItemImage* restart = MenuItemImage::create("res/r1.png", "res/r2.png", CC_CALLBACK_1(LayerTwo::menuRestartCallback, this));
	restart->setPosition(Vec2(visibleSize.width / 2, restart->getContentSize().height));
	MenuItemImage* back = MenuItemImage::create("res/b1.png", "res/b2.png", CC_CALLBACK_1(LayerTwo::menuBackCallback, this));
	back->setPosition(Vec2(visibleSize.width / 2 - restart->getContentSize().width*1.5, back->getContentSize().height));
	MenuItemImage* forward = MenuItemImage::create("res/f1.png", "res/f2.png", CC_CALLBACK_1(LayerTwo::menuForwardCallback, this));
	forward->setPosition(Vec2(visibleSize.width / 2 + restart->getContentSize().width*1.5, forward->getContentSize().height));
	auto menu = Menu::create(restart, back, forward, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto label = Label::createWithTTF("LayerTwo", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);
	auto transitionName = Label::createWithTTF(transitions[transition_index].name, "fonts/Marker Felt.ttf", 24);
	transitionName->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - transitionName->getContentSize().height*2));
	this->addChild(transitionName, 1);
	auto sprite = Sprite::create("res/background2.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);
	return true;
}


void LayerTwo::menuRestartCallback(Ref* pSender){
	Scene* s = MainScene::createScene();
	Layer* layer = new LayerOne();
	s->addChild(layer);
	auto scene = createTranstion(transition_index, DURATION, s);
	if (scene){
		Director::getInstance()->replaceScene(scene);
	}
}

void LayerTwo::menuBackCallback(Ref* pSender){
	transition_index--;
	if (transition_index < 0){
		transition_index += MAX_TRANSITION_COUNT;
	}
	Scene* s = MainScene::createScene();
	Layer* layer = new LayerOne();
	s->addChild(layer);
	auto scene = createTranstion(transition_index, DURATION, s);
	if (scene){
		Director::getInstance()->replaceScene(scene);
	}
}

void LayerTwo::menuForwardCallback(Ref* pSender){
	transition_index++;
	transition_index = transition_index % MAX_TRANSITION_COUNT;
	Scene* s = MainScene::createScene();
	Layer* layer = new LayerOne();
	s->addChild(layer);
	auto scene = createTranstion(transition_index, DURATION, s);
	if (scene){
		Director::getInstance()->replaceScene(scene);
	}
}
/*-------------------------------LayerTwo-----------------------------------------*/
