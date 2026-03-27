#include "views/CardView.h"
#include "utils/CardResourceHelper.h"

namespace playingcards
{
namespace
{
const cocos2d::Size kCardSize(182.0f, 282.0f);
}

bool CardView::init()
{
    if (!Node::init())
    {
        return false;
    }

    setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
    setContentSize(kCardSize);

    _backgroundSprite = cocos2d::Sprite::create(CardResourceHelper::getCardBackgroundPath());
    _smallNumberSprite = cocos2d::Sprite::create(CardResourceHelper::getSmallNumberPath(CST_CLUBS, CFT_ACE));
    _smallSuitSprite = cocos2d::Sprite::create(CardResourceHelper::getSuitPath(CST_CLUBS));
    _bigNumberSprite = cocos2d::Sprite::create(CardResourceHelper::getBigNumberPath(CST_CLUBS, CFT_ACE));
    _bigSuitSprite = cocos2d::Sprite::create(CardResourceHelper::getSuitPath(CST_CLUBS));

    _backgroundSprite->setPosition(cocos2d::Vec2(kCardSize.width * 0.5f, kCardSize.height * 0.5f));
    _smallNumberSprite->setPosition(cocos2d::Vec2(35.0f, 240.0f));
    _smallSuitSprite->setPosition(cocos2d::Vec2(35.0f, 195.0f));
    _bigNumberSprite->setPosition(cocos2d::Vec2(91.0f, 165.0f));
    _bigSuitSprite->setPosition(cocos2d::Vec2(91.0f, 75.0f));
    _bigSuitSprite->setScale(1.7f);

    addChild(_backgroundSprite);
    addChild(_smallNumberSprite);
    addChild(_smallSuitSprite);
    addChild(_bigNumberSprite);
    addChild(_bigSuitSprite);

    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event*) {
        return _isInputEnabled && isVisible() && containsTouch(touch);
    };
    touchListener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event*) {
        if (_isInputEnabled && containsTouch(touch) && _onTapCallback)
        {
            _onTapCallback(_cardId);
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    return true;
}

void CardView::setCardData(int cardId, CardFaceType cardFace, CardSuitType cardSuit)
{
    _cardId = cardId;
    _smallNumberSprite->setTexture(CardResourceHelper::getSmallNumberPath(cardSuit, cardFace));
    _smallSuitSprite->setTexture(CardResourceHelper::getSuitPath(cardSuit));
    _bigNumberSprite->setTexture(CardResourceHelper::getBigNumberPath(cardSuit, cardFace));
    _bigSuitSprite->setTexture(CardResourceHelper::getSuitPath(cardSuit));
}

void CardView::setInputEnabled(bool inputEnabled)
{
    _isInputEnabled = inputEnabled;
}

void CardView::setTapCallback(const std::function<void(int)>& onTapCallback)
{
    _onTapCallback = onTapCallback;
}

bool CardView::containsTouch(cocos2d::Touch* touch) const
{
    const cocos2d::Vec2 location = convertToNodeSpaceAR(touch->getLocation());
    const cocos2d::Rect bounds(-kCardSize.width * 0.5f, -kCardSize.height * 0.5f, kCardSize.width, kCardSize.height);
    return bounds.containsPoint(location);
}
}
