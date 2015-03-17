#ifndef _AIPlayer_H_
#define _AIPlayer_H_

#include "cocos2d.h"

USING_NS_CC;

class GameScene;

class Step : public cocos2d::Object{
public:
	int moveID;
	int killID;
	int moveFromX;
	int moveFromY;
	int moveToX;
	int moveToY;
	static Step* create(
		int _moveID,
		int _killID,
		int _moveFromX,
		int _moveFromY,
		int _moveToX,
		int _moveToY)
	{
		Step* step = new Step();
		step->moveID = _moveID;
		step->killID = _killID;
		step->moveFromX = _moveFromX;
		step->moveFromY = _moveFromY;
		step->moveToX = _moveToX;
		step->moveToY = _moveToY;
		step->autorelease();
		return step;
	}
};

class AIPlayer
{
public:
	AIPlayer(GameScene* _gameScene);
	~AIPlayer();
	Step* getOneMoveAction(int level);
	int getScores();
	Array* getAllPosibleStep();
	void getAllPosibleStep(int i, Array* stepArray);
	int getMinScore(int level, int max);
	int getMaxScore(int level, int min);
public:
	GameScene* gameScene;
	static int stone_scores[7];
};
#endif
