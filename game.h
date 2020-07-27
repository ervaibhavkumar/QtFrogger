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
    QSize screenSize;
};

#endif // GAME_H
