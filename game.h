#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>

class Game : public QGraphicsView
{
    Q_OBJECT;
public:
    Game(QSize sizeOfScreen, QGraphicsView *parent = nullptr);
    void Start();

private:
    void createLanes();
    void createBanners();
    void createObstacles(int numObstacles, QString obstacleType, QSize obstacleSize, \
                         int obstacleSpeed, int startTime, int startX, int startY, \
                         QPoint endPoint, QPoint startPoint, int difference);
    QSize screenSize;
};

#endif // GAME_H
