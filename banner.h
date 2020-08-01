#ifndef BANNER_H
#define BANNER_H

#include <QGraphicsPixmapItem>

class Banner: public QGraphicsPixmapItem
{
public:
    Banner(QPixmap pixmap, QSize size, \
           Qt::AspectRatioMode aspectRatio = Qt::KeepAspectRatio, QGraphicsItem *parent = nullptr);
    int getPixmapwidth();

private:
    void DisplayBanner();

    QPixmap label;
    QSize bannerSize;
    Qt::AspectRatioMode bannerAspectRatio;
};

#endif // BANNER_H
