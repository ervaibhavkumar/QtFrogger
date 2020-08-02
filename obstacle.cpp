#include "obstacle.h"
#include "player.h"
#include "audio.h"
#include "appdialog.h"

#include <QDebug>

Obstacle::Obstacle(QString obstacle, QSize size, int speed, int interval, \
                   QPoint point, QPoint minPoint, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
      obstacleType(obstacle),
      obstacleSize(size),
      maxCoordinates(point),
      minCoordinates(minPoint),
      obstacleSpeed(speed),
      timerInterval(interval)
{
    createObstacle();
}

void Obstacle::createObstacle() {
    if (obstacleType == "TRUCK") {
        QPixmap *pixmap;
        if (obstacleSpeed < 0) {
            pixmap = new QPixmap(":/images/truck_right.png");
        }
        else {
            pixmap = new QPixmap(":/images/truck_left.png");
        }
        setPixmap(pixmap->scaled(obstacleSize));
    }
    else {
        Q_ASSERT(obstacleType == "BOAT");
        QPixmap *pixmap;
        if (obstacleSpeed < 0) {
            pixmap = new QPixmap(":/images/boat_right.png");
        }
        else {
            pixmap = new QPixmap(":/images/boat_left.png");
        }
        setPixmap(pixmap->scaled(obstacleSize));
    }
    setupTimer();
}

void Obstacle::updatePos() {
    setPos(x() - obstacleSpeed, y());
    checkCollisonWithPlayer();
    if (x() < -15) {
        setPos(maxCoordinates.x(), maxCoordinates.y());
    }
    else if (x() > maxCoordinates.x() + 15) {
        setPos(minCoordinates.x(), minCoordinates.y());
    }
}


void Obstacle::setupTimer() {
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePos()));
    timer->start(timerInterval);
}

void Obstacle::checkCollisonWithPlayer() {
    if (obstacleType != "BOAT") {
        for (auto const item : collidingItems()) {
            Player* player = dynamic_cast<Player*>(item);
            if (player != nullptr) {
                player->resetPlayer();
                Audio::playSound("die");
                if (AppDialog::informationPopup("You died.", "No....", "Quit") == QMessageBox::Ok)
                    QCoreApplication::quit();
            }
        }
    }
}

int Obstacle::getObstacleSpeed() {
    return  obstacleSpeed;
}
