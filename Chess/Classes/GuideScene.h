#pragma once
#include "cocos2d.h"

USING_NS_CC;

class GuideScene : public cocos2d::Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GuideScene);
	virtual bool onTouchBegan(Touch* mTouch, Event* mEvent);
	virtual void onTouchMoved(Touch* mTouch, Event* mEvent);
	virtual void onTouchEnded(Touch* mTouch, Event* mEvent);
	virtual void onTouchCancelled(Touch* mTouch, Event* mEvent);
	virtual void update(float delta);
public:
	Sprite* jiang;
	Sprite* shuai;
	bool clickRed;
};

