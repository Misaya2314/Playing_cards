#include <algorithm>
#include "models/GameModel.h"

namespace playingcards
{
GameModel::GameModel()
    : _currentTrayCardId(-1)
{
}

void GameModel::addCard(const CardModel& cardModel)
{
    _cards[cardModel.getCardId()] = cardModel;
    _allCardIds.push_back(cardModel.getCardId());
}

const std::vector<int>& GameModel::getAllCardIds() const
{
    return _allCardIds;
}

const std::vector<int>& GameModel::getPlayfieldCardIds() const
{
    return _playfieldCardIds;
}

const std::vector<int>& GameModel::getStackCardIds() const
{
    return _stackCardIds;
}

CardModel* GameModel::getCardModel(int cardId)
{
    auto iterator = _cards.find(cardId);
    return iterator == _cards.end() ? nullptr : &iterator->second;
}

const CardModel* GameModel::getCardModel(int cardId) const
{
    auto iterator = _cards.find(cardId);
    return iterator == _cards.end() ? nullptr : &iterator->second;
}

int GameModel::getCurrentTrayCardId() const
{
    return _currentTrayCardId;
}

void GameModel::setCurrentTrayCardId(int cardId)
{
    _currentTrayCardId = cardId;
}

void GameModel::setPlayfieldCardIds(const std::vector<int>& cardIds)
{
    _playfieldCardIds = cardIds;
}

void GameModel::setStackCardIds(const std::vector<int>& cardIds)
{
    _stackCardIds = cardIds;
}

int GameModel::getTopStackCardId() const
{
    return _stackCardIds.empty() ? -1 : _stackCardIds.back();
}

int GameModel::findPlayfieldCardIndex(int cardId) const
{
    auto iterator = std::find(_playfieldCardIds.begin(), _playfieldCardIds.end(), cardId);
    if (iterator == _playfieldCardIds.end())
    {
        return -1;
    }

    return static_cast<int>(iterator - _playfieldCardIds.begin());
}

int GameModel::removePlayfieldCard(int cardId)
{
    const int index = findPlayfieldCardIndex(cardId);
    if (index < 0)
    {
        return -1;
    }

    _playfieldCardIds.erase(_playfieldCardIds.begin() + index);
    return index;
}

void GameModel::insertPlayfieldCard(int cardId, int index)
{
    const int safeIndex = std::max(0, std::min(index, static_cast<int>(_playfieldCardIds.size())));
    _playfieldCardIds.insert(_playfieldCardIds.begin() + safeIndex, cardId);
}

int GameModel::popStackCard()
{
    if (_stackCardIds.empty())
    {
        return -1;
    }

    const int cardId = _stackCardIds.back();
    _stackCardIds.pop_back();
    return cardId;
}

void GameModel::pushStackCard(int cardId)
{
    _stackCardIds.push_back(cardId);
}
}
