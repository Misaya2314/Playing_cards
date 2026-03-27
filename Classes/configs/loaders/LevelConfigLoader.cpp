#include "configs/loaders/LevelConfigLoader.h"
#include "cocos2d.h"
#include "json/document.h"

namespace playingcards
{
namespace
{
bool parseCardArray(const rapidjson::Value& arrayValue, std::vector<LevelCardConfig>& outCards)
{
    if (!arrayValue.IsArray())
    {
        return false;
    }

    outCards.clear();
    outCards.reserve(arrayValue.Size());
    for (rapidjson::SizeType index = 0; index < arrayValue.Size(); ++index)
    {
        const rapidjson::Value& cardValue = arrayValue[index];
        if (!cardValue.IsObject() || !cardValue.HasMember("Position"))
        {
            return false;
        }

        const rapidjson::Value& positionValue = cardValue["Position"];
        if (!positionValue.IsObject() || !positionValue.HasMember("x") || !positionValue.HasMember("y"))
        {
            return false;
        }

        LevelCardConfig cardConfig;
        cardConfig.cardFace = static_cast<CardFaceType>(cardValue["CardFace"].GetInt());
        cardConfig.cardSuit = static_cast<CardSuitType>(cardValue["CardSuit"].GetInt());
        cardConfig.position = cocos2d::Vec2(positionValue["x"].GetFloat(), positionValue["y"].GetFloat());
        outCards.push_back(cardConfig);
    }

    return true;
}
}

bool LevelConfigLoader::loadLevelConfig(int levelId, LevelConfig& outLevelConfig) const
{
    const std::string fileContent = cocos2d::FileUtils::getInstance()->getStringFromFile(getLevelPath(levelId));
    if (fileContent.empty())
    {
        return false;
    }

    rapidjson::Document document;
    document.Parse(fileContent.c_str());
    if (document.HasParseError() || !document.IsObject())
    {
        return false;
    }

    if (!document.HasMember("Playfield") || !document.HasMember("Stack"))
    {
        return false;
    }

    return parseCardArray(document["Playfield"], outLevelConfig.playfieldCards)
        && parseCardArray(document["Stack"], outLevelConfig.stackCards);
}

std::string LevelConfigLoader::getLevelPath(int levelId) const
{
    return cocos2d::StringUtils::format("levels/level_%d.json", levelId);
}
}
