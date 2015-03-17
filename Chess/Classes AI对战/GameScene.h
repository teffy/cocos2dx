#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"
#include "Stone.h"
#include "AIPlayer.h"

#define stone_def_x 72
#define stone_def_y 35
#define stone_def   64

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
	void fakeMove(Step* step);
	void unfakeMove(Step* step);
	void updateAutoGo(float delay);
	void aiGostep();
public:
	Stone* sts[32];
	bool clickRed;
	int select_id;
	Sprite* spriteSelected;
	bool isRedTurn;
	Array* steps;
	AIPlayer* aiPlayer;
	int level = 3;
};

#endif
