#include "Obstacle.h"

Obstacle::Obstacle(QWidget *parent, int x, int y,int type) : x(x), y(y),type(type), parent(parent)
{
    chair.load(":/chair.png");
    table.load(":/table.png");
}

void Obstacle::draw(QPainter *painter) {

    painter->drawImage(QRect(x, y, exWidth, exHeight),type?chair:table);
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
