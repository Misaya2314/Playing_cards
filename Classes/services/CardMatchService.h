#ifndef __CARD_MATCH_SERVICE_H__
#define __CARD_MATCH_SERVICE_H__

#include <cstdlib>
#include "models/CardTypes.h"

namespace playingcards
{
class CardMatchService
{
public:
    // 需求一里先只做最简单的差 1 规则。
    static bool canMatch(CardFaceType sourceFace, CardFaceType targetFace)
    {
        const int difference = static_cast<int>(sourceFace) - static_cast<int>(targetFace);
        return std::abs(difference) == 1;
    }
};
}

#endif // __CARD_MATCH_SERVICE_H__
