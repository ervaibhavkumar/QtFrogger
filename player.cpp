#include "player.h"

Player::Player(QSize size, QPoint minXY, QPoint maxXY, int horizontalMove, int verticalMove, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
      playerSize(size),
      minXY(minXY),
      maxXY(maxXY),
      horizontalMovementOffset(horizontalMove),
      verticalMovementOffset(verticalMove)
{
    currentLane = 1;
    createPlayer();
}

void Player::createPlayer() {
    QPixmap pixmap(":/images/player.png");
    setPixmap(pixmap.scaled(playerSize));
}

int Player::getCurrentLane() {
    return  currentLane;
}

void Player::moveUp() {
    if (y() - verticalMovementOffset >= minXY.y()) {
        setPos(x(), y() - verticalMovementOffset);
    }
}

void Player::moveDown() {
    if (y() + verticalMovementOffset <= maxXY.y()) {
        setPos(x(), y() + verticalMovementOffset);
    }
}

void Player::moveLeft() {
    if (x() - horizontalMovementOffset >= minXY.x()) {
        setPos(x() - horizontalMovementOffset, y());
    }
}

void Player::moveRight() {
    if (x() + horizontalMovementOffset <= maxXY.x()) {
        setPos(x() + horizontalMovementOffset, y());
    }
}


