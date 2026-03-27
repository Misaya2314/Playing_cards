#ifndef __GAME_VIEW_H__
#define __GAME_VIEW_H__

#include <functional>
#include <unordered_map>
#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/CardView.h"
#include "views/PlayFieldView.h"
#include "views/StackView.h"

namespace playingcards
{
// 整局可见节点都挂在这里，顺便统一处理卡牌移动动画。
class GameView : public cocos2d::Node
{
public:
    CREATE_FUNC(GameView);
    virtual bool init() override;
    void buildFromModel(const GameModel& gameModel);
    void refresh(const GameModel& gameModel, bool canUndo, bool inputEnabled);
    void setInteractionEnabled(bool inputEnabled, bool canUndo);
    void setPlayfieldCardClickCallback(const std::function<void(int)>& onPlayfieldCardClickCallback);
    void setStackClickCallback(const std::function<void()>& onStackClickCallback);
    void setUndoClickCallback(const std::function<void()>& onUndoClickCallback);
    void playCardToTrayAnimation(int cardId, const std::function<void()>& onComplete);
    void playCardToPositionAnimation(int cardId,
                                     const cocos2d::Vec2& targetPosition,
                                     const std::function<void()>& onComplete);
    cocos2d::Vec2 getStackPosition() const;

private:
    // 刷新时根据区域决定牌应该停在哪。
    cocos2d::Vec2 resolveCardPosition(const CardModel& cardModel, bool isTopStackCard) const;
    void refreshCardInteraction(CardView* cardView,
                                const CardModel& cardModel,
                                bool isTopStackCard,
                                bool inputEnabled);
    void runCardMoveAnimation(int cardId,
                              const cocos2d::Vec2& targetPosition,
                              const std::function<void()>& onComplete);

    std::function<void(int)> _onPlayfieldCardClickCallback;
    std::function<void()> _onStackClickCallback;
    std::unordered_map<int, CardView*> _cardViews;
    PlayFieldView* _playFieldView = nullptr;
    StackView* _stackView = nullptr;
    cocos2d::Node* _cardLayer = nullptr;
};
}

#endif // __GAME_VIEW_H__
