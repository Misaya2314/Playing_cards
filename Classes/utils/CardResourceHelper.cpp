#include "utils/CardResourceHelper.h"
#include "cocos2d.h"

namespace playingcards
{
namespace
{
bool isRedSuit(CardSuitType cardSuit)
{
    return cardSuit == CST_DIAMONDS || cardSuit == CST_HEARTS;
}
}

std::string CardResourceHelper::getCardBackgroundPath()
{
    return "res/card_general.png";
}

std::string CardResourceHelper::getSuitPath(CardSuitType cardSuit)
{
    // 花色图标与数字资源拆分管理，便于后续替换牌面风格。
    switch (cardSuit)
    {
    case CST_CLUBS:
        return "res/suits/club.png";
    case CST_DIAMONDS:
        return "res/suits/diamond.png";
    case CST_HEARTS:
        return "res/suits/heart.png";
    case CST_SPADES:
        return "res/suits/spade.png";
    default:
        return "res/suits/club.png";
    }
}

std::string CardResourceHelper::getSmallNumberPath(CardSuitType cardSuit, CardFaceType cardFace)
{
    return cocos2d::StringUtils::format("res/number/small_%s_%s.png",
                                        getColorToken(cardSuit).c_str(),
                                        getFaceToken(cardFace).c_str());
}

std::string CardResourceHelper::getBigNumberPath(CardSuitType cardSuit, CardFaceType cardFace)
{
    return cocos2d::StringUtils::format("res/number/big_%s_%s.png",
                                        getColorToken(cardSuit).c_str(),
                                        getFaceToken(cardFace).c_str());
}

std::string CardResourceHelper::getColorToken(CardSuitType cardSuit)
{
    return isRedSuit(cardSuit) ? "red" : "black";
}

std::string CardResourceHelper::getFaceToken(CardFaceType cardFace)
{
    switch (cardFace)
    {
    case CFT_ACE:
        return "A";
    case CFT_TWO:
        return "2";
    case CFT_THREE:
        return "3";
    case CFT_FOUR:
        return "4";
    case CFT_FIVE:
        return "5";
    case CFT_SIX:
        return "6";
    case CFT_SEVEN:
        return "7";
    case CFT_EIGHT:
        return "8";
    case CFT_NINE:
        return "9";
    case CFT_TEN:
        return "10";
    case CFT_JACK:
        return "J";
    case CFT_QUEEN:
        return "Q";
    case CFT_KING:
        return "K";
    default:
        return "A";
    }
}
}
