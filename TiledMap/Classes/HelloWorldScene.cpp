#include "HelloWorldScene.h"



Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    
	tiledMap = TMXTiledMap::create("res/test2.tmx");
	addChild(tiledMap);
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled,this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, tiledMap);
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event){
	Vec2 touchLoaction = touch->getLocation();
	Size tiledSize = tiledMap->getTileSize();
	Size mapSize = tiledMap->getMapSize();
	Vec2 touchLoaction1 = Vec2(touchLoaction.x, tiledSize.height* mapSize.height - touchLoaction.y);
	log("tiledSize:%d,%d", tiledSize.width, tiledSize.height);
	log("mapSize:%d,%d", mapSize.width, mapSize.height);
	int x = touchLoaction1.x / tiledSize.width;
	int y = touchLoaction1.y / tiledSize.height;
	log("x:%d,y:%d", x,y);

	TMXLayer* layer0 = tiledMap->layerNamed("Layer 0");
	layer0->setTileGID(0, Vec2(x, y));
	TMXLayer* layer1 = tiledMap->layerNamed("Layer 1");
	layer1->setTileGID(0, Vec2(x, y));
	TMXLayer* layer2 = tiledMap->layerNamed("Layer 2");
	layer2->setTileGID(8, Vec2(x, y));

	Sprite * sprite = layer2->tileAt(Vec2(x, y));
	sprite->runAction(JumpBy::create(1.5f, Vec2(0,0), 40, 4));
	return true;
}
void HelloWorld::onTouchCancelled(Touch* touch, Event* event){

}
void HelloWorld::onTouchMoved(Touch* touch, Event* event){

}
void HelloWorld::onTouchEnded(Touch* touch, Event* event){
	TMXObjectGroup* objGroup = tiledMap->getObjectGroup("Obj1");
	ValueVector vv = objGroup->getObjects();
	auto o1 = objGroup->getObject("o1");
	int xxx = o1.at("x").asInt();
	int aa = o1.at("aa").asInt();
	log("xxxx->%d,aa->%d", xxx,aa);
}
