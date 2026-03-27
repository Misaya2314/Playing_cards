#ifndef __UNDO_RECORD_H__
#define __UNDO_RECORD_H__

namespace playingcards
{
enum class UndoRecordType
{
    DrawFromStack,
    MatchFromPlayfield
};

// 当前撤销只记最小必要信息，不做整局快照。
struct UndoRecord
{
    UndoRecordType recordType = UndoRecordType::DrawFromStack;
    int movedCardId = -1;
    int previousTrayCardId = -1;
    int playfieldIndex = -1;
};
}

#endif // __UNDO_RECORD_H__
