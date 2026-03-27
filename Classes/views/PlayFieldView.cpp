#include "views/PlayFieldView.h"

namespace playingcards
{
namespace
{
const cocos2d::Size kPlayFieldSize(1080.0f, 1500.0f);
}

bool PlayFieldView::init()
{
    if (!Node::init())
    {
        return false;
    }

    setContentSize(kPlayFieldSize);
    auto background = cocos2d::LayerColor::create(cocos2d::Color4B(14, 84, 56, 255),
                                                  static_cast<int>(kPlayFieldSize.width),
                                                  static_cast<int>(kPlayFieldSize.height));
    addChild(background);

    auto titleLabel = cocos2d::Label::createWithTTF("Playfield", "fonts/arial.ttf", 42);
    titleLabel->setPosition(cocos2d::Vec2(kPlayFieldSize.width * 0.5f, kPlayFieldSize.height - 48.0f));
    addChild(titleLabel);
    return true;
}
}
