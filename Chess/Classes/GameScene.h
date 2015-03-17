#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"
#include "Stone.h"

#define stone_def_x 70
#define stone_def_y 35
#define stone_def   64

class Step : public cocos2d::Object{
public:
	int moveID;
	int killID;
	int moveFromX;
	int moveFromY;
	int moveToX;
	int moveToY;
	int moveX;
	int moveY;
	int killX;
	int killY;
	static Step* create(
		int _moveID,
		int _killID,
		int _moveX,
		int _moveY)
	{
		Step* step = new Step();
		step->moveID = _moveID;
		step->killID = _killID;
		step->moveX = _moveX;
		step->moveY = _moveY;
		step->autorelease();
		return step;
	}
};

class GameScene : public cocos2d::Layer
{
public:
	GameScene();
	virtual ~GameScene();

	static cocos2d::Scene* createScene(bool _clickRed);
	virtual bool init(bool _clickRed);
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	//CREATE_FUNC(HelloWorld);
	static GameScene* create(bool _clickRed);

	bool onTouchesBegan(Touch *mTouch, Event *mEvent);
	void onTouchesMoved(Touch *mTouch, Event *mEvent);
	void onTouchesEnded(Touch *mTouch, Event *mEvent);
	void onTouchesCancelled(Touch *mTouch, Event *mEvent);
	bool checkTouchPositionStone(Vec2 touchPosition, int &x, int &y);
	int getStoneIDByXY(int x, int y);
	void moveToXY(int moveID, int killID, int tox, int toy);
	void setSelectedID(int clickID);
	void backQIMenuCallback(cocos2d::Ref* pSender);
	void newGameMenuCallback(cocos2d::Ref* pSender);
	void reStartGame();
	void onActionComplete(Node* node, int moveID, int killID);
	bool isCanMove(int moveID, int killID, int tox, int toy);
	bool canMoveJIANG(int moveID, int killID, int tox, int toy);
	bool canMoveSHI(int moveID, int tox, int toy);
	bool canMoveXIANG(int moveID, int killID, int tox, int toy);
	bool canMoveJU(int moveID, int killID, int tox, int toy);
	bool canMoveMA(int moveID, int killID, int tox, int toy);
	bool canMovePAO(int moveID, int killID, int tox, int toy);
	bool canMoveBING(int moveID, int killID, int tox, int toy);
	int getStoneCountInSingleXY(int moveID, int killID, int tox, int toy);
public:
	Stone* sts[32];
	bool clickRed;
	int select_id;
	Sprite* spriteSelected;
	bool isRedTurn;
	Array* steps;
};

#endif // __HELLOWORLD_SCENE_H__
