#ifndef PLAYER_H
#define PLAYER_H

#include <QRect>
#include <QPainter>
#include <QDateTime>
#include <QTimer>

class Ground;

class Player {
public:
    Player(int windowWidth,int lifeCount);//用于确定初始位置
    void draw(QPainter *painter);//进行实时绘制
    void move(int dx);//移动函数
    void jump();//跳跃函数

    void update(const Ground *ground);//角色状态更新函数
    QRect rect() const;//碰撞检测函数
    QRect rectWithRewardBlock() const;
    void lifeDown();//生命下降函数
    int getLife();//获取实时生命值
    void activateInvincibility();  // 激活无敌状态
    bool isInvincible() const;     // 判断是否处于无敌状态
    void scoreSkill(int& score);
    void faceSideChange();
    void startGlide();
    void stopGlide();
    void checkGlide();
    void addGlideEnergy();
    int getEnergy();

private:
    bool faceSide;
    int lifeCount;
    int x, y;
    int windowWidth;
    float gravity;
    float velocityX;
    float velocityY;
    bool isJumping;
    bool doubleJumping;
    int groundY;  // 默认地面高度
    bool isGliding;
    QImage playerImage1;
    QImage playerImage0;
    QImage glideImage;
    static const int width = 50;//玩家外观大小
    static const int height = 50;
    static const int realWidth = 4;//玩家实际碰撞体积
    static const int realHeight = 4;
    bool invincible;          // 是否处于无敌状态
    qint64 invincibleEndTime; // 无敌状态结束时间
    QTimer *glideTimer;
    bool checkKeyPressed;
    float glideEnergy; // 滑翔能量
    static const float maxGlideEnergy;
    static const float glideEnergyConsumption;
};

#endif
