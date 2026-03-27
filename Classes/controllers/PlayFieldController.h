#ifndef __PLAYFIELD_CONTROLLER_H__
#define __PLAYFIELD_CONTROLLER_H__

#include "models/GameModel.h"
#include "models/UndoRecord.h"

namespace playingcards
{
// 桌面牌点击逻辑放这里。
class PlayFieldController
{
public:
    void init(GameModel* gameModel);
    bool handleCardClick(int cardId, UndoRecord& outUndoRecord);

private:
    GameModel* _gameModel = nullptr;
};
}

#endif // __PLAYFIELD_CONTROLLER_H__
