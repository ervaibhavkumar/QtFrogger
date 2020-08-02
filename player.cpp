#include "player.h"
#include "audio.h"
#include "appdialog.h"

#include <QDebug>

Player::Player(QSize size, QPoint startPoint, QPoint minXY, QPoint maxXY, \
               int horizontalMove, int verticalMove, int maxLanes, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
      playerSize(size),
      initPos(startPoint),
      minXY(minXY),
      maxXY(maxXY),
      maxLanes(maxLanes),
      horizontalMovementOffset(horizontalMove),
      verticalMovementOffset(verticalMove)
{
    currentLane = 1;
    createPlayer();
}

void Player::createPlayer() {
    QPixmap pixmap(":/images/player.png");
    setPixmap(pixmap.scaled(playerSize));
    resetPlayer();
}

int Player::getCurrentLane() {
    return  currentLane;
}

void Player::moveUp() {
    if (y() - verticalMovementOffset >= minXY.y() && currentLane + 1 <= maxLanes) {
        setPos(x(), y() - verticalMovementOffset);
        currentLane++;
    }
}

void Player::moveDown() {
    if (y() + verticalMovementOffset <= maxXY.y() && currentLane - 1 > 0) {
        setPos(x(), y() + verticalMovementOffset);
        currentLane--;
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

void Player::resetPlayer() {
    currentLane = 1;
    setPos(initPos.x(), initPos.y());
}

void Player::setPlayerSpeed(int speed) {
    playerSpeed = speed;
}

int Player::getPlayerSpeed() {
    return playerSpeed;
}

void Player::updatePos() {
    setPos(x() - playerSpeed, y());
    if (x() < -15) {
        Audio::playSound("die");
        if (AppDialog::informationPopup("You died.", "No....", "Quit") == QMessageBox::Ok)
            QCoreApplication::quit();
    }
    else if (x() > maxXY.x() + 15) {
        Audio::playSound("die");
        if (AppDialog::informationPopup("You died.", "No....", "Quit") == QMessageBox::Ok)
            QCoreApplication::quit();
    }
}

