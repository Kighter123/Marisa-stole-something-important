#include "Obstacle.h"

Obstacle::Obstacle(QWidget *parent, int x, int y) : x(x), y(y), parent(parent) {}

void Obstacle::draw(QPainter *painter) {
    painter->setBrush(Qt::red);
    painter->drawRect(x, y, width, height);
}

void Obstacle::moveDown() {
    y += 4.0f; // 向下移动速度
}

void Obstacle::setX(int x) {
    this->x = x;
}

void Obstacle::setY(int y) {
    this->y = y;
}

int Obstacle::gety() const {
    return y;
}

QRect Obstacle::rect() const {
    return QRect(x, y, width, height);//位置用于命中判定
}
