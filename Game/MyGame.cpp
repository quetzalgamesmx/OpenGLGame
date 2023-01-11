#include "MyGame.h"

MyGame::MyGame()
{
}

MyGame::~MyGame()
{
}

void MyGame::onCreate()
{
	OGame::onCreate();
	auto e = getEntitySystem()->createEntity<OEntity>();
}
