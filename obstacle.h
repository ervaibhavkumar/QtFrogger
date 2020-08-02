#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "player.h"

#include <QGraphicsPixmapItem>
#include <QTimer>

class Obstacle : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Obstacle(QString obstacle, QSize size, int speed, int interval, \
             QPoint point, QPoint minPoint, QGraphicsItem *parent = nullptr);
    int getObstacleSpeed();

public slots:
    void updatePos();

private:
    void createObstacle();
    void setupTimer();
    void checkCollisonWithPlayer();

    QString obstacleType;
    QSize obstacleSize;
    QPoint maxCoordinates;
    QPoint minCoordinates;
    Player *tempPlayer = nullptr;
    int obstacleSpeed;
    int timerInterval;
};

#endif // OBSTACLE_H
