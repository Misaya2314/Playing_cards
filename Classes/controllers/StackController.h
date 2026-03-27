#ifndef __STACK_CONTROLLER_H__
#define __STACK_CONTROLLER_H__

#include "models/GameModel.h"
#include "models/UndoRecord.h"

namespace playingcards
{
// 牌堆翻牌逻辑。
class StackController
{
public:
    void init(GameModel* gameModel);
    bool handleStackClick(UndoRecord& outUndoRecord);

private:
    GameModel* _gameModel = nullptr;
};
}

#endif // __STACK_CONTROLLER_H__
