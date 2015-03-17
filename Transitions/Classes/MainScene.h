#ifndef __MainScene_SCENE_H__
#define __MainScene_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuRestartCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(MainScene);
};

class LayerOne : public cocos2d::Layer
{
public:
	LayerOne();
	~LayerOne();
	virtual bool init();
	void menuRestartCallback(cocos2d::Ref* pSender);
	void menuBackCallback(cocos2d::Ref* pSender);
	void menuForwardCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(LayerOne);
};
class LayerTwo : public cocos2d::Layer
{
public:
	LayerTwo();
	~LayerTwo();
	virtual bool init();
	void menuRestartCallback(cocos2d::Ref* pSender);
	void menuBackCallback(cocos2d::Ref* pSender);
	void menuForwardCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(LayerTwo);
};
#endif // __MainScene_SCENE_H__
