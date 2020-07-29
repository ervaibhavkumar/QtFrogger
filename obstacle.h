#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsPixmapItem>
#include <QTimer>

class Obstacle : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Obstacle(QString obstacle, QSize size, int speed, int interval, QPoint point, QPoint minPoint, QGraphicsItem *parent = nullptr);

public slots:
    void updatePos();

private:
    void createObstacle();
    void setupTimer();

    QString obstacleType;
    QSize obstacleSize;
    QPoint maxCoordinates;
    QPoint minCoordinates;
    int obstacleSpeed;
    int timerInterval;
};

#endif // OBSTACLE_H
