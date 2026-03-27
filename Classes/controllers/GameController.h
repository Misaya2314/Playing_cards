#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include <memory>
#include "cocos2d.h"
#include "configs/loaders/LevelConfigLoader.h"
#include "controllers/PlayFieldController.h"
#include "controllers/StackController.h"
#include "managers/UndoManager.h"
#include "services/GameModelFromLevelGenerator.h"

namespace playingcards
{
class GameView;

// 这个类把加载、点击、动画和撤销都串在一起。
class GameController
{
public:
    explicit GameController(cocos2d::Node* sceneRoot);
    void startGame(int levelId);
    void undo();

private:
    void handlePlayfieldCardClick(int cardId);
    void handleStackClick();
    void refreshView();
    void lockInput();
    void finishAnimation();
    void revertUndoRecord(const UndoRecord& undoRecord);
    cocos2d::Vec2 getUndoTargetPosition(const UndoRecord& undoRecord) const;

    cocos2d::Node* _sceneRoot = nullptr;
    std::unique_ptr<GameModel> _gameModel;
    GameView* _gameView = nullptr;
    LevelConfigLoader _levelConfigLoader;
    GameModelFromLevelGenerator _gameModelGenerator;
    PlayFieldController _playFieldController;
    StackController _stackController;
    UndoManager _undoManager;
    // 动画期间统一锁输入，避免状态和画面不同步。
    bool _isInputLocked = false;
};
}

#endif // __GAME_CONTROLLER_H__
