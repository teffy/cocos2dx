#include "Stone.h"

Stone::StoneInitPoint Stone::stonePoints[32] =
{
	{ 0, 0, Stone::JU },
	{ 1, 0, Stone::MA },
	{ 2, 0, Stone::XIANG },
	{ 3, 0, Stone::SHI },
	{ 4, 0, Stone::JIANG },
	{ 5, 0, Stone::SHI },
	{ 6, 0, Stone::XIANG },
	{ 7, 0, Stone::MA },
	{ 8, 0, Stone::JU },

	{ 1, 2, Stone::PAO },
	{ 7, 2, Stone::PAO },

	{ 0, 3, Stone::BING },
	{ 2, 3, Stone::BING },
	{ 4, 3, Stone::BING },
	{ 6, 3, Stone::BING },
	{ 8, 3, Stone::BING },
};

void Stone::reset(bool _clickRed){
	this->setisDead(false);
	if (id < 16){
		this->setX(stonePoints[id].x);
		this->setY(stonePoints[id].y);
	}
	else{
		this->setX(8 - stonePoints[id - 16].x);
		this->setY(9 - stonePoints[id - 16].y);
	}
}

int Stone::getRealX(){
	return stone_def_x + getX()*stone_def;
}
int Stone::getRealY(){
	return stone_def_y + getY()*stone_def;
}