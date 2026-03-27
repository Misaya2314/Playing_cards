#ifndef __GAME_MODEL_FROM_LEVEL_GENERATOR_H__
#define __GAME_MODEL_FROM_LEVEL_GENERATOR_H__

#include "configs/models/LevelConfig.h"
#include "models/GameModel.h"

namespace playingcards
{
// 把关卡配置转成游戏运行时用的数据。
class GameModelFromLevelGenerator
{
public:
    GameModel generateGameModel(const LevelConfig& levelConfig) const;
};
}

#endif // __GAME_MODEL_FROM_LEVEL_GENERATOR_H__
