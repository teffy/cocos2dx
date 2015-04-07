#include "HelloWorldScene.h"
#include "sqlite3.h"

#define DBNAME "mysqlite3.db"

USING_NS_CC;

Scene* HelloWorld::createScene() {
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

std::string path;
bool initdb() {
	sqlite3* msqlite = NULL;
	path = FileUtils::getInstance()->fullPathForFilename(DBNAME);

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	path = FileUtils::getInstance()->getWritablePath();
	path += "/";
	path += DBNAME;
	FILE* dbfile = fopen(path.c_str(),"r");
	if (dbfile == nullptr) {
		ssize_t size;
		const char* data = (char*)FileUtils::getInstance()->getFileData(DBNAME, "rb", &size);
		dbfile = fopen(path.c_str(), "wb");
		fwrite(data, size, 1, dbfile);
		CC_SAFE_DELETE_ARRAY(data);
	}
	fclose(dbfile);
#endif

	log("dbpath->%s", path.c_str());

	int open = sqlite3_open(path.c_str(), &msqlite);
	if (open != SQLITE_OK) {
		const char* errmsg = sqlite3_errmsg(msqlite);
		log("errmsg:%s", errmsg);
		return false;
	}
	int result =
			sqlite3_exec(msqlite,
					"CREATE TABLE peoples (id integer primary key AUTOINCREMENT,name text,pwd text)",
					NULL, NULL, NULL);
	log("1result:%d", result);
	result = sqlite3_exec(msqlite,
			"insert into peoples values(NULL,'lam','123334')", NULL, NULL,
			NULL);
	result = sqlite3_exec(msqlite,
			"insert into peoples values(NULL,'wj','321')", NULL, NULL, NULL);
	log("2result:%d", result);
	sqlite3_close(msqlite);
	return true;
}

bool HelloWorld::init() {
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto closeItem = MenuItemImage::create("CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(
			Vec2(
					origin.x + visibleSize.width
							- closeItem->getContentSize().width / 2,
					origin.y + closeItem->getContentSize().height / 2));


	MenuItemFont* userDefault = MenuItemFont::create("UserDefault",
			CC_CALLBACK_1(HelloWorld::menuUserDefaultCallback, this));
	userDefault->setPosition(
			Vec2(visibleSize.width / 3,
					visibleSize.height * 2 / 3
							+ userDefault->getContentSize().height));

	MenuItemFont* plist = MenuItemFont::create("Plist",
			CC_CALLBACK_1(HelloWorld::menuPlistCallback, this));
	plist->setPosition(
			Vec2(visibleSize.width / 3,
					visibleSize.height * 2 / 3
							+ plist->getContentSize().height * 2));

	MenuItemFont* sqlite3 = MenuItemFont::create("Sqlite3",
			CC_CALLBACK_1(HelloWorld::menuSqlite3Callback, this));
	sqlite3->setPosition(
			Vec2(visibleSize.width / 3,
					visibleSize.height * 2 / 3
							+ sqlite3->getContentSize().height * 3));

	auto menu = Menu::create(closeItem, userDefault, plist, sqlite3,
			NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf",24);

	label->setPosition(
			Vec2(origin.x + visibleSize.width / 2,
					origin.y + visibleSize.height
							- label->getContentSize().height));

	this->addChild(label, 1);
	auto sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(
			Vec2(visibleSize.width / 2 + origin.x,
					visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	UserDefault::getInstance()->setIntegerForKey("key", 122);
	return initdb();
	//return true;
}

int sqlite3result(void* key, int c, char** value, char** cols) {
	log("c=%d", c);
	for (int i = 0; i < c; i++) {
		log("%s=%s", cols[i], value[i]);
	}
	return 0;
}

void HelloWorld::menuCloseCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}


void HelloWorld::menuPlistCallback(Ref* pSender) {
	Dictionary* dict = Dictionary::createWithContentsOfFile("res/aaa.plist");
	const __String* ss = dict->valueForKey("name");
	log("Plist name->%s", ss->getCString());

	Ref* family = dict->objectForKey("family");

	Dictionary* dictfamily = (Dictionary*) family;
	Dictionary* son = (Dictionary*) dictfamily->objectForKey("son");
	const __String* sonname = son->valueForKey("name");
	log("Plist sonname->%s", sonname->getCString());
}
void HelloWorld::menuUserDefaultCallback(Ref* pSender) {
	int intkey = UserDefault::getInstance()->getIntegerForKey("key");

	log("UserDefault intkey: %d", intkey);
}
void HelloWorld::menuSqlite3Callback(Ref* pSender) {
	sqlite3* msqlite;
	int open = sqlite3_open(path.c_str(), &msqlite);
	int result = sqlite3_exec(msqlite, "SELECT * FROM peoples", sqlite3result,
			NULL, NULL);
	log("Sqlite3 result:%d", result);
	sqlite3_close(msqlite);
}

