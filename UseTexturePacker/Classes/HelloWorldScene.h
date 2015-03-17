#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "AnimationCreator.h"


class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuPlayBgMusicCallback(cocos2d::Ref* pSender);
	void menuPlayEffectCallback(cocos2d::Ref* pSender);
	void menuResumeCallback(cocos2d::Ref* pSender);
	void menuPauseCallback(cocos2d::Ref* pSender);
	void menuStopCallback(cocos2d::Ref* pSender);
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
public:
	int dog_wangwang = -1;
};

#endif // __HELLOWORLD_SCENE_H__
