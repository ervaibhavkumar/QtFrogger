#ifndef GAME_H
#define GAME_H

#include "player.h"

#include <QGraphicsView>
#include <QKeyEvent>

class Game : public QGraphicsView
{
    Q_OBJECT;
public:
    Game(QSize sizeOfScreen, QGraphicsView *parent = nullptr);
    void Start();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void createLanesAndObstacles();
    void createBanners();
    void createPlayer(int startX, int startY, int moveX, int moveY);
    void createObstacles(int numObstacles, QString obstacleType, QSize obstacleSize, \
                         int obstacleSpeed, int startTime, int startX, int startY, \
                         QPoint endPoint, QPoint startPoint, int difference);
    QSize screenSize;
    Player *player;
};

#endif // GAME_H
