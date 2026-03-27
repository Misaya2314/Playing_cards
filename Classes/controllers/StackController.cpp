#include "controllers/StackController.h"

namespace playingcards
{
void StackController::init(GameModel* gameModel)
{
    _gameModel = gameModel;
}

bool StackController::handleStackClick(UndoRecord& outUndoRecord)
{
    if (_gameModel == nullptr)
    {
        return false;
    }

    const int movedCardId = _gameModel->popStackCard();
    if (movedCardId < 0)
    {
        return false;
    }

    const int previousTrayCardId = _gameModel->getCurrentTrayCardId();
    _gameModel->getCardModel(previousTrayCardId)->setCardZone(CardZoneType::Discard);
    _gameModel->getCardModel(movedCardId)->setCardZone(CardZoneType::Tray);
    _gameModel->setCurrentTrayCardId(movedCardId);

    outUndoRecord.recordType = UndoRecordType::DrawFromStack;
    outUndoRecord.movedCardId = movedCardId;
    outUndoRecord.previousTrayCardId = previousTrayCardId;
    outUndoRecord.playfieldIndex = -1;
    return true;
}
}
