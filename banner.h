#ifndef BANNER_H
#define BANNER_H

#include <QGraphicsPixmapItem>

class Banner: public QGraphicsPixmapItem
{
public:
    Banner(QPixmap pixmap, QSize size, QGraphicsItem *parent = nullptr);
    int getPixmapwidth();

private:
    void DisplayBanner();

    QPixmap label;
    QSize bannerSize;
};

#endif // BANNER_H
