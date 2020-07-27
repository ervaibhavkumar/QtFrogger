#include "banner.h"

Banner::Banner(QPixmap pixmap, QSize size, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
      label(pixmap),
      bannerSize(size)
{
    DisplayBanner();
}

void Banner::DisplayBanner() {
    setPixmap(label.scaled(bannerSize, Qt::KeepAspectRatio));
}

int Banner::getPixmapwidth() {
    return pixmap().width();
}
