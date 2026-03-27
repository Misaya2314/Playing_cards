#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <memory>
#include "cocos2d.h"

namespace playingcards
{
class GameController;

// 场景入口本身比较轻，主要就是拉起 GameController。
class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    GameScene();
    virtual ~GameScene();
    virtual bool init() override;

    CREATE_FUNC(GameScene);

private:
    std::unique_ptr<GameController> _gameController;
};
}

#endif // __GAME_SCENE_H__
