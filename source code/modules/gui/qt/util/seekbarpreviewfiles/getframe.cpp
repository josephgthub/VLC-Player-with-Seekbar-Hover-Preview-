#include "getframe.hpp"
#include <QPixmap>

QPixmap getDummyFrame()
{
    QString imagePath;
#ifdef Q_OS_WIN
    imagePath = "C:/users/joseph/Documents/Wallpaper.png";
#else
    imagePath = "/media/joseph/Storage/Documents/Wallpaper.png";
#endif
    
    QPixmap pixmap(imagePath);
    if (pixmap.isNull())
    {
        pixmap = QPixmap(300, 169);
        pixmap.fill(Qt::black);
    }
    
    return pixmap;
}