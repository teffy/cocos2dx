#pragma once

#include<iostream>
#include<cocos2d.h>
USING_NS_CC;
class AnimationCreator
{
public:
	AnimationCreator();
	~AnimationCreator();
	// 参数为：文件名，图片数量，每一帧播放间隔时间，播放次数
	static Animation* createAnimWithFrameNameAndNum(const char* name,int num,float delay,unsigned int loops);
};

