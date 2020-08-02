#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "obstacle.h"

#include <QGraphicsView>
#include <QKeyEvent>

class Game : public QGraphicsView
{
    Q_OBJECT;
public:
    Game(QSize sizeOfScreen, QGraphicsView *parent = nullptr);
    void Start();

public slots:
    void updatePos();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void createLanesAndObstacles();
    void createBackground(int numLanes, QString mapPath, QPoint startPoint, QSize size);
    void createBanners();
    void createPlayer(QPoint startPoint, int moveX, int moveY);
    void createObstacles(int numObstacles, QString obstacleType, QSize obstacleSize, \
                         int obstacleSpeed, int startTime, int startX, int startY, \
                         QPoint endPoint, QPoint startPoint, int difference);

    void collisonCheck();
    bool isStartOrPauseLane(int currentLane);
    void raiseQuestionPopup(QString message, QString title);

    QSize screenSize;
    Player *player;

    QTimer *playerTimer;
};

#endif // GAME_H
