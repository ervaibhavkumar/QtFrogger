#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>

class Player: public QGraphicsPixmapItem
{
public:
    Player(QSize size, QPoint minXY, QPoint maxXY, int horizontalMove, int verticalMove, QGraphicsItem *parent = nullptr);
    int getCurrentLane();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

private:
    void createPlayer();
    QSize playerSize;
    QPoint minXY;
    QPoint maxXY;
    int currentLane;
    int horizontalMovementOffset;
    int verticalMovementOffset;
};

#endif // PLAYER_H
