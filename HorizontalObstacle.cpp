#include "HorizontalObstacle.h"

HorizontalObstacle::HorizontalObstacle(int y, float speed) : x(-30), y(y), speed(speed) {}

void HorizontalObstacle::draw(QPainter *painter) {
    painter->setBrush(Qt::yellow);  // 用黄色区分横向障碍物
    painter->drawRect(x, y, width, height);//实时位置绘制
}

void HorizontalObstacle::moveRight() {
    x += speed;//横向移动速度
}

QRect HorizontalObstacle::rect() const {
    return QRect(x, y, width, height);//位置用于命中判定
}
