#ifndef __CARD_MODEL_H__
#define __CARD_MODEL_H__

#include "cocos2d.h"
#include "models/CardTypes.h"

namespace playingcards
{
// 单张牌的运行时数据。
class CardModel
{
public:
    CardModel();
    CardModel(int cardId,
              CardFaceType cardFace,
              CardSuitType cardSuit,
              const cocos2d::Vec2& boardPosition,
              CardZoneType cardZone);
    int getCardId() const;
    CardFaceType getCardFace() const;
    CardSuitType getCardSuit() const;
    const cocos2d::Vec2& getBoardPosition() const;
    CardZoneType getCardZone() const;
    void setCardZone(CardZoneType cardZone);

private:
    int _cardId;
    CardFaceType _cardFace;
    CardSuitType _cardSuit;
    cocos2d::Vec2 _boardPosition;
    CardZoneType _cardZone;
};
}

#endif // __CARD_MODEL_H__
