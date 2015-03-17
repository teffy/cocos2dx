#ifndef Stone_H
#define Stone_H

#include "cocos2d.h"

USING_NS_CC;

#define stone_def_x 70
#define stone_def_y 35
#define stone_def   64

class Stone : public Sprite
{
public:
	enum TYPE { JIANG, SHI, XIANG, JU, MA, PAO, BING };
	CC_SYNTHESIZE(TYPE, type, Type);
	CC_SYNTHESIZE(int, x, X);
	CC_SYNTHESIZE(int, y, Y);
	CC_SYNTHESIZE(int, id, ID);
	CC_SYNTHESIZE(bool, isDead, isDead);
	CC_SYNTHESIZE(bool, isRed, isRed);

	static Stone* create(int _id, bool _clickRed){
		Stone* stone = new Stone();
		stone->init(_id, _clickRed);
		stone->autorelease();
		return stone;
	}
	void reset(bool _clickRed);
	bool init(int _id, bool _clickRed){
		const char* stonePic[14] = {
			"res/rshuai.png",
			"res/rshi.png",
			"res/rxiang.png",
			"res/rche.png",
			"res/rma.png",
			"res/rpao.png",
			"res/rbing.png",

			"res/bjiang.png",
			"res/bshi.png",
			"res/bxiang.png",
			"res/bche.png",
			"res/bma.png",
			"res/bpao.png",
			"res/bzu.png"
		};
		id = _id;

		// 是否点击的是黑棋，和根据id的位置无关，id<16的就是在下半部分
		if (id < 16){
			type = stonePoints[id].type;
		}
		else{
			type = stonePoints[id - 16].type;
		}
		int iconIndex = -1;

		if (_clickRed){
			// 如果点击的是红棋,id<16的都是需要红棋资源
			iconIndex = (id < 16 ? 0 : 1) * 7 + type;
			isRed = id < 16;
		}
		else{
			// 如果点击的是黑棋,id<16的都是需要黑棋资源
			iconIndex = (id < 16 ? 1 : 0) * 7 + type;
			isRed = id >= 16;
		}
		Sprite::initWithFile(stonePic[iconIndex]);
		//setScale(0.6f);
		reset(_clickRed);
		return true;
	}
	static struct StoneInitPoint{
		int x;
		int y;
		Stone::TYPE type;
	}
	stonePoints[32];
	int getRealX();
	int getRealY();
};


#endif
