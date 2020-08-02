#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>

class Player: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player(QSize size, QPoint startPoint, QPoint minXY, QPoint maxXY, \
           int horizontalMove, int verticalMove, int maxLanes, QGraphicsItem *parent = nullptr);
    int getCurrentLane();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void resetPlayer();
    void setPlayerSpeed(int speed);
    int getPlayerSpeed();

public slots:
    void updatePos();

private:
    void createPlayer();
    QSize playerSize;
    QPoint initPos;
    QPoint minXY;
    QPoint maxXY;
    int currentLane;
    int maxLanes;
    int horizontalMovementOffset;
    int verticalMovementOffset;

    int playerSpeed;
};

#endif // PLAYER_H
