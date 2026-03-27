#include "views/StackView.h"

namespace playingcards
{
namespace
{
const float kStackAreaHeight = 580.0f;
const cocos2d::Size kStackSize(1080.0f, kStackAreaHeight);
const cocos2d::Vec2 kStackPosition(300.0f, 250.0f);
const cocos2d::Vec2 kTrayPosition(760.0f, 250.0f);
}

bool StackView::init()
{
    if (!Node::init())
    {
        return false;
    }

    setContentSize(kStackSize);
    auto background = cocos2d::LayerColor::create(cocos2d::Color4B(11, 52, 36, 255),
                                                  static_cast<int>(kStackSize.width),
                                                  static_cast<int>(kStackSize.height));
    addChild(background);

    auto stackLabel = cocos2d::Label::createWithTTF("Stack", "fonts/arial.ttf", 34);
    stackLabel->setPosition(cocos2d::Vec2(kStackPosition.x, 505.0f));
    addChild(stackLabel);

    auto trayLabel = cocos2d::Label::createWithTTF("Tray", "fonts/arial.ttf", 34);
    trayLabel->setPosition(cocos2d::Vec2(kTrayPosition.x, 505.0f));
    addChild(trayLabel);

    _stackCountLabel = cocos2d::Label::createWithTTF("x0", "fonts/arial.ttf", 30);
    _stackCountLabel->setPosition(cocos2d::Vec2(kStackPosition.x, 70.0f));
    addChild(_stackCountLabel);

    auto undoLabel = cocos2d::Label::createWithTTF("Undo", "fonts/arial.ttf", 34);
    _undoMenuItem = cocos2d::MenuItemLabel::create(undoLabel, [this](cocos2d::Ref*) {
        if (_isUndoEnabled && _onUndoCallback)
        {
            _onUndoCallback();
        }
    });

    auto menu = cocos2d::Menu::create(_undoMenuItem, nullptr);
    menu->setPosition(cocos2d::Vec2(960.0f, 250.0f));
    addChild(menu);
    refreshUndoState();
    return true;
}

cocos2d::Vec2 StackView::getTrayPosition() const
{
    return kTrayPosition;
}

cocos2d::Vec2 StackView::getStackPosition() const
{
    return kStackPosition;
}

void StackView::setStackCount(int stackCount)
{
    if (_stackCountLabel != nullptr)
    {
        _stackCountLabel->setString(cocos2d::StringUtils::format("x%d", stackCount));
    }
}

void StackView::setUndoEnabled(bool enabled)
{
    _isUndoEnabled = enabled;
    refreshUndoState();
}

void StackView::setUndoCallback(const std::function<void()>& onUndoCallback)
{
    _onUndoCallback = onUndoCallback;
}

void StackView::refreshUndoState()
{
    if (_undoMenuItem == nullptr)
    {
        return;
    }

    _undoMenuItem->setEnabled(_isUndoEnabled);
    auto label = dynamic_cast<cocos2d::Label*>(_undoMenuItem->getLabel());
    if (label != nullptr)
    {
        label->setTextColor(_isUndoEnabled ? cocos2d::Color4B::WHITE : cocos2d::Color4B(120, 120, 120, 255));
    }
}
}
