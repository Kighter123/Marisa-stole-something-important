#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include "Player.h"
#include "Obstacle.h"
#include "HorizontalObstacle.h"
#include "Ground.h"
#include "RewardBlock.h"
class GameWindow : public QMainWindow {
    Q_OBJECT
public:
    const int pertime=14;//帧数
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void paintEvent(QPaintEvent *event) ;//初始化绘制函数
    void keyPressEvent(QKeyEvent *event) ;//键盘按键监听
    void updateScore();

private slots:
    void updateGame();


private:
    Player *player;
    Ground *ground;
    QList<Obstacle*> obstacles;  // 顶部障碍物
    QList<HorizontalObstacle*> horiObstacles;  // 横向障碍物
    QTimer *timer;
    QTimer *scoreTimer;
    float elapsedTime;  // 跟踪游戏时间（秒）
    int obstacleCount;  // 顶部障碍物数量
    int horiObstacleCount;  // 横向障碍物数量
    float horiSpeed;  // 横向障碍物速度
    int score;  // 当前分数
    RewardBlock rewardBlock; // 奖励方块
};

#endif
