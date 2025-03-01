#ifndef REWARDBLOCK_H
#define REWARDBLOCK_H

#include <QRect>
#include <QPainter>
#include <QRandomGenerator>

class RewardBlock {
public:
    RewardBlock(int windowWidth, int windowHeight); // 构造函数
    void reset();                                  // 重置奖励方块的位置
    void draw(QPainter *painter);                  // 绘制奖励方块
    bool checkCollision(const QRect &playerRect);  // 检测与玩家的碰撞
    QRect getRect() const;                         // 获取奖励方块的矩形区域
    bool isActive() const;                         // 判断奖励方块是否激活

private:
    int windowWidth;      // 窗口宽度
    int windowHeight;     // 窗口高度
    QRect rect;           // 奖励方块的矩形区域
    bool active;          // 奖励方块是否激活
};

#endif // REWARDBLOCK_H
