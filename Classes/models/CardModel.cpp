#include "models/CardModel.h"

namespace playingcards
{
CardModel::CardModel()
    : _cardId(-1)
    , _cardFace(CFT_NONE)
    , _cardSuit(CST_NONE)
    , _boardPosition(cocos2d::Vec2::ZERO)
    , _cardZone(CardZoneType::Discard)
{
}

CardModel::CardModel(int cardId,
                     CardFaceType cardFace,
                     CardSuitType cardSuit,
                     const cocos2d::Vec2& boardPosition,
                     CardZoneType cardZone)
    : _cardId(cardId)
    , _cardFace(cardFace)
    , _cardSuit(cardSuit)
    , _boardPosition(boardPosition)
    , _cardZone(cardZone)
{
}

int CardModel::getCardId() const
{
    return _cardId;
}

CardFaceType CardModel::getCardFace() const
{
    return _cardFace;
}

CardSuitType CardModel::getCardSuit() const
{
    return _cardSuit;
}

const cocos2d::Vec2& CardModel::getBoardPosition() const
{
    return _boardPosition;
}

CardZoneType CardModel::getCardZone() const
{
    return _cardZone;
}

void CardModel::setCardZone(CardZoneType cardZone)
{
    _cardZone = cardZone;
}
}
