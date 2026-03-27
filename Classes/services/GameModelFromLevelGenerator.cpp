#include "services/GameModelFromLevelGenerator.h"

namespace playingcards
{
GameModel GameModelFromLevelGenerator::generateGameModel(const LevelConfig& levelConfig) const
{
    GameModel gameModel;
    std::vector<int> playfieldCardIds;
    std::vector<int> stackCardIds;
    int nextCardId = 1;

    for (const LevelCardConfig& cardConfig : levelConfig.playfieldCards)
    {
        const int cardId = nextCardId++;
        CardModel cardModel(cardId, cardConfig.cardFace, cardConfig.cardSuit, cardConfig.position, CardZoneType::Playfield);
        gameModel.addCard(cardModel);
        playfieldCardIds.push_back(cardId);
    }

    for (std::size_t index = 0; index < levelConfig.stackCards.size(); ++index)
    {
        const LevelCardConfig& cardConfig = levelConfig.stackCards[index];
        const bool isTrayCard = index + 1 == levelConfig.stackCards.size();
        const CardZoneType cardZone = isTrayCard ? CardZoneType::Tray : CardZoneType::Stack;
        const int cardId = nextCardId++;
        CardModel cardModel(cardId, cardConfig.cardFace, cardConfig.cardSuit, cardConfig.position, cardZone);
        gameModel.addCard(cardModel);
        if (isTrayCard)
        {
            gameModel.setCurrentTrayCardId(cardId);
        }
        else
        {
            stackCardIds.push_back(cardId);
        }
    }

    gameModel.setPlayfieldCardIds(playfieldCardIds);
    gameModel.setStackCardIds(stackCardIds);
    return gameModel;
}
}
