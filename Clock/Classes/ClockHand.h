#pragma once

#ifndef _ClockHand_
#define _ClockHand_

#include<iostream>
#include"cocos2d.h"

USING_NS_CC;

class ClockHand :public::CCLayer
{
public:
	ClockHand();
	~ClockHand();
	virtual bool init();
	CREATE_FUNC(ClockHand);
	CCSprite* getSprite();
	void bindSprite(CCSprite* sprite);
private:
	CCSprite *mHand;
};
#endif
