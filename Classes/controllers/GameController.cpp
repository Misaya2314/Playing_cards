#include "controllers/GameController.h"
#include "views/GameView.h"

namespace playingcards
{
GameController::GameController(cocos2d::Node* sceneRoot)
    : _sceneRoot(sceneRoot)
{
}

void GameController::startGame(int levelId)
{
    LevelConfig levelConfig;
    if (!_levelConfigLoader.loadLevelConfig(levelId, levelConfig))
    {
        cocos2d::log("Failed to load level config: %d", levelId);
        return;
    }

    _gameModel.reset(new GameModel(_gameModelGenerator.generateGameModel(levelConfig)));
    _undoManager.clear();
    _playFieldController.init(_gameModel.get());
    _stackController.init(_gameModel.get());
    _isInputLocked = false;

    if (_gameView != nullptr)
    {
        _gameView->removeFromParent();
        _gameView = nullptr;
    }

    _gameView = GameView::create();
    _gameView->setPlayfieldCardClickCallback([this](int cardId) { handlePlayfieldCardClick(cardId); });
    _gameView->setStackClickCallback([this]() { handleStackClick(); });
    _gameView->setUndoClickCallback([this]() { undo(); });
    _gameView->buildFromModel(*_gameModel);
    _sceneRoot->addChild(_gameView);
    refreshView();
}

void GameController::undo()
{
    if (_gameModel == nullptr || _gameView == nullptr || _isInputLocked || !_undoManager.canUndo())
    {
        return;
    }

    const UndoRecord undoRecord = _undoManager.popRecord();
    revertUndoRecord(undoRecord);
    lockInput();
    _gameView->playCardToPositionAnimation(undoRecord.movedCardId,
                                           getUndoTargetPosition(undoRecord),
                                           [this]() { finishAnimation(); });
}

void GameController::handlePlayfieldCardClick(int cardId)
{
    if (_gameModel == nullptr || _gameView == nullptr || _isInputLocked)
    {
        return;
    }

    UndoRecord undoRecord;
    if (!_playFieldController.handleCardClick(cardId, undoRecord))
    {
        return;
    }

    _undoManager.pushRecord(undoRecord);
    lockInput();
    _gameView->playCardToTrayAnimation(undoRecord.movedCardId, [this]() { finishAnimation(); });
}

void GameController::handleStackClick()
{
    if (_gameModel == nullptr || _gameView == nullptr || _isInputLocked)
    {
        return;
    }

    UndoRecord undoRecord;
    if (!_stackController.handleStackClick(undoRecord))
    {
        return;
    }

    _undoManager.pushRecord(undoRecord);
    lockInput();
    _gameView->playCardToTrayAnimation(undoRecord.movedCardId, [this]() { finishAnimation(); });
}

void GameController::refreshView()
{
    if (_gameModel != nullptr && _gameView != nullptr)
    {
        _gameView->refresh(*_gameModel, _undoManager.canUndo(), !_isInputLocked);
    }
}

void GameController::lockInput()
{
    _isInputLocked = true;
    if (_gameView != nullptr)
    {
        _gameView->setInteractionEnabled(false, false);
    }
}

void GameController::finishAnimation()
{
    _isInputLocked = false;
    refreshView();
}

void GameController::revertUndoRecord(const UndoRecord& undoRecord)
{
    CardModel* movedCard = _gameModel->getCardModel(undoRecord.movedCardId);
    CardModel* previousTrayCard = _gameModel->getCardModel(undoRecord.previousTrayCardId);
    if (movedCard == nullptr || previousTrayCard == nullptr)
    {
        return;
    }

    previousTrayCard->setCardZone(CardZoneType::Tray);
    _gameModel->setCurrentTrayCardId(undoRecord.previousTrayCardId);
    if (undoRecord.recordType == UndoRecordType::DrawFromStack)
    {
        movedCard->setCardZone(CardZoneType::Stack);
        _gameModel->pushStackCard(undoRecord.movedCardId);
        return;
    }

    movedCard->setCardZone(CardZoneType::Playfield);
    _gameModel->insertPlayfieldCard(undoRecord.movedCardId, undoRecord.playfieldIndex);
}

cocos2d::Vec2 GameController::getUndoTargetPosition(const UndoRecord& undoRecord) const
{
    if (undoRecord.recordType == UndoRecordType::DrawFromStack)
    {
        return _gameView->getStackPosition();
    }

    const CardModel* cardModel = _gameModel->getCardModel(undoRecord.movedCardId);
    return cardModel == nullptr ? cocos2d::Vec2::ZERO : cardModel->getBoardPosition();
}
}
