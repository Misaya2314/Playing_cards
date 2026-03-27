#include "controllers/PlayFieldController.h"
#include "services/CardMatchService.h"

namespace playingcards
{
void PlayFieldController::init(GameModel* gameModel)
{
    _gameModel = gameModel;
}

bool PlayFieldController::handleCardClick(int cardId, UndoRecord& outUndoRecord)
{
    if (_gameModel == nullptr)
    {
        return false;
    }

    CardModel* selectedCard = _gameModel->getCardModel(cardId);
    CardModel* trayCard = _gameModel->getCardModel(_gameModel->getCurrentTrayCardId());
    if (selectedCard == nullptr || trayCard == nullptr || selectedCard->getCardZone() != CardZoneType::Playfield)
    {
        return false;
    }

    if (!CardMatchService::canMatch(selectedCard->getCardFace(), trayCard->getCardFace()))
    {
        return false;
    }

    const int playfieldIndex = _gameModel->removePlayfieldCard(cardId);
    if (playfieldIndex < 0)
    {
        return false;
    }

    const int previousTrayCardId = _gameModel->getCurrentTrayCardId();
    _gameModel->getCardModel(previousTrayCardId)->setCardZone(CardZoneType::Discard);
    selectedCard->setCardZone(CardZoneType::Tray);
    _gameModel->setCurrentTrayCardId(cardId);

    outUndoRecord.recordType = UndoRecordType::MatchFromPlayfield;
    outUndoRecord.movedCardId = cardId;
    outUndoRecord.previousTrayCardId = previousTrayCardId;
    outUndoRecord.playfieldIndex = playfieldIndex;
    return true;
}
}
