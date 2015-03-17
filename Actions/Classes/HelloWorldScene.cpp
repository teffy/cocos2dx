#include "HelloWorldScene.h"

#define ANDROIDAPPLE "androidapple"
#define LABEL "label"
#define TTF "fonts/fangzheng.ttf"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "..\cocos2d\iconv\include\iconv.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "..\cocos2d\external\win32-specific\icon\include\iconv.h"
#endif

#pragma comment(lib,"libiconv.lib")
#include "string"
using namespace std;

static int code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	iconv_t cd;
	const char *temp = inbuf;
	const char **pin = &temp;
	char **pout = &outbuf;
	memset(outbuf, 0, outlen);
	cd = iconv_open(to_charset, from_charset);
	if (cd == 0) return -1;
	if (iconv(cd, pin, &inlen, pout, &outlen) == -1) return -1;
	iconv_close(cd);
	return 0;
}

/*UTF8 to GB2312*/
static std::string utf2gbk(const char *inbuf)
{
	size_t inlen = strlen(inbuf);
	char * outbuf = new char[inlen * 2 + 2];
	std::string strRet;
	if (code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
	{
		strRet = outbuf;
	}
	delete[] outbuf;
	return strRet;
}

/*GB2312 to UTF8*/
static std::string gbk2utf8(const char *inbuf)
{
	size_t inlen = strlen(inbuf);
	char * outbuf = new char[inlen * 2 + 2];
	std::string strRet;
	if (code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
	{
		strRet = outbuf;
	}
	delete[] outbuf;
	return strRet;
}

static std::string getStringByKey(const char* key){
	Dictionary *strings = Dictionary::createWithContentsOfFile("fonts/strings.xml");
	return ((String*)strings->objectForKey(key))->getCString();
}

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	int x = 0;
	auto last = MenuItemFont::create("Last", CC_CALLBACK_1(HelloWorld::menuLastCallback, this));
	x = origin.x + last->getContentSize().width + 160;
	last->setPosition(Vec2(x, origin.y + last->getContentSize().height));

	auto restart = MenuItemFont::create("Restart", CC_CALLBACK_1(HelloWorld::menuRestartCallback, this));
	x += restart->getContentSize().width + 30;
	restart->setPosition(Vec2(x, origin.y + restart->getContentSize().height));

	auto next = MenuItemFont::create("Next", CC_CALLBACK_1(HelloWorld::menuNextCallback, this));
	x += next->getContentSize().width + 30;
	next->setPosition(Vec2(x, origin.y + next->getContentSize().height));
	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, last, restart, next, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	label = Label::createWithTTF("Hello World", TTF, 24);
	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1, LABEL);

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	androidapple = Sprite::create("res/androidapple.png");
	androidapple->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 2 - androidapple->getContentSize().height));
	this->addChild(androidapple, 0, ANDROIDAPPLE);

	actionDescriptions = new std::list<std::string>;

	auto scaleto = ScaleTo::create(2.0f, 2.0f, 0.5f);
	actionDescriptions->push_back(gbk2utf8("ScaleTo,缩放动画"));
	actions.pushBack(scaleto);

	auto place = Place::create(Vec2(visibleSize.width * 2 / 3, visibleSize.height / 2 - androidapple->getContentSize().height));
	actionDescriptions->push_back(getStringByKey("Place"));
	actions.pushBack(place);

	auto hide = Hide::create();
	actionDescriptions->push_back(getStringByKey("Hide"));
	actions.pushBack(hide);

	auto flipx = FlipX::create(true);
	actionDescriptions->push_back(getStringByKey("FlipX"));
	actions.pushBack(flipx);

	auto flipy = FlipY::create(true);
	actionDescriptions->push_back(getStringByKey("FlipY"));
	actions.pushBack(flipy);

	auto removeSelf = RemoveSelf::create();
	actionDescriptions->push_back(getStringByKey("RemoveSelf"));
	actions.pushBack(removeSelf);

	/* 不知道这个是干啥的，运行错误
	auto reuseGrid = ReuseGrid::create(100);
	actionDescriptions->push_back(getStringByKey("ReuseGrid"));
	actions.pushBack(reuseGrid);
	*/

	auto show = Show::create();
	actionDescriptions->push_back(getStringByKey("Show"));
	actions.pushBack(show);

	auto toggleVisibility = ToggleVisibility::create();
	actionDescriptions->push_back(getStringByKey("ToggleVisibility"));
	actions.pushBack(toggleVisibility);

	/*
	振幅动作，需要指定一个具有振幅属性的内部action，
	第一个参数 duration表示，波动总体时间，单位秒
	第二个参数 gridSize 表示 波动的整个区域 ，设置一个  宽 *  高  的 框。
	第三个参数waves是 希望总共波动多少次，次数。
	第四个参数 amplitude 相当于波动的振幅，波动范围。
	第五个参数 horizontal 如果为YES ,那么就是垂直波动，否则垂直不波动。
	第六个参数 vertical 如果为YES,那么就是水平波动，否则水平不波动。
	auto wave = CCWaves::create(2,androidapple->getContentSize(),5,5,true,true);
	auto accelAmplitude = AccelAmplitude::create(wave, 2);
	actionDescriptions->push_back(getStringByKey("AccelAmplitude"));
	actions.pushBack(accelAmplitude);
	// AccelDeccelAmplitude振幅动作
	*/

	//作用：创建一个球面坐标轨迹进行旋转的动作
	//参数1：旋转轨迹的时间
	//参数2：起始半径
	//参数3：半径差
	//参数4：起始z角
	//参数5：旋转z角的差
	//参数6：起始x角
	//参数7：旋转x角的差
	auto orbitCamera = OrbitCamera::create(3, 10, 0, 45, 180, 90, 0);
	actionDescriptions->push_back(getStringByKey("OrbitCamera"));
	actions.pushBack(orbitCamera);

	/*
	http://www.cnblogs.com/AlexLiu/archive/2010/01/24/1655325.html
	Actions: Ease,缓冲操作,是一个特殊的复杂操作，可以改变inner 动作的时间。在Flash里面，它们经常被称作Tweening 或者Easing 动作。
	可以对inner的action进行加速或者是减速。

	这些action可以被分成3类：
	In actions: action开始的时候加速
	Out actions: action结束的时候加速
	InOut actions: action开始，结束的时候加速
	*/
	auto easeBackIn = EaseBackIn::create(orbitCamera);
	actionDescriptions->push_back(getStringByKey("EaseBackIn"));
	actions.pushBack(easeBackIn);

	auto easeBackOut = EaseBackOut::create(orbitCamera);
	actionDescriptions->push_back(getStringByKey("EaseBackOut"));
	actions.pushBack(easeBackOut);

	auto easeBackInOut = EaseBackInOut::create(orbitCamera);
	actionDescriptions->push_back(getStringByKey("EaseBackInOut"));
	actions.pushBack(easeBackInOut);

	auto easeBezierAction = EaseBezierAction::create(scaleto);
	actionDescriptions->push_back(getStringByKey("EaseBezierAction"));
	actions.pushBack(easeBezierAction);

	auto easeBounceIn = EaseBounceIn::create(scaleto);
	actionDescriptions->push_back(getStringByKey("EaseBounceIn"));
	actions.pushBack(easeBounceIn);

	auto easeBounceOut = EaseBounceOut::create(scaleto);
	actionDescriptions->push_back(getStringByKey("EaseBounceOut"));
	actions.pushBack(easeBounceOut);

	auto easeBounceInOut = EaseBounceInOut::create(scaleto);
	actionDescriptions->push_back(getStringByKey("EaseBounceInOut"));
	actions.pushBack(easeBounceInOut);

	auto easeCircleActionIn = EaseCircleActionIn::create(scaleto);
	actionDescriptions->push_back(getStringByKey("EaseCircleActionIn"));
	actions.pushBack(easeCircleActionIn);

	auto easeCircleActionInOut = EaseCircleActionInOut::create(scaleto);
	actionDescriptions->push_back(getStringByKey("EaseCircleActionInOut"));
	actions.pushBack(easeCircleActionInOut);

	auto easeCircleActionOut = EaseCircleActionOut::create(scaleto);
	actionDescriptions->push_back(getStringByKey("EaseCircleActionOut"));
	actions.pushBack(easeCircleActionOut);

	auto easeElasticIn = EaseElasticIn::create(scaleto);
	actionDescriptions->push_back(getStringByKey("EaseElasticIn"));
	actions.pushBack(easeElasticIn);

	auto easeElasticInOut = EaseElasticInOut::create(scaleto);
	actionDescriptions->push_back(getStringByKey("EaseElasticInOut"));
	actions.pushBack(easeElasticInOut);

	auto easeElasticOut = EaseElasticOut::create(scaleto);
	actionDescriptions->push_back(getStringByKey("EaseElasticOut"));
	actions.pushBack(easeElasticOut);

	auto easeExponentialIn = EaseExponentialIn::create(scaleto);
	actionDescriptions->push_back(getStringByKey("EaseExponentialIn"));
	actions.pushBack(easeExponentialIn);

	auto easeExponentialInOut = EaseExponentialInOut::create(scaleto);
	actionDescriptions->push_back(getStringByKey("EaseExponentialInOut"));
	actions.pushBack(easeExponentialInOut);

	auto easeExponentialOut = EaseExponentialOut::create(scaleto);
	actionDescriptions->push_back(getStringByKey("EaseExponentialOut"));
	actions.pushBack(easeExponentialOut);

	auto easeQuadraticActionIn = EaseQuadraticActionIn::create(scaleto);
	actionDescriptions->push_back(getStringByKey("EaseQuadraticActionIn"));
	actions.pushBack(easeQuadraticActionIn);

	auto easeQuadraticActionInOut = EaseQuadraticActionInOut::create(scaleto);
	actionDescriptions->push_back(getStringByKey("EaseQuadraticActionInOut"));
	actions.pushBack(easeQuadraticActionInOut);

	auto easeQuadraticActionOut = EaseQuadraticActionOut::create(scaleto);
	actionDescriptions->push_back(getStringByKey("EaseQuadraticActionOut"));
	actions.pushBack(easeQuadraticActionOut);

	auto easeIn = EaseIn::create(scaleto, 3.0f);
	actionDescriptions->push_back(getStringByKey("EaseIn"));
	actions.pushBack(easeIn);

	auto easeInOut = EaseInOut::create(scaleto, 3.0f);
	actionDescriptions->push_back(getStringByKey("EaseInOut"));
	actions.pushBack(easeIn);

	auto easeOut = EaseOut::create(scaleto, 3.0f);
	actionDescriptions->push_back(getStringByKey("EaseOut"));
	actions.pushBack(easeOut);

	auto easeSineIn = EaseSineIn::create(scaleto);
	actionDescriptions->push_back(getStringByKey("EaseSineIn"));
	actions.pushBack(easeSineIn);

	auto easeSineInOut = EaseSineInOut::create(scaleto);
	actionDescriptions->push_back(getStringByKey("EaseSineInOut"));
	actions.pushBack(easeSineInOut);

	auto easeSineOut = EaseSineOut::create(scaleto);
	actionDescriptions->push_back(getStringByKey("EaseSineOut"));
	actions.pushBack(easeSineOut);

	// CCBEaseInstant
	/*
	auto actionTween = ActionTween::create(3, "width", 400, 100);
	actionDescriptions->push_back(getStringByKey("ActionTween"));
	actions.pushBack(actionTween);
	*/

	// Animate前面 《Cocos2d学习之路》三，学习使用TexturePacker创建动画效果，已经用到过 http://blog.csdn.net/lsmfeixiang/article/details/42214027
	
	ccBezierConfig bezierConfig;
	bezierConfig.controlPoint_1 = Vec2(150,50);
	bezierConfig.controlPoint_2 = Vec2(250, 450);
	bezierConfig.endPosition = Vec2(710, 230);
	auto bezierBy = BezierBy::create(3, bezierConfig);
	actionDescriptions->push_back(getStringByKey("BezierBy"));
	actions.pushBack(bezierBy);

	auto blink = Blink::create(3, 10);
	actionDescriptions->push_back(getStringByKey("Blink"));
	actions.pushBack(blink);

	PointArray * pointArray = PointArray::create(20);
	pointArray->addControlPoint(Vec2(100, 100));
	pointArray->addControlPoint(Vec2(310, 100));
	pointArray->addControlPoint(Vec2(310, 340));
	pointArray->addControlPoint(Vec2(100, 260));
	pointArray->addControlPoint(Vec2(100, 100));

	auto catmullRomTo = CatmullRomTo::create(3, pointArray);
	actionDescriptions->push_back(getStringByKey("CatmullRomTo"));
	actions.pushBack(catmullRomTo);

	auto catmullRomBy = CatmullRomBy::create(3, pointArray);
	actionDescriptions->push_back(getStringByKey("CatmullRomBy"));
	actions.pushBack(catmullRomBy);

	auto cardinalSplineBy = CardinalSplineBy::create(3, pointArray, 1);
	actionDescriptions->push_back(getStringByKey("CardinalSplineBy"));
	actions.pushBack(cardinalSplineBy);

	/*
	auto deccelAmplitude = DeccelAmplitude::create(catmullRomBy, 3);
	actionDescriptions->push_back(getStringByKey("DeccelAmplitude"));
	actions.pushBack(deccelAmplitude);
	*/

	//DelayTime,在下面的按钮回调函数中有使用到

	auto fadeTo = FadeTo::create(5, 20);
	actionDescriptions->push_back(getStringByKey("FadeTo"));
	actions.pushBack(fadeTo);

	auto fadeOut = FadeOut::create(2);
	actionDescriptions->push_back(getStringByKey("FadeOut"));
	actions.pushBack(fadeOut);

	auto fadeIn = FadeIn::create(2);
	actionDescriptions->push_back(getStringByKey("FadeIn"));
	actions.pushBack(fadeIn);

	auto jumpBy = JumpBy::create(3, Vec2(400, 500), 30, 5);
	actionDescriptions->push_back(getStringByKey("JumpBy"));
	actions.pushBack(jumpBy);

	auto jumpTo = JumpTo::create(3, Vec2(400, 500), 30, 5);
	actionDescriptions->push_back(getStringByKey("JumpTo"));
	actions.pushBack(jumpTo);

	auto moveBy = MoveBy::create(3, Vec2(500, 200));
	actionDescriptions->push_back(getStringByKey("MoveBy"));
	actions.pushBack(moveBy);

	auto moveTo = MoveTo::create(3, Vec2(500, 200));
	actionDescriptions->push_back(getStringByKey("MoveTo"));
	actions.pushBack(moveTo);

	/*
	auto progressFromTo = ProgressFromTo::create(3, 10, 100);
	actionDescriptions->push_back(getStringByKey("ProgressFromTo"));
	actions.pushBack(progressFromTo);
	*/

	auto progressTo = ProgressTo::create(3, 65);
	actionDescriptions->push_back(getStringByKey("ProgressTo"));
	actions.pushBack(progressTo);

	auto repeat = Repeat::create(orbitCamera, 2);
	actionDescriptions->push_back(getStringByKey("Repeat"));
	actions.pushBack(repeat);

	auto repeatForever = RepeatForever::create(scaleto);
	actionDescriptions->push_back(getStringByKey("RepeatForever"));
	actions.pushBack(repeatForever);

	auto reverseTime = ReverseTime::create(orbitCamera);
	actionDescriptions->push_back(getStringByKey("ReverseTime"));
	actions.pushBack(reverseTime);

	auto rotateBy = RotateBy::create(1.0, 90);
	actionDescriptions->push_back(getStringByKey("RotateBy"));
	actions.pushBack(rotateBy);

	auto rotateTo = RotateTo::create(1.0,215);
	actionDescriptions->push_back(getStringByKey("RotateTo"));
	actions.pushBack(rotateTo);

	/*
	auto sequence = Sequence::create(rotateTo, scaleto);
	actionDescriptions->push_back(getStringByKey("Sequence"));
	actions.pushBack(sequence);
	*/

	auto skewTo = SkewTo::create(2,4.0f, 12.0f);
	actionDescriptions->push_back(getStringByKey("SkewTo"));
	actions.pushBack(skewTo);

	auto skewBy = SkewBy::create(2, 4.0f, 12.0f);
	actionDescriptions->push_back(getStringByKey("SkewBy"));
	actions.pushBack(skewBy);

	auto targetedAction = TargetedAction::create(sprite, skewBy);
	actionDescriptions->push_back(getStringByKey("TargetedAction"));
	actions.pushBack(targetedAction);

	auto tintBy = TintBy::create(3, 125, 95, 254);
	actionDescriptions->push_back(getStringByKey("TintBy"));
	actions.pushBack(tintBy);

	auto tintTo = TintTo::create(3, 125, 95, 254);
	actionDescriptions->push_back(getStringByKey("TintTo"));
	actions.pushBack(tintTo);

	/*
	auto jumpTiles3D = JumpTiles3D::create(2, androidapple->getContentSize(), 5, 0);
	actionDescriptions->push_back(getStringByKey("JumpTiles3D"));
	actions.pushBack(jumpTiles3D);

	auto liquid = Liquid::create(2, androidapple->getContentSize(), 5, 0);
	actionDescriptions->push_back(getStringByKey("Liquid"));
	actions.pushBack(liquid);
	*/

	index = 0;
	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::menuLastCallback(Ref* pSender){
	this->removeChildByName(ANDROIDAPPLE, true);
	androidapple = Sprite::create("res/androidapple.png");
	androidapple->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 2 - androidapple->getContentSize().height));
	this->addChild(androidapple, 0, ANDROIDAPPLE);

	currentAction = actions.at(index);
	androidapple->runAction(Sequence::create(DelayTime::create(0.5f), currentAction, NULL));

	std::list<std::string>::iterator it = actionDescriptions->begin();
	for (int i = 0; i < index; ++i) {
		++it;
	}
	this->removeChildByName(LABEL, true);
	log("%s", ((std::string) *it).c_str());
	label = Label::createWithTTF(((std::string) *it).c_str(), TTF, 24);
	label->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1, LABEL);

	if (--index < 0){
		index = actions.size() - 1;
	}
}
void HelloWorld::menuRestartCallback(Ref* pSender){
	if (currentAction != NULL){
		this->removeChildByName(ANDROIDAPPLE, true);
		androidapple = Sprite::create("res/androidapple.png");
		androidapple->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 2 - androidapple->getContentSize().height));
		this->addChild(androidapple, 0, ANDROIDAPPLE);
		androidapple->runAction(Sequence::create(DelayTime::create(0.5f), currentAction, NULL));
	}
}
void HelloWorld::menuNextCallback(Ref* pSender){
	//不知道怎样使sprite恢复到原始状态，只能用最笨的方法了，remove掉，然后重新加载一个进来
	this->removeChildByName(ANDROIDAPPLE, true);
	androidapple = Sprite::create("res/androidapple.png");
	androidapple->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 2 - androidapple->getContentSize().height));
	this->addChild(androidapple, 0, ANDROIDAPPLE);

	//DelayTime::create(1);//为了明细的看出效果，延后0.5秒
	//Sequence::create//动作组合，顺序执行，NULL是结束
	currentAction = actions.at(index);
	androidapple->runAction(Sequence::create(DelayTime::create(0.5f), currentAction, NULL));

	std::list<std::string>::iterator it = actionDescriptions->begin();
	for (int i = 0; i < index; ++i) {
		++it;
	}
	this->removeChildByName(LABEL, true);
	log("%s", ((std::string) *it).c_str());
	label = Label::createWithTTF(((std::string) *it).c_str(), TTF, 24);
	label->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1, LABEL);

	// 检测index，以防越界
	if (++index >= actions.size()){
		index = 0;
	}
}