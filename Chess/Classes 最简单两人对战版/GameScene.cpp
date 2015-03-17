#include "GameScene.h"

USING_NS_CC;

void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

GameScene::GameScene(){
}
GameScene::~GameScene(){
	if (steps != NULL)
		steps->release();
}

static std::string getStringByKey(const char* key){
	Dictionary *strings = Dictionary::createWithContentsOfFile("fonts/strings.xml");
	return ((String*)strings->objectForKey(key))->getCString();
}

Scene* GameScene::createScene(bool _clickRed)
{
	auto scene = Scene::create();
	auto layer = GameScene::create(_clickRed);
	scene->addChild(layer);
	return scene;
}
GameScene* GameScene::create(bool _clickRed){
	GameScene* game = new GameScene();
	if (game && game->init(_clickRed))
	{
		game->autorelease();
		return game;
	}
	else
	{
		delete game;
		game = NULL;
		return NULL;
	}
}
bool GameScene::init(bool _clickRed)
{
	if (!Layer::init())
	{
		return false;
	}

	clickRed = _clickRed;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameScene::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	MenuItemImage* backMenu = MenuItemImage::create("res/regret.png", "res/regret_selected.png", CC_CALLBACK_1(GameScene::backQIMenuCallback, this));
	backMenu->setPosition(Vec2(visibleSize.width - 200, visibleSize.height / 2 - 100));

	MenuItemImage* newGameMenu = MenuItemImage::create("res/new.png", "res/new_selected.png", CC_CALLBACK_1(GameScene::newGameMenuCallback, this));
	newGameMenu->setPosition(Vec2(visibleSize.width - 200, visibleSize.height / 2));

	auto menu = Menu::create(closeItem, backMenu, newGameMenu, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	/*
	auto label = Label::createWithTTF(getStringByKey("GuideStart"), "fonts/fangzheng.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
	origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);
	*/

	Vec2 offset = Vec2(20.0, 10.0);
	auto floor = Sprite::create("res/floor.png");
	floor->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	floor->setScaleX(visibleSize.width / floor->getContentSize().width);
	floor->setScaleY(visibleSize.height / floor->getContentSize().height);
	this->addChild(floor);

	Sprite* qipan = Sprite::create("res/background.png");
	qipan->setAnchorPoint(Vec2::ZERO);
	qipan->setPosition(offset);
	qipan->setScale((visibleSize.height - offset.y * 2) / qipan->getContentSize().height);
	this->addChild(qipan);
	// 给棋盘添加touch监听
	EventListenerTouchOneByOne *touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), qipan);

	for (int i = 0; i < 32; i++){
		sts[i] = Stone::create(i, clickRed);
		sts[i]->setPosition(Vec2(rand_0_1()*visibleSize.width, rand_0_1()*visibleSize.height));
		MoveTo* moveTo = MoveTo::create(0.6f, Vec2(sts[i]->getRealX(), sts[i]->getRealY()));
		//MoveTo* moveTo = MoveTo::create(0.6f, Vec2(stone_x + sts[i]->getX()*def, stone_y + sts[i]->getY()*def));
		//sts[i]->setPosition(Vec2(stone_x + sts[i]->getX()*def, stone_y + sts[i]->getY()*def));
		sts[i]->runAction(moveTo);
		this->addChild(sts[i]);
	}

	spriteSelected = Sprite::create("res/selected.png");
	spriteSelected->setVisible(false);
	addChild(spriteSelected, 10);
	select_id = -1;
	isRedTurn = true;
	steps = Array::create();
	steps->retain();

	return true;
}

bool GameScene::onTouchesBegan(Touch *mTouch, Event *mEvent){
	Vec2 touchPosition = mTouch->getLocation();
	int tox = 0, toy = 0;
	// 判断点击的是不是棋盘内，并把点击的坐标的x,y确定下来
	if (!checkTouchPositionStone(touchPosition, tox, toy)){
		return false;
	}
	int clickStoneID = getStoneIDByXY(tox, toy);
	if (select_id == -1){
		setSelectedID(clickStoneID);
	}
	else{
		moveToXY(select_id, clickStoneID, tox, toy);
	}
	return true;
}
void GameScene::onTouchesMoved(Touch *mTouch, Event *mEvent){
}
void GameScene::onTouchesEnded(Touch *mTouch, Event *mEvent){
}
void GameScene::onTouchesCancelled(Touch *mTouch, Event *mEvent){
}

bool GameScene::checkTouchPositionStone(Vec2 touchPosition, int &x, int &y){
	for (x = 0; x < 9; x++){
		for (y = 0; y < 10; y++){
			Vec2 theXYPostion = Vec2(stone_def_x + x*stone_def, stone_def_y + y*stone_def);
			float distance = touchPosition.getDistance(theXYPostion);
			if (distance < stone_def / 2){
				return true;
			}
		}
	}
	return false;
}

int GameScene::getStoneIDByXY(int x, int y){
	for (int i = 0; i < 32; i++){
		if (sts[i]->getX() == x && sts[i]->getY() == y && !sts[i]->getisDead()){
			return sts[i]->getID();
		}
	}
	return -1;
}

void GameScene::moveToXY(int moveID, int killID, int tox, int toy){
	// 判断是否可以移动到xy位置，如果是并移动到xy的位置，并将select_id 置为-1
	if (killID != -1 && sts[moveID]->getisRed() == sts[killID]->getisRed()){
		setSelectedID(killID);
		return;
	}
	// 判断是否可以移动棋子
	bool canMove = isCanMove(moveID, killID, tox, toy);
	if (!canMove){
		return;
	}
	// 记录走的每一步
	Step* itemsStep = Step::create(moveID, killID, sts[moveID]->getX(), sts[moveID]->getY());
	steps->addObject(itemsStep);

	sts[moveID]->setX(tox);
	sts[moveID]->setY(toy);
	sts[moveID]->setZOrder(sts[moveID]->getZOrder() + 1);
	MoveTo* moveTo = MoveTo::create(0.5f, Vec2(sts[moveID]->getRealX(), sts[moveID]->getRealY()));
	CallFuncN* actionCallback = CallFuncN::create(CC_CALLBACK_1(GameScene::onActionComplete, this, moveID, killID));
	Sequence* seq = Sequence::create(moveTo, actionCallback, NULL);
	sts[moveID]->runAction(seq);

	spriteSelected->setVisible(false);
	select_id = -1;
	isRedTurn = !isRedTurn;
}

void GameScene::setSelectedID(int clickID){
	if (clickID == -1){
		return;
	}
	if (isRedTurn != sts[clickID]->getisRed()){
		return;
	}

	select_id = clickID;
	spriteSelected->setVisible(true);
	spriteSelected->setPosition(sts[select_id]->getPosition());
}

void GameScene::backQIMenuCallback(cocos2d::Ref* pSender){
	if (steps->count() == 0){
		return;
	}
	Step* lastStep = (Step*)steps->getLastObject();
	sts[lastStep->moveID]->setX(lastStep->moveX);
	sts[lastStep->moveID]->setY(lastStep->moveY);
	sts[lastStep->moveID]->setPosition(Vec2(sts[lastStep->moveID]->getRealX(), sts[lastStep->moveID]->getRealY()));
	if (lastStep->killID != -1){
		sts[lastStep->killID]->setVisible(true);
		sts[lastStep->killID]->setisDead(false);
	}
	spriteSelected->setVisible(false);
	isRedTurn = !isRedTurn;
	steps->removeLastObject();
}

void GameScene::newGameMenuCallback(cocos2d::Ref* pSender){
	reStartGame();
}

void GameScene::reStartGame(){
	Director::getInstance()->replaceScene(GameScene::createScene(clickRed));
}

void GameScene::onActionComplete(Node* node, int moveID, int killID){
	/*当MoveAction执行完成*/
	sts[moveID]->setZOrder(sts[moveID]->getZOrder() - 1);
	if (killID != -1){
		sts[killID]->setisDead(true);
		sts[killID]->setVisible(false);
		if (sts[killID]->getType() == Stone::JIANG){
			reStartGame();
		}
	}
}

bool GameScene::isCanMove(int moveID, int killID, int tox, int toy){
	/*根据要移动的棋子的类型来分别判断*/
	Stone* moveStone = sts[moveID];
	switch (moveStone->getType()){
	case Stone::JIANG:
		return canMoveJIANG(moveID, killID, tox, toy);
	case Stone::SHI:
		return canMoveSHI(moveID, tox, toy);
	case Stone::XIANG:
		return canMoveXIANG(moveID, killID, tox, toy);
	case Stone::JU:
		return canMoveJU(moveID, killID, tox, toy);
	case Stone::MA:
		return canMoveMA(moveID, killID, tox, toy);
	case Stone::PAO:
		return canMovePAO(moveID, killID, tox, toy);
	case Stone::BING:
		return canMoveBING(moveID, killID, tox, toy);
	default:return false;
	}
}
bool GameScene::canMoveJIANG(int moveID, int killID, int tox, int toy){
	/*如果要杀的对面的将或帅，则直接按车的走法*/
	if (killID != -1 && sts[killID]->getType() == Stone::JIANG){
		return canMoveJU(moveID, killID, tox, toy);
	}
	/*判断是否走的一格*/
	Stone* moveStone = sts[moveID];
	int m_x = moveStone->getX();
	int m_y = moveStone->getY();
	int xoff = abs(m_x - tox);
	int yoff = abs(m_y - toy);
	int checkXY = xoff * 10 + yoff;
	if (checkXY != 1 && checkXY != 10){
		return false;
	}

	/*判断将或帅是否走出9宫格*/
	if (tox > 5 || tox < 3){
		return false;
	}
	if (clickRed == sts[moveID]->getisRed()){
		if (toy > 2 || toy < 0){
			return false;
		}
	}
	else{
		if (toy > 9 || toy < 7){
			return false;
		}
	}
	return true;
}
bool GameScene::canMoveSHI(int moveID, int tox, int toy){
	Stone* moveStone = sts[moveID];
	int m_x = moveStone->getX();
	int m_y = moveStone->getY();
	int xoff = abs(m_x - tox);
	int yoff = abs(m_y - toy);
	if (xoff != 1 || yoff != 1 ){
		return false;
	}

	/*判断将或帅是否走出9宫格*/
	if (tox > 5 || tox < 3){
		return false;
	}
	if (clickRed == sts[moveID]->getisRed()){
		if (toy > 2 || toy < 0){
			return false;
		}
	}
	else{
		if (toy > 9 || toy < 7){
			return false;
		}
	}
	return true;
}
bool GameScene::canMoveXIANG(int moveID, int killID, int tox, int toy){
	Stone* moveStone = sts[moveID];
	int m_x = moveStone->getX();
	int m_y = moveStone->getY();
	int xoff = abs(m_x - tox);
	int yoff = abs(m_y - toy);
	if (xoff != 2|| yoff != 2){
		return false;
	}
	/*判断象眼位置*/
	int mid_x = (m_x + tox) / 2;
	int mid_y = (m_y + toy) / 2;
	int mid_stone = getStoneIDByXY(mid_x, mid_y);
	if (mid_stone != -1){
		return false;
	}
	//如果是在棋盘下面，y如果超过4，就越过楚河汉界了
	if (clickRed == sts[moveID]->getisRed()){
		if (toy > 4){
			return false;
		}
	}
	else{
		//如果是在棋盘上面，y如果小于5，就越过楚河汉界了
		if (toy < 5){
			return false;
		}
	}
	return true;
}
bool GameScene::canMoveJU(int moveID, int killID, int tox, int toy){
	int count = getStoneCountInSingleXY(moveID, killID, tox, toy);
	if (count != 0){
		return false;
	}
	return true;
}
bool GameScene::canMoveMA(int moveID, int killID, int tox, int toy){
	Stone* moveStone = sts[moveID];
	int m_x = moveStone->getX();
	int m_y = moveStone->getY();
	int xoff = abs(m_x - tox);
	int yoff = abs(m_y - toy);
	int checkXY = xoff * 10 + yoff;
	if (checkXY != 12 && checkXY != 21){
		return false;
	}
	if (xoff == 2 && (getStoneIDByXY((m_x + tox) / 2, m_y) != -1)){
		return false;
	}
	else if (yoff == 2 && (getStoneIDByXY(m_x, (m_y + toy) / 2) != -1)){
		return false;
	}else{ }
	return true;
}
bool GameScene::canMovePAO(int moveID, int killID, int tox, int toy){
	int count = getStoneCountInSingleXY(moveID, killID, tox, toy);

	if (killID != -1 && count == 1){
		return true;
	}
	return canMoveJU(moveID, killID, tox, toy);
}
bool GameScene::canMoveBING(int moveID, int killID, int tox, int toy){
	Stone* moveStone = sts[moveID];
	int m_x = moveStone->getX();
	int m_y = moveStone->getY();
	int xoff = abs(m_x - tox);
	int yoff = abs(m_y - toy);
	int checkXY = xoff * 10 + yoff;
	if (checkXY != 1 && checkXY != 10){
		return false;
	}
	if (clickRed == moveStone->getisRed()){//棋盘的下半部分
		if (toy < m_y){
			return false;
		}
		if (m_y <= 4 && m_x != tox){//过河了
			return false;
		}
	}
	else{//棋盘的上半部分
		if (toy > m_y){
			return false;
		}
		if (m_y >= 5 && m_x != tox){//过河了
			return false;
		}
	}
	return true;
}
//判断在走的X,Y轴上，moveID和killID之间有多少个棋子
int GameScene::getStoneCountInSingleXY(int moveID, int killID, int tox, int toy){
	int count = 0;
	Stone* moveStone = sts[moveID];
	if (moveStone->getX() != tox && moveStone->getY() != toy){
		return -1;
	}
	int m_x = moveStone->getX();
	int m_y = moveStone->getY();
	if (m_x == tox){
		int y_min = m_y < toy ? m_y : toy;
		int y_max = m_y > toy ? m_y : toy;
		for (int i = y_min+1; i < y_max; i++){
			if (getStoneIDByXY(m_x, i) != -1){
				count++;
			}
		}
	}
	else if (m_y == toy){
		int x_min = m_x < tox ? m_x : tox;
		int x_max = m_x > tox ? m_x : tox;
		for (int i = x_min+1; i < x_max; i++){
			if (getStoneIDByXY(i, m_y) != -1){
				count++;
			}
		}
	}
	else{
		return -1;
	}
	return count;
}