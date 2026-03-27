#include "managers/UndoManager.h"

namespace playingcards
{
void UndoManager::clear()
{
    _records.clear();
}

void UndoManager::pushRecord(const UndoRecord& undoRecord)
{
    _records.push_back(undoRecord);
}

bool UndoManager::canUndo() const
{
    return !_records.empty();
}

UndoRecord UndoManager::popRecord()
{
    if (_records.empty())
    {
        return UndoRecord();
    }

    const UndoRecord undoRecord = _records.back();
    _records.pop_back();
    return undoRecord;
}
}
