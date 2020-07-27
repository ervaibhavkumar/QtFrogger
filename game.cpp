#include "game.h"
#include "banner.h"
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
    pause->setPos((screenSize.width() - pause->getPixmapwidth()) / 2, 4 * bannerHeight);
    scene()->addItem(pause);

    Banner *start = new Banner(QPixmap(":/images/start.png"), QSize(bannerWidth, bannerHeight));
    start->setPos((screenSize.width() - start->getPixmapwidth()) / 2, 8 * bannerHeight);
    scene()->addItem(start);
}
