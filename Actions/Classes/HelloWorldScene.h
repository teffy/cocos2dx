#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuNextCallback(cocos2d::Ref* pSender);
	void menuLastCallback(cocos2d::Ref* pSender);
	void menuRestartCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
protected:
	cocos2d::Sprite*  androidapple;
	cocos2d::Label*   label;
	Size visibleSize;
	int index;
	FiniteTimeAction* currentAction;
	Vector<FiniteTimeAction*> actions;
	std::list<std::string> *actionDescriptions;
};

#endif // __HELLOWORLD_SCENE_H__
