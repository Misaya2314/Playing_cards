#ifndef __CARD_RESOURCE_HELPER_H__
#define __CARD_RESOURCE_HELPER_H__

#include <string>
#include "models/CardTypes.h"

namespace playingcards
{
// 牌面资源路径都从这里统一取。
class CardResourceHelper
{
public:
    static std::string getCardBackgroundPath();
    static std::string getSuitPath(CardSuitType cardSuit);
    static std::string getSmallNumberPath(CardSuitType cardSuit, CardFaceType cardFace);
    static std::string getBigNumberPath(CardSuitType cardSuit, CardFaceType cardFace);

private:
    static std::string getColorToken(CardSuitType cardSuit);
    static std::string getFaceToken(CardFaceType cardFace);
};
}

#endif // __CARD_RESOURCE_HELPER_H__
