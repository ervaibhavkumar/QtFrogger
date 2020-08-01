#include "banner.h"

Banner::Banner(QPixmap pixmap, QSize size, Qt::AspectRatioMode aspectRatio, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
      label(pixmap),
      bannerSize(size),
      bannerAspectRatio(aspectRatio)
{
    DisplayBanner();
}

void Banner::DisplayBanner() {
    setPixmap(label.scaled(bannerSize, bannerAspectRatio));
}

int Banner::getPixmapwidth() {
    return pixmap().width();
}
