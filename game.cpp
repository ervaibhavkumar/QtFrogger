#include "game.h"
#include "banner.h"
#include "obstacle.h"
#include "player.h"
#include "config.h"

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
    setWindowTitle("QT Frogger");
}

void Game::Start() {
    scene()->clear();
    createBanners();
    createLanesAndObstacles();
    return;
}

void Game::createLanesAndObstacles() {
    int bannerHeight = screenSize.height() / numLanes;
    int bannerWidth = screenSize.width();

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

    Banner *finish = new Banner(QPixmap(":/images/finish.png"), QSize(bannerWidth, bannerHeight));
    finish->setPos((screenSize.width() - finish->getPixmapwidth()) / 2, 0);
    scene()->addItem(finish);

    Banner *pause = new Banner(QPixmap(":/images/pause.png"), QSize(bannerWidth, bannerHeight));
    pause->setPos((screenSize.width() - pause->getPixmapwidth()) / 2, 5 * bannerHeight);
    scene()->addItem(pause);

    Banner *start = new Banner(QPixmap(":/images/start.png"), QSize(bannerWidth, bannerHeight));
    start->setPos((screenSize.width() - start->getPixmapwidth()) / 2, 10 * bannerHeight);
    scene()->addItem(start);

    createPlayer((screenSize.width() - start->getPixmapwidth()) / 2 - 140, 10 * bannerHeight, 100, bannerHeight);
}

void Game::createPlayer(int startX, int startY, int moveX, int moveY) {
    player = new Player(playerSize, QPoint(-moveX + 55,-moveY + 50), \
                        QPoint(screenSize.width() + moveX - 55, screenSize.height() + moveY - 50), moveX, moveY);
    player->setPos(startX, startY);
    scene()->addItem(player);
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

void Game::keyPressEvent(QKeyEvent *event) {
    if (player == nullptr) return;

    switch (event->key()) {
        case Qt::Key_Up : {
            player->moveUp();
            break;
        }
        case Qt::Key_Down: {
            player->moveDown();
            break;
        }
        case Qt::Key_Left: {
            player->moveLeft();
            break;
        }
        case Qt::Key_Right: {
            player->moveRight();
            break;
        }
    }
}
