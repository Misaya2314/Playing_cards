视频演示：

https://github.com/user-attachments/assets/a27d983e-2947-4166-ae61-b8d89c460efa

已经实现的内容：

- 读关卡 JSON
- 显示桌面牌、牌堆和当前手牌
- 点击牌堆翻牌
- 点击桌面牌做差 1 匹配
- 支持撤销

## 代码结构

### `Classes/AppDelegate.*`

程序入口。这里主要做 cocos 初始化、窗口创建、分辨率设置，然后进入 `GameScene`。

### `Classes/GameScene.*`

场景入口。这里没有放太多东西，主要就是创建 `GameController` 并启动第一关。

### `Classes/configs/`

这一层只管关卡配置。

- `models/` 里是配置结构，比如 `LevelConfig`
- `loaders/` 里是 JSON 读取逻辑

我的想法是把“关卡长什么样”和“运行时怎么变化”分开。

### `Classes/models/`

这里放运行时数据。

- `CardTypes.h`：花色、点数、区域这些枚举
- `CardModel.*`：单张牌的数据
- `GameModel.*`：整局牌的数据
- `UndoRecord.h`：撤销时要用到的记录

简单说，这层就是当前牌局状态。

### `Classes/views/`

这里放界面相关的内容。

- `GameView.*`：整局界面的总入口
- `PlayFieldView.*`：上半部分桌面区
- `StackView.*`：下半部分牌堆、手牌和撤销按钮
- `CardView.*`：单张卡牌显示

这一层只管显示、点击和动画，不直接处理规则。

### `Classes/controllers/`

这里是主要业务逻辑。

- `GameController.*`：总控，负责把模型、界面和撤销串起来
- `PlayFieldController.*`：处理桌面牌点击
- `StackController.*`：处理牌堆点击

### `Classes/managers/`

目前只有 `UndoManager.*`，专门存撤销记录。

### `Classes/services/`

这里放一些不太适合塞进控制器里的小逻辑。

- `CardMatchService.h`：判断能不能匹配
- `GameModelFromLevelGenerator.*`：把关卡配置转成运行时模型

### `Classes/utils/`

目前主要是 `CardResourceHelper.*`，负责根据花色和点数找到对应图片。

### `Resources/`

- `levels/`：关卡 JSON
- `res/`：牌面资源

## 代码运行步骤

启动后会先在 `AppDelegate` 里进场景，然后 `GameScene` 创建 `GameController`。

`GameController` 做的事情比较集中：

1. 读取关卡 JSON
2. 生成 `GameModel`
3. 创建 `GameView`
4. 绑定点击回调
5. 处理动画和撤销

桌面牌点击时，逻辑会走到 `PlayFieldController`。  
牌堆点击时，逻辑会走到 `StackController`。  
两边如果操作成功，都会生成一条 `UndoRecord`，最后交给 `GameController` 统一做动画和刷新。

## 后面如果要加一张牌

### 只是关卡里多放一张普通牌

这种最简单，改 `Resources/levels/level_1.json` 就行。

在 `Playfield` 或 `Stack` 里多加一项，比如：

```json
{
  "CardFace": 5,
  "CardSuit": 2,
  "Position": { "x": 500, "y": 700 }
}
```

因为现在的代码本来就是按配置生成卡牌的，所以：

- `LevelConfigLoader` 会读出来
- `GameModelFromLevelGenerator` 会生成运行时卡牌
- `GameView` 会自动创建对应的 `CardView`

也就是说，普通牌基本已经是按配置走了。

### 如果不是普通牌，而是想换一种牌面表现

主要改下面两个地方：

- `Classes/utils/CardResourceHelper.*`
- `Classes/views/CardView.*`

我的理解是：

- `CardResourceHelper` 决定用哪张图
- `CardView` 决定怎么把这些图拼出来

所以以后如果要做新主题，或者某种特殊牌长得和普通牌不一样，优先就在这两层改，不用先碰控制器。

## 后面如果要加一种新的撤销类型

当前项目里只有两种撤销：

- `DrawFromStack`
- `MatchFromPlayfield`

如果以后要加新的回退类型

### 1. 先改 `UndoRecordType`

文件：

- `Classes/models/UndoRecord.h`

先把新的动作类型加进去。

### 2. 看这个动作回退时到底要恢复什么

比如有的新动作可能除了 `movedCardId` 以外，还要记：

- 原来的区域
- 原来的顺序
- 被联动影响的另一张牌

如果当前 `UndoRecord` 不够，就直接补字段，不用强行复用老结构。

### 3. 在正向逻辑发生时把记录写进去

如果动作发生在桌面区逻辑里，就改 `PlayFieldController`。  
如果动作发生在牌堆逻辑里，就改 `StackController`。  
如果以后新功能有自己的控制器，就在那个控制器里记。

### 4. 在 `GameController` 里补真正的撤销处理

主要看这两个函数：

- `revertUndoRecord`
- `getUndoTargetPosition`
