#ifndef __CARD_VIEW_H__
#define __CARD_VIEW_H__

#include <functional>
#include "cocos2d.h"
#include "models/CardTypes.h"

namespace playingcards
{
// 单张牌的显示和点击都放在这里。
class CardView : public cocos2d::Node
{
public:
    CREATE_FUNC(CardView);
    virtual bool init() override;
    void setCardData(int cardId, CardFaceType cardFace, CardSuitType cardSuit);
    void setInputEnabled(bool inputEnabled);
    void setTapCallback(const std::function<void(int)>& onTapCallback);

private:
    // 用节点自己的矩形范围做命中测试。
    bool containsTouch(cocos2d::Touch* touch) const;

    cocos2d::Sprite* _backgroundSprite = nullptr;
    cocos2d::Sprite* _smallNumberSprite = nullptr;
    cocos2d::Sprite* _smallSuitSprite = nullptr;
    cocos2d::Sprite* _bigNumberSprite = nullptr;
    cocos2d::Sprite* _bigSuitSprite = nullptr;
    std::function<void(int)> _onTapCallback;
    bool _isInputEnabled = false;
    int _cardId = -1;
};
}

#endif // __CARD_VIEW_H__
