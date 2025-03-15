#include "HorizontalObstacle.h"

HorizontalObstacle::HorizontalObstacle(int y, float speed) : x(-30), y(y), speed(speed) {
    magicBall.load(":/magicBall.png");
}

void HorizontalObstacle::draw(QPainter *painter) {

    painter->drawImage(QRect(x, y, exWidth, exHeight),magicBall);//实时位置绘制
}

void HorizontalObstacle::moveRight() {
    x += speed;//横向移动速度
}

QRect HorizontalObstacle::rect() const {
    return QRect(x, y, width, height);//位置用于命中判定
}
