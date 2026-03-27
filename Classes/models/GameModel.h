#ifndef __GAME_MODEL_H__
#define __GAME_MODEL_H__

#include <unordered_map>
#include <vector>
#include "models/CardModel.h"

namespace playingcards
{
// 整局牌的运行时状态都放这里。
class GameModel
{
public:
    GameModel();
    void addCard(const CardModel& cardModel);
    const std::vector<int>& getAllCardIds() const;
    const std::vector<int>& getPlayfieldCardIds() const;
    const std::vector<int>& getStackCardIds() const;
    CardModel* getCardModel(int cardId);
    const CardModel* getCardModel(int cardId) const;
    int getCurrentTrayCardId() const;
    void setCurrentTrayCardId(int cardId);
    void setPlayfieldCardIds(const std::vector<int>& cardIds);
    void setStackCardIds(const std::vector<int>& cardIds);
    int getTopStackCardId() const;
    int findPlayfieldCardIndex(int cardId) const;
    int removePlayfieldCard(int cardId);
    void insertPlayfieldCard(int cardId, int index);
    int popStackCard();
    void pushStackCard(int cardId);

private:
    std::unordered_map<int, CardModel> _cards;
    std::vector<int> _allCardIds;
    std::vector<int> _playfieldCardIds;
    // 这里按从底到顶保存，back() 就是当前牌堆顶。
    std::vector<int> _stackCardIds;
    int _currentTrayCardId;
};
}

#endif // __GAME_MODEL_H__
