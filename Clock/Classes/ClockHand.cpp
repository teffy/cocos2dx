#include "ClockHand.h"


ClockHand::ClockHand()
{
}

ClockHand::~ClockHand()
{
}

bool ClockHand::init(){
	return true;
}

CCSprite* ClockHand::getSprite(){
	return this->mHand;
}

void ClockHand::bindSprite(CCSprite* sprite){
	mHand = sprite;
	mHand->setAnchorPoint(ccp(0, 0.5));
	mHand->setScale(0.2f);
	mHand->setRotation(-90);
	this->addChild(mHand);
}