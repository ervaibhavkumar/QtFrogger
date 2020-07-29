#include "game.h"
#include "banner.h"
#include "obstacle.h"
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
    createBanners();
    createLanes();
    return;
}

void Game::createLanes() {
//    int height = screenSize.height();
//    int width = screenSize.width();
//    Banner *start = new Banner(QPixmap(":/images/start.png"), QSize(width, height / 18));
//    start->setPos(0, 80);
//    start->setFocus();
//    scene()->addItem(start);
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

    // Small size Boats
    QSize *smallObstacles = new QSize(70,bannerHeight);
    createObstacles(3, "BOAT", *smallObstacles, 32, \
                    100, screenSize.width(), bannerHeight, QPoint(screenSize.width(), bannerHeight), \
                    QPoint(0, bannerHeight), 200);

    // Large Boats
    QSize *largeObstacles = new QSize(210,bannerHeight);
    createObstacles(2, "BOAT", *largeObstacles, -40, \
                    100, 0, 2 * bannerHeight, QPoint(screenSize.width(), 2 * bannerHeight), \
                    QPoint(0, 2 * bannerHeight), -400);

    // Small size slow Boats
    QSize *smallSlowObstacles = new QSize(70,bannerHeight);
    createObstacles(4, "BOAT", *smallSlowObstacles, 25, \
                    100, screenSize.width(), 3 * bannerHeight, QPoint(screenSize.width(), 3 * bannerHeight), \
                    QPoint(0, 3 * bannerHeight), 250);

    // Medium Boats
    QSize *mediumObstacles = new QSize(90,bannerHeight);
    createObstacles(3, "BOAT", *mediumObstacles, -30, \
                    100, 0,  4 * bannerHeight, QPoint(screenSize.width(), 4 * bannerHeight), \
                    QPoint(0, 4 * bannerHeight), -315);
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
