#ifndef __LEVEL_CONFIG_H__
#define __LEVEL_CONFIG_H__

#include <vector>
#include "cocos2d.h"
#include "models/CardTypes.h"

namespace playingcards
{
// 关卡文件里单张牌的配置。
struct LevelCardConfig
{
    CardFaceType cardFace = CFT_NONE;
    CardSuitType cardSuit = CST_NONE;
    cocos2d::Vec2 position = cocos2d::Vec2::ZERO;
};

// 当前关卡只用到桌面区和牌堆两组数据。
struct LevelConfig
{
    std::vector<LevelCardConfig> playfieldCards;
    std::vector<LevelCardConfig> stackCards;
};
}

#endif // __LEVEL_CONFIG_H__
