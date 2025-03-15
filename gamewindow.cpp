#include "GameWindow.h"
#include <QPainter>
#include <QRandomGenerator>



GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent),
    elapsedTime(0.0f),//初始时间，可循环，用于难度递进
    obstacleCount(5),//初始顶部障碍物记录总数量，用于障碍物上限构造
    horiObstacleCount(0),//初始侧面障碍物
    horiSpeed(1.0f),//初始横向障碍物速度
    score(0),//初始分数
    rewardBlockCount(0),
    rewardBlock(1200, 800),//奖励函数初始状态
    spacebarPressed(false)

{
    library.load(":/Library.jpg");
    setFixedSize(1200, 800);//窗口大小
    player = new Player(1200,3);
    ground = new Ground(1200, 800);
    timer = new QTimer(this);


    //每过一个timer，发出一个超时信号，用于实时检测画面整体信息并进行检测与绘制
    connect(timer, &QTimer::timeout, this, &GameWindow::updateGame);
    timer->start(pertime);  // ~70 FPS


    scoreTimer = new QTimer(this);
    connect(scoreTimer, &QTimer::timeout, this, &GameWindow::updateScore);
    scoreTimer->start(1000);  // 每1秒触发一次


    spacebarTimer = new QTimer(this);
    connect(spacebarTimer, &QTimer::timeout, this, &GameWindow::checkSpacebarLongPress);

    // 初始顶部障碍物
    for (int i = 0; i < obstacleCount; ++i) {
        obstacles.append(new Obstacle(this, QRandomGenerator::global()->bounded(1000),
        -50 - i * 200,QRandomGenerator::global()->bounded(2)));
    }
}
//结束时释放全部内存，包括角色，地面，顶部障碍物，侧面障碍物
GameWindow::~GameWindow() {
    delete player;
    delete ground;
    qDeleteAll(obstacles);
    qDeleteAll(horiObstacles);
}

void GameWindow::updateScore() {
    score += 5;  // 每1秒增加5分
    update();    // 触发重绘以更新分数显示
}
void GameWindow::paintEvent(QPaintEvent *event) {

    //窗口初始化绘制
    QPainter painter(this);

    //绘制背景
    painter.drawImage(0, 0, library.scaled(width(), height()));

    ground->draw(&painter);
    player->draw(&painter);

    //绘制初始障碍物
    for (Obstacle *obs : obstacles) {
        obs->draw(&painter);
    }
    for (HorizontalObstacle *horiObs : horiObstacles) {
        horiObs->draw(&painter);
    }

    // 绘制奖励方块
    rewardBlock.draw(&painter);

    // 绘制分数
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 24));
    painter.drawText(100, 50, QString("分数: %1").arg(score));
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 24));
    painter.drawText(100, 100, QString("生命值: %1").arg(player->getLife()));
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 24));
    painter.drawText(100, 150, QString("魔法书: %1").arg(rewardBlockCount));
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 24));
    painter.drawText(100, 200, QString("滑翔能量: %1").arg(player->getEnergy()));
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    //检测键盘
    if (event->key() == Qt::Key_Left) {
        player->move(-6.0f);//左
    } else if (event->key() == Qt::Key_Right) {
        player->move(6.0f);//右
    } else if (event->key() == Qt::Key_Space) {
        if (!spacebarPressed) {
            spacebarPressed = true;
            spacebarTimer->start(150); // 开始计时
            player->jump(); // 先进行跳跃
        }
    } else if (event->key() == Qt::Key_Z) {
        player->scoreSkill(GameWindow::score);//主动触发无敌状态
    }
}

void GameWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        spacebarPressed = false;
        spacebarTimer->stop(); // 停止计时
        player->stopGlide(); // 停止滑翔
    }
}

void GameWindow::checkSpacebarLongPress() {
    if (spacebarPressed) {
        player->startGlide(); // 开始滑翔
    }
}

void GameWindow::updateGame() {
    elapsedTime += 0.014f;  // 每帧 ~14ms，累计时间（秒）

    // 随时间增加顶部障碍物
    if (elapsedTime >= 3.0f && obstacleCount < 120) {  // 画面中上限 120 个
        //基于随机的x，并预留一定的y，
        obstacles.append(new Obstacle(this, QRandomGenerator::global()->bounded(1200), -30,QRandomGenerator::global()->bounded(2)));
        obstacleCount++;
        elapsedTime = 0.0f;  // 重置计时器
    }

    // 随时间增加横向障碍物
    static float horiTimer = 0.0f;
    horiTimer += 0.014f;
    if (horiTimer >= 1.5f && horiObstacleCount < 5) {  //画面中上限5个，也许达不到？
        int y = QRandomGenerator::global()->bounded(400, 700);  // 在地面以上随机高度
        //对于y进行增加
        horiSpeed=QRandomGenerator::global()->bounded(2,7);//横向障碍物速度随机
        horiObstacles.append(new HorizontalObstacle(y, horiSpeed));
        horiObstacleCount++;

        horiTimer = 0.0f;  // 重置计时器
    }

    // 每6秒生成一个奖励方块
    static float rewardTimer = 0.0f;
    rewardTimer += 0.016f;
    if (rewardTimer >= 6.0f && !rewardBlock.isActive()) {
        rewardBlock.reset();  // 重置奖励方块
        rewardTimer = 0.0f;   // 重置计时器
    }

    // 更新玩家
    player->update(ground);



    // 更新顶部障碍物状态
    for (Obstacle *obs : obstacles) {
        obs->moveDown();//祥子，移动！
        if (obs->gety() > height()) {
            obs->setY(-30);//对障碍物进行重置，用于监听障碍物数量，同时防止内存溢出，
            obs->setX(QRandomGenerator::global()->bounded(1200));//随机横坐标
        }
        //与角色的碰撞判定
        if (!player->isInvincible() && player->rect().intersects(obs->rect())) {
            player->lifeDown();
            player->activateInvincibility();
        }
    }

    // 更新横向障碍物状态，使用数组
    for (int i = 0; i < horiObstacles.size(); ++i) {
        horiObstacles[i]->moveRight();//祥子，移动！
        if (horiObstacles[i]->rect().x() > 1200) {
            delete horiObstacles[i];//即过即消
            horiObstacles.removeAt(i--);
            horiObstacleCount--;
        }
        //与角色的碰撞判定
        else if (!player->isInvincible() && player->rect().intersects(horiObstacles[i]->rect())) {
            player->lifeDown();
            player->activateInvincibility();
        }
    }

    // 检测玩家与奖励方块的碰撞
    if (rewardBlock.checkCollision(player->rectWithRewardBlock())) {
        score += 50;  // 增加50分
        rewardBlockCount++;
        player->activateInvincibility();
        player->addGlideEnergy();
        update();     // 触发重绘

    }

    //GAME OVER
    if(player->getLife()==0){
        timer->stop();
        scoreTimer->stop();
    }

    update();
}
