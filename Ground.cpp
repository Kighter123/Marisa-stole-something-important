#include "Ground.h"
#include <QRandomGenerator>

Ground::Ground(int windowWidth, int windowHeight) ://初始化窗口尺寸并生成随机突起
    windowWidth(windowWidth), windowHeight(windowHeight) {
    generateBumps();
    groundImage.load(":/wood.png");


}

void Ground::draw(QPainter *painter) {

    painter->drawImage(QRect(0, windowHeight - 10, windowWidth, 10),groundImage);//绘制底部，高度10像素
    for (const QRect &bump : bumps) {
        painter->drawImage(QRect(bump),groundImage);
    }
}

int Ground::getHeightAt(int x) const {
    //根据x坐标检测位置，检测突起的高度，用于检测与player的碰撞
    for (const QRect &bump : bumps) {
        //根据x检测是否突起，返回相应高度
        if (x >= bump.left() && x <= bump.right()) {
            return bump.top();
        }
    }
    return windowHeight - 10;
}

//生成随机突起
void Ground::generateBumps() {
    bumps.clear();
    int x = 0;
    while (x < windowWidth) {
        //障碍物随机长宽
        int bumpWidth = QRandomGenerator::global()->bounded(50, 150);
        int bumpHeight = QRandomGenerator::global()->bounded(20, 100);
        if (x + bumpWidth > windowWidth) bumpWidth = windowWidth - x;//检测边界情况
        bumps.append(QRect(x, windowHeight - 10 - bumpHeight, bumpWidth, bumpHeight));//在底边上添加突起
        x += bumpWidth + QRandomGenerator::global()->bounded(50, 100);
    }
}
