#pragma once

#ifndef Clock_ClockBackgroundScene
#define Clock_ClockBackgroundScene

#include<iostream>
#include"cocos2d.h"
#include"ClockHand.h"

USING_NS_CC;

class ClockBackgroundScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(ClockBackgroundScene);
	void getCurrentTime();
	void updateTime(float t);
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	virtual void onTouchCancelled(Touch *touch, Event *unused_event);
public:
	ClockHand *m_hour;
	ClockHand *m_minute;
	ClockHand *m_second;
public:
	int hour;
	int minute;
	int second;
};
#endif

