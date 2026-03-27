#ifndef __LEVEL_CONFIG_LOADER_H__
#define __LEVEL_CONFIG_LOADER_H__

#include <string>
#include "configs/models/LevelConfig.h"

namespace playingcards
{
// 负责把关卡 json 读成代码里的配置结构。
class LevelConfigLoader
{
public:
    bool loadLevelConfig(int levelId, LevelConfig& outLevelConfig) const;

private:
    std::string getLevelPath(int levelId) const;
};
}

#endif // __LEVEL_CONFIG_LOADER_H__
