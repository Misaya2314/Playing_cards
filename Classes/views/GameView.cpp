#include "views/GameView.h"

namespace playingcards
{
namespace
{
const cocos2d::Size kDesignSize(1080.0f, 2080.0f);
const float kAnimationDuration = 0.18f;
const int kMovingZOrder = 5000;
}

bool GameView::init()
{
    if (!Node::init())
    {
        return false;
    }

    setContentSize(kDesignSize);
    _playFieldView = PlayFieldView::create();
    _stackView = StackView::create();
    _cardLayer = cocos2d::Node::create();

    _playFieldView->setPosition(cocos2d::Vec2(0.0f, 580.0f));
    _stackView->setPosition(cocos2d::Vec2::ZERO);
    addChild(_playFieldView);
    addChild(_stackView);
    addChild(_cardLayer, 10);
    return true;
}

void GameView::buildFromModel(const GameModel& gameModel)
{
    _cardLayer->removeAllChildrenWithCleanup(true);
    _cardViews.clear();

    for (int cardId : gameModel.getAllCardIds())
    {
        const CardModel* cardModel = gameModel.getCardModel(cardId);
        if (cardModel == nullptr)
        {
            continue;
        }

        auto cardView = CardView::create();
        cardView->setCardData(cardId, cardModel->getCardFace(), cardModel->getCardSuit());
        _cardLayer->addChild(cardView);
        _cardViews[cardId] = cardView;
    }
}

void GameView::refresh(const GameModel& gameModel, bool canUndo, bool inputEnabled)
{
    const int topStackCardId = gameModel.getTopStackCardId();
    for (int cardId : gameModel.getAllCardIds())
    {
        const CardModel* cardModel = gameModel.getCardModel(cardId);
        CardView* cardView = _cardViews[cardId];
        if (cardModel == nullptr || cardView == nullptr)
        {
            continue;
        }

        const bool isTopStackCard = cardId == topStackCardId;
        const CardZoneType cardZone = cardModel->getCardZone();
        const bool isVisible = cardZone == CardZoneType::Playfield
            || cardZone == CardZoneType::Tray
            || (cardZone == CardZoneType::Stack && isTopStackCard);

        cardView->setVisible(isVisible);
        if (!isVisible)
        {
            continue;
        }

        cardView->setPosition(resolveCardPosition(*cardModel, isTopStackCard));
        refreshCardInteraction(cardView, *cardModel, isTopStackCard, inputEnabled);
    }

    const std::vector<int>& playfieldCardIds = gameModel.getPlayfieldCardIds();
    for (std::size_t index = 0; index < playfieldCardIds.size(); ++index)
    {
        CardView* cardView = _cardViews[playfieldCardIds[index]];
        if (cardView != nullptr)
        {
            cardView->setLocalZOrder(static_cast<int>(100 + index));
        }
    }

    const int trayCardId = gameModel.getCurrentTrayCardId();
    if (_cardViews[trayCardId] != nullptr)
    {
        _cardViews[trayCardId]->setLocalZOrder(1000);
    }

    if (topStackCardId >= 0 && _cardViews[topStackCardId] != nullptr)
    {
        _cardViews[topStackCardId]->setLocalZOrder(900);
    }

    _stackView->setStackCount(static_cast<int>(gameModel.getStackCardIds().size()));
    _stackView->setUndoEnabled(canUndo && inputEnabled);
}

void GameView::setInteractionEnabled(bool inputEnabled, bool canUndo)
{
    for (const auto& cardEntry : _cardViews)
    {
        cardEntry.second->setInputEnabled(inputEnabled && cardEntry.second->isVisible());
    }

    _stackView->setUndoEnabled(canUndo && inputEnabled);
}

void GameView::setPlayfieldCardClickCallback(const std::function<void(int)>& onPlayfieldCardClickCallback)
{
    _onPlayfieldCardClickCallback = onPlayfieldCardClickCallback;
}

void GameView::setStackClickCallback(const std::function<void()>& onStackClickCallback)
{
    _onStackClickCallback = onStackClickCallback;
}

void GameView::setUndoClickCallback(const std::function<void()>& onUndoClickCallback)
{
    _stackView->setUndoCallback(onUndoClickCallback);
}

void GameView::playCardToTrayAnimation(int cardId, const std::function<void()>& onComplete)
{
    runCardMoveAnimation(cardId, _stackView->getTrayPosition(), onComplete);
}

void GameView::playCardToPositionAnimation(int cardId,
                                           const cocos2d::Vec2& targetPosition,
                                           const std::function<void()>& onComplete)
{
    runCardMoveAnimation(cardId, targetPosition, onComplete);
}

cocos2d::Vec2 GameView::getStackPosition() const
{
    return _stackView->getStackPosition();
}

cocos2d::Vec2 GameView::resolveCardPosition(const CardModel& cardModel, bool isTopStackCard) const
{
    switch (cardModel.getCardZone())
    {
    case CardZoneType::Playfield:
        return cardModel.getBoardPosition();
    case CardZoneType::Stack:
        return isTopStackCard ? _stackView->getStackPosition() : cocos2d::Vec2(-1000.0f, -1000.0f);
    case CardZoneType::Tray:
        return _stackView->getTrayPosition();
    case CardZoneType::Discard:
    default:
        return cocos2d::Vec2(-1000.0f, -1000.0f);
    }
}

void GameView::refreshCardInteraction(CardView* cardView,
                                      const CardModel& cardModel,
                                      bool isTopStackCard,
                                      bool inputEnabled)
{
    if (cardModel.getCardZone() == CardZoneType::Playfield)
    {
        cardView->setTapCallback(_onPlayfieldCardClickCallback);
        cardView->setInputEnabled(inputEnabled);
        return;
    }

    if (cardModel.getCardZone() == CardZoneType::Stack && isTopStackCard)
    {
        cardView->setTapCallback([this](int) {
            if (_onStackClickCallback)
            {
                _onStackClickCallback();
            }
        });
        cardView->setInputEnabled(inputEnabled);
        return;
    }

    cardView->setTapCallback(std::function<void(int)>());
    cardView->setInputEnabled(false);
}

void GameView::runCardMoveAnimation(int cardId,
                                    const cocos2d::Vec2& targetPosition,
                                    const std::function<void()>& onComplete)
{
    CardView* cardView = _cardViews[cardId];
    if (cardView == nullptr)
    {
        if (onComplete)
        {
            onComplete();
        }
        return;
    }

    cardView->stopAllActions();
    cardView->setVisible(true);
    cardView->setLocalZOrder(kMovingZOrder);
    auto moveAction = cocos2d::MoveTo::create(kAnimationDuration, targetPosition);
    auto finishAction = cocos2d::CallFunc::create([onComplete]() {
        if (onComplete)
        {
            onComplete();
        }
    });

    cardView->runAction(cocos2d::Sequence::create(moveAction, finishAction, nullptr));
}
}
