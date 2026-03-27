#ifndef __PLAYFIELD_VIEW_H__
#define __PLAYFIELD_VIEW_H__

#include "cocos2d.h"

namespace playingcards
{
// 桌面区背景，暂时比较简单。
class PlayFieldView : public cocos2d::Node
{
public:
    CREATE_FUNC(PlayFieldView);
    virtual bool init() override;
};
}

#endif // __PLAYFIELD_VIEW_H__
