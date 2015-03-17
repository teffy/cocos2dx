#include "AnimationCreator.h"


AnimationCreator::AnimationCreator()
{
}


AnimationCreator::~AnimationCreator()
{
}

Animation* AnimationCreator::createAnimWithFrameNameAndNum(const char* name, int num, float delay, unsigned int loops){
	SpriteFrameCache* cache = SpriteFrameCache::sharedSpriteFrameCache();
	Vector<SpriteFrame*> framesVector(num);
	SpriteFrame* spriteFrame = NULL;
	for (int i = 1; i < num; i++){
		spriteFrame = cache->spriteFrameByName(String::createWithFormat("%s%d.png",name,i)->getCString());
		if (spriteFrame == NULL){
			break;
		}
		framesVector.pushBack(spriteFrame);
	}
	Animation* animation = Animation::createWithSpriteFrames(framesVector, delay, loops);
	animation->setRestoreOriginalFrame(true);
	return animation;
}