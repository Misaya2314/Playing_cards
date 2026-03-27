#ifndef __UNDO_MANAGER_H__
#define __UNDO_MANAGER_H__

#include <vector>
#include "models/UndoRecord.h"

namespace playingcards
{
// 一个很简单的撤销栈。
class UndoManager
{
public:
    void clear();
    void pushRecord(const UndoRecord& undoRecord);
    bool canUndo() const;
    UndoRecord popRecord();

private:
    std::vector<UndoRecord> _records;
};
}

#endif // __UNDO_MANAGER_H__
