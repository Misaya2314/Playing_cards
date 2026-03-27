#ifndef __CARD_TYPES_H__
#define __CARD_TYPES_H__

namespace playingcards
{
// 关卡里用到的花色和点数定义。
enum CardSuitType
{
    CST_NONE = -1,
    CST_CLUBS = 0,
    CST_DIAMONDS = 1,
    CST_HEARTS = 2,
    CST_SPADES = 3,
    CST_NUM_CARD_SUIT_TYPES
};

enum CardFaceType
{
    CFT_NONE = -1,
    CFT_ACE = 0,
    CFT_TWO = 1,
    CFT_THREE = 2,
    CFT_FOUR = 3,
    CFT_FIVE = 4,
    CFT_SIX = 5,
    CFT_SEVEN = 6,
    CFT_EIGHT = 7,
    CFT_NINE = 8,
    CFT_TEN = 9,
    CFT_JACK = 10,
    CFT_QUEEN = 11,
    CFT_KING = 12,
    CFT_NUM_CARD_FACE_TYPES
};

enum class CardZoneType
{
    Playfield,
    Stack,
    Tray,
    Discard
};
}

#endif // __CARD_TYPES_H__
