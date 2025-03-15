#ifndef HORIZONTALOBSTACLE_H
#define HORIZONTALOBSTACLE_H

#include <QRect>
#include <QPainter>
//横向障碍物主要通过速度的增加以提高难度
class HorizontalObstacle {
public:
    HorizontalObstacle(int y, float speed);
    void draw(QPainter *painter);//用于实时绘制
    void moveRight();//移动函数
    QRect rect() const;//碰撞检测

private:
    int x, y;
    float speed;//可进行难度递进
    const int exWidth=35;
    const int exHeight=35;
    static const int horiObstacleSize=25;//大小方便维护
    static const int width = horiObstacleSize;
    static const int height = horiObstacleSize;
    QImage magicBall;
};

#endif
