#include "game.h"
#include "banner.h"
#include "obstacle.h"
#include "player.h"
#include "config.h"
#include "audio.h"
#include "appdialog.h"

#include <QGraphicsScene>
#include <QDebug>

Game::Game(QSize sizeoFScreen, QGraphicsView *parent)
    : QGraphicsView(parent),
      screenSize(sizeoFScreen)
{
    QGraphicsScene *scene = new QGraphicsScene();
    setScene(scene);

    scene->setSceneRect(0,0,screenSize.width(),screenSize.height());
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWindowTitle("QT Frogger");}

void Game::Start() {
    scene()->clear();
    createBanners();
    createLanesAndObstacles();
    return;
}

void Game::createLanesAndObstacles() {
    int bannerHeight = screenSize.height() / numLanes;
    int bannerWidth = screenSize.width();

    // create ocean background
    createBackground(1, ":/images/ocean.jpg", QPoint(0, bannerHeight), QSize(screenSize.width(), 4 * bannerHeight));

    // Small size Boats
    QSize *smallObstacles = new QSize(70,bannerHeight);
    createObstacles(3, "BOAT", *smallObstacles, 32, \
                    100, screenSize.width() - 700, bannerHeight, QPoint(screenSize.width(), bannerHeight), \
                    QPoint(0, bannerHeight), 200);

    // Large Boats
    QSize *largeObstacles = new QSize(210,bannerHeight);
    createObstacles(2, "BOAT", *largeObstacles, -40, \
                    100, 0 + 300, 2 * bannerHeight, QPoint(screenSize.width(), 2 * bannerHeight), \
                    QPoint(0, 2 * bannerHeight), -400);

    // Small size slow Boats
    QSize *smallSlowObstacles = new QSize(70,bannerHeight);
    createObstacles(4, "BOAT", *smallSlowObstacles, 25, \
                    100, screenSize.width() - 250, 3 * bannerHeight, QPoint(screenSize.width(), 3 * bannerHeight), \
                    QPoint(0, 3 * bannerHeight), 250);

    // Medium Boats
    QSize *mediumObstacles = new QSize(110,bannerHeight);
    createObstacles(3, "BOAT", *mediumObstacles, -30, \
                    100, 0,  4 * bannerHeight, QPoint(screenSize.width(), 4 * bannerHeight), \
                    QPoint(0, 4 * bannerHeight), -315);

    // create road background
    createBackground(4, ":/images/road.png", QPoint(0, 6 * bannerHeight), QSize(screenSize.width(), bannerHeight));

    // Small size Trucks
    QSize *smallTrucks = new QSize(140,bannerHeight);
    createObstacles(3, "TRUCK", *smallTrucks, 32, \
                    100, screenSize.width() - 300, 6 * bannerHeight, QPoint(screenSize.width(), 6 * bannerHeight), \
                    QPoint(0, 6 * bannerHeight), 200);

    // Large Trucks
    QSize *largeTrucks = new QSize(210,bannerHeight);
    createObstacles(2, "TRUCK", *largeTrucks, -40, \
                    100, 0, 7 * bannerHeight, QPoint(screenSize.width(), 7 * bannerHeight), \
                    QPoint(0, 7 * bannerHeight), -400);

    // Small size slow Trucks
    QSize *smallSlowTrucks = new QSize(140,bannerHeight);
    createObstacles(4, "TRUCK", *smallSlowTrucks, 25, \
                    100, screenSize.width() - 900, 8 * bannerHeight, QPoint(screenSize.width(), 8 * bannerHeight), \
                    QPoint(0, 8 * bannerHeight), 250);

    // Medium Trucks
    QSize *mediumTrucks = new QSize(120,bannerHeight);
    createObstacles(3, "TRUCK", *mediumTrucks, -30, \
                    100, 0 + 600,  9 * bannerHeight, QPoint(screenSize.width(), 9 * bannerHeight), \
                    QPoint(0, 9 * bannerHeight), -315);

}

void Game::createBanners() {
    int bannerHeight = screenSize.height() / numLanes;
    int bannerWidth = screenSize.width();

    // create finish background
    createBackground(1, ":/images/raceBg.png", QPoint(0, 0), QSize(screenSize.width(), bannerHeight));

    Banner *finish = new Banner(QPixmap(":/images/finish.png"), QSize(bannerWidth, bannerHeight));
    finish->setPos((screenSize.width() - finish->getPixmapwidth()) / 2, 0);
    scene()->addItem(finish);

    // create pause background
    createBackground(1, ":/images/pauseBg.jpeg", QPoint(0, 5 * bannerHeight), \
                     QSize(screenSize.width(), bannerHeight));

    Banner *pause = new Banner(QPixmap(":/images/pause.png"), QSize(bannerWidth, bannerHeight));
    pause->setPos((screenSize.width() - pause->getPixmapwidth()) / 2, 5 * bannerHeight);
    scene()->addItem(pause);

    // create start background
    int remainingScreenHeight = screenSize.height() - (bannerHeight * numLanes) ;
    createBackground(1, ":/images/raceBg.png", QPoint(0, 10 * bannerHeight), \
                     QSize(screenSize.width(), bannerHeight + remainingScreenHeight));

    Banner *start = new Banner(QPixmap(":/images/start.png"), QSize(bannerWidth, bannerHeight));
    start->setPos((screenSize.width() - start->getPixmapwidth()) / 2, 10 * bannerHeight);
    scene()->addItem(start);

    createPlayer(QPoint((screenSize.width() - start->getPixmapwidth()) / 2 - 140, 10 * bannerHeight), \
                 100, bannerHeight);
}

void Game::createPlayer(QPoint startPoint, int moveX, int moveY) {
    player = new Player(playerSize, startPoint, QPoint(-moveX + 55,-moveY + 50), \
                        QPoint(screenSize.width() + moveX - 55, screenSize.height() + moveY - 50), \
                        moveX, moveY, numLanes);
    player->setZValue(1);
    scene()->addItem(player);

    playerTimer = new QTimer(this);
    connect(playerTimer, SIGNAL(timeout()), this, SLOT(updatePos()));
//    playerTimer->start(100);
//    playerTimer->stop();
}

void Game::updatePos() {
    player->updatePos();
    qDebug() << player->getPlayerSpeed();
}

void Game::createObstacles(int numObstacles, QString obstacleType, QSize obstacleSize, \
                           int obstacleSpeed, int startTime , int startX, int startY, \
                           QPoint endPoint, QPoint startPoint, int difference) {
    for (auto i = 0; i < numObstacles; i++) {
        Obstacle *boat = new Obstacle(obstacleType, obstacleSize, obstacleSpeed, startTime, endPoint, startPoint);
        boat->setPos(startX - ((i + 1) * difference), startY);
        scene()->addItem(boat);
    }
}

void Game::raiseQuestionPopup(QString message, QString title) {
    if (AppDialog::questionPopup(message, title, "Restart Game", "Quit Game") == QMessageBox::Yes) {
        Start();
    }
    else {
        QApplication::quit();
    }
}

void Game::keyPressEvent(QKeyEvent *event) {
    if (player == nullptr) return;

    switch (event->key()) {
        case Qt::Key_Up : {
            player->moveUp();
            collisonCheck();
            break;
        }
        case Qt::Key_Down: {
            player->moveDown();
            collisonCheck();
            break;
        }
        case Qt::Key_Left: {
            player->moveLeft();
            collisonCheck();
            break;
        }
        case Qt::Key_Right: {
            player->moveRight();
            collisonCheck();
            break;
        }
    }
}

void Game::collisonCheck() {
    playerTimer->stop();
    int playerCurrentLane = player->getCurrentLane();
    // skip the "Start" and "Pause" lane
    if (!isStartOrPauseLane(playerCurrentLane)) {
        if (playerCurrentLane == numLanes) {
            // player won
            playerTimer->stop();
            Audio::playSound("success");
            raiseQuestionPopup("YOU WON", "Hurayyy...");
        }
        else {
            if (playerCurrentLane >=2 && playerCurrentLane <= 5) {
                // road lanes
                for (auto const item : player->collidingItems()) {
                    Obstacle* truck = dynamic_cast<Obstacle*>(item);
                    if (truck != nullptr) {
                        playerTimer->stop();
                        Audio::playSound("die");
                        if (AppDialog::informationPopup("You died.", "No....", "Quit") == QMessageBox::Ok)
                            QCoreApplication::quit();
                    }
                }
            }
            else if (playerCurrentLane >= 7 && playerCurrentLane <= 10) {
                // ocean lanes
                QList<QGraphicsItem*> collison = player->collidingItems();
                for(int k = 0; k < (collison.size()/2); k++) collison.swap(k,collison.size()-(1+k));
                for (auto const item : collison) {
                    Obstacle* boat = dynamic_cast<Obstacle*>(item);
                    if (boat != nullptr) {
                        // move player with boat
                        player->setPlayerSpeed(boat->getObstacleSpeed());
                        playerTimer->start(100);
                        return;
                    }
                }
                // not landed on boat
                playerTimer->stop();
                Audio::playSound("die");
                if (AppDialog::informationPopup("You died.", "No....", "Quit") == QMessageBox::Ok)
                    QCoreApplication::quit();
            }
        }
    }
}

bool Game::isStartOrPauseLane(int currentLane) {
    return (currentLane == 1 || currentLane == 6);
}

void Game::createBackground(int numLanes, QString mapPath, QPoint startPoint, QSize size) {
    for (auto i = 0; i< numLanes; i ++) {
        Banner *bg = new Banner(QPixmap(mapPath), size, Qt::IgnoreAspectRatio);
        bg->setPos(startPoint.x(), startPoint.y() + (i * size.height()));
        scene()->addItem(bg);
    }
}
