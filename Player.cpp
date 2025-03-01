#include "Player.h"
#include "Ground.h"

Player::Player(int windowWidth,int lifeCount)
    :lifeCount(lifeCount),
    x(580), y(700),
    windowWidth(windowWidth),
    gravity(0.6f),
    velocityX(0.0f),
    velocityY(0.0f),
    isJumping(false),
    groundY(700),
    invincible(false),//初始为非无敌状态
    invincibleEndTime(0)
{}  // 初始位置为新窗口的中下部

void Player::activateInvincibility() {//激活无敌状态，在被攻击或吃到奖励方块后触发
    invincible = true;
    invincibleEndTime = QDateTime::currentMSecsSinceEpoch() + 4000;  // 4秒后结束
}

bool Player::isInvincible() const {//布尔型，判断是否为无敌状态
    return invincible && (QDateTime::currentMSecsSinceEpoch() < invincibleEndTime);
}

void Player::draw(QPainter *painter) {
    if (isInvincible()) {
        painter->setBrush(Qt::black);  // 无敌状态下显示为黑色
    } else {
        painter->setBrush(Qt::blue);    // 正常状态下显示为蓝色
    }
    painter->drawRect(x, y, width, height);
}


void Player::move(int dx) {//将速度转化为每帧移动的距离
    velocityX = dx;
}

void Player::jump() {//跳跃函数，允许二段跳
    if (!isJumping) {
        velocityY = -13.0f;
        isJumping = true;
    }
    else{
        if (!doubleJumping) {
            velocityY = -13.0f;
            doubleJumping = true;
        }
    }
}



void Player::lifeDown(){//生命减少函数
    lifeCount--;
}

int Player::getLife(){
    return lifeCount;//实时获取生命值
}

void Player::update(const Ground *ground) {//角色状态更新函数（核心）
    int newX = x + velocityX;//横向移动
    int checkX = (velocityX > 0) ? x + width : x;//实时检测位置，根据速度方向选取相应的角，其中x代表左下角
    int groundHeight = ground->getHeightAt(checkX);//根据checkX确定当前障碍物是否允许跨越
    int currentHeight = ground->getHeightAt(x + width / 2);//以角色中心的高度为是否攀登的判定条件
    int heightDiff = currentHeight - groundHeight;//若角色当前高度超越障碍物，视为可攀登

    if (isJumping) {//跳跃状态下，对角色与突起的判定
        int playerBottom = y + height;//角色底部
        if (playerBottom < groundHeight) {
            x = newX;//若在空中，横向速度不受影响
        } else {
            //若接触，对双方高度进行判定，若无法攀登，则速度降为零
            if (heightDiff > height && velocityX != 0) {
                velocityX = 0.0f;
            }
        }
    } else {//地面状态下与突起的判定
        if (heightDiff > height && velocityX != 0) {
            newX=x;
            velocityX = 0.0f;
        } else {
            x = newX;
        }
    }

    //防止越界
    if (x < 0) x = 0;
    if (x + width > windowWidth) x = windowWidth - width;

    //水平运动的速度递减，当速度足够小时，速度减为0
    if (!isJumping || velocityX != 0) {
        if (velocityX > 0) velocityX -= 0.3f;
        else if (velocityX < 0) velocityX += 0.3f;
        if (std::abs(velocityX) < 0.5f) velocityX = 0.0f;
    }

    //下降过程模拟自由落体
    y += velocityY;
    velocityY += gravity;

    //落地判定，同时结束跳跃及二段跳状态
    if (y + height >= currentHeight) {
        y = currentHeight - height;
        velocityY = 0.0f;
        isJumping = false;
        doubleJumping=false;
    }
}
//角色与障碍物的接触判定
QRect Player::rect() const {
    return QRect(x, y, width, height);
}
