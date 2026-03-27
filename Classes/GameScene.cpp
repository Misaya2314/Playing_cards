#include "GameScene.h"
#include "controllers/GameController.h"

namespace playingcards
{
cocos2d::Scene* GameScene::createScene()
{
    return GameScene::create();
}

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    _gameController.reset(new GameController(this));
    _gameController->startGame(1);
    return true;
}
}
