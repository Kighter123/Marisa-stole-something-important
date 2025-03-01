#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QRect>
#include <QPainter>
//顶部障碍物的难度递增体现在数量的增加
class Obstacle {
public:
    Obstacle(QWidget *parent, int x, int y);
    void draw(QPainter *painter);
    void moveDown();
    void setX(int x);//位置改变
    void setY(int y);//位置改变
    int gety() const;//y位置监听
    QRect rect() const;//碰撞检测


private:
    int x,y;//用y与上方重复，于是使用yi
    QWidget *parent;
    static const int ObstacleSize=30;//大小方便维护调整
    static const int width =ObstacleSize;
    static const int height = ObstacleSize;
};

#endif
