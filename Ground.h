#ifndef GROUND_H
#define GROUND_H

#include <QVector>
#include <QRect>
#include <QPainter>

//游戏中的静态地面类，有地面直线与随机矩形突起
class Ground {
public:
    Ground(int windowWidth, int windowHeight);//获取窗口高度与长度
    void draw(QPainter *painter);//绘制地面
    int getHeightAt(int x) const;  // 获取某点的地面高度

private:
    int windowWidth;
    int windowHeight;
    QVector<QRect> bumps;  // 矩形突起列表
    void generateBumps();//生成随机矩形突起
};

#endif
