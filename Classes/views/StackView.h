#ifndef __STACK_VIEW_H__
#define __STACK_VIEW_H__

#include <functional>
#include "cocos2d.h"

namespace playingcards
{
// 底部区域：牌堆、当前手牌和撤销按钮。
class StackView : public cocos2d::Node
{
public:
    CREATE_FUNC(StackView);
    virtual bool init() override;
    cocos2d::Vec2 getTrayPosition() const;
    cocos2d::Vec2 getStackPosition() const;
    void setStackCount(int stackCount);
    void setUndoEnabled(bool enabled);
    void setUndoCallback(const std::function<void()>& onUndoCallback);

private:
    void refreshUndoState();

    std::function<void()> _onUndoCallback;
    cocos2d::Label* _stackCountLabel = nullptr;
    cocos2d::MenuItemLabel* _undoMenuItem = nullptr;
    bool _isUndoEnabled = false;
};
}

#endif // __STACK_VIEW_H__
