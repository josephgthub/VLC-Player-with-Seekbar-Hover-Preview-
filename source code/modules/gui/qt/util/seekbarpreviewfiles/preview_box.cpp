#include "preview_box.hpp"
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QGuiApplication>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include "getframe.hpp"
#include "../../components/simple_preferences_seekbar.hpp"

PreviewBox::PreviewBox(QWidget *parent, intf_thread_t *p_intf)
    : QWidget(parent)
    , p_intf(p_intf)
{
    setWindowFlags( Qt::ToolTip | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint );
    setAttribute( Qt::WA_TranslucentBackground );
    
    QPixmap dummyFrame = getDummyFrame();
    if (!dummyFrame.isNull())
    {
        SeekbarPreviewPreferences prefs = loadSeekbarPreviewPreferences(p_intf);
        int boxWidth = prefs.boxSize;
        QPixmap scaledFrame = dummyFrame.scaledToWidth(boxWidth, Qt::SmoothTransformation);
        resize(boxWidth + 2 * (prefs.previewBorderWidth / 10.0), scaledFrame.height() + 2 * (prefs.previewBorderWidth / 10.0));
    }
}

void PreviewBox::setPosition(const QPoint &target, int tooltipTop, const QRect &windowRect)
{
    mTarget = target;
    mTooltipTop = tooltipTop;
    
    SeekbarPreviewPreferences prefs = loadSeekbarPreviewPreferences(p_intf);
    int boxWidth = prefs.boxSize;
    int borderWidth = prefs.previewBorderWidth / 10.0;
    int topMargin = prefs.topMargin / 4.0;
    
    QPixmap dummyFrame = getDummyFrame();
    if (!dummyFrame.isNull())
    {
        QPixmap scaledFrame = dummyFrame.scaledToWidth(boxWidth, Qt::SmoothTransformation);
        QSize size(boxWidth + 2 * borderWidth, scaledFrame.height() + 2 * borderWidth);
        
        resize(size);
        
        QPoint position(target.x() - size.width() / 2.0, tooltipTop - size.height() - topMargin);
        
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
        QRect screen;
        auto *screenAt = QGuiApplication::screenAt(target);
        if (screenAt != nullptr)
            screen = screenAt->geometry();
#else
        QRect screen = QApplication::desktop()->screenGeometry(target);
#endif
        
        qreal maxX = screen.left() + screen.width() - size.width();
        qreal maxY = screen.top() + screen.height() - size.height();
        
        // Use window bounds for horizontal clamping if in windowed mode
        if (windowRect.isValid())
        {
            maxX = windowRect.left() + windowRect.width() - size.width();
            position.setX(qMin(qMax(windowRect.left(), position.x()), static_cast<int>(maxX)));
        }
        else
        {
            position.setX(qMin(qMax(screen.left(), position.x()), static_cast<int>(maxX)));
        }
        
        // Always use screen bounds for vertical clamping
        position.setY(qMin(qMax(screen.top(), position.y()), static_cast<int>(maxY)));
        
        move(position);
    }
}

void PreviewBox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    SeekbarPreviewPreferences prefs = loadSeekbarPreviewPreferences(p_intf);
    int borderWidth = prefs.previewBorderWidth / 10.0;
    QColor borderColor = prefs.previewBorderColor.isValid() ? prefs.previewBorderColor : QColor("#131111");
    int borderRadius = prefs.previewBorderRadius / 10.0;
    
    QPainterPath path;
    path.addRoundedRect(rect().adjusted(borderWidth, borderWidth, -borderWidth, -borderWidth), borderRadius, borderRadius);
    
    painter.setPen(QPen(borderColor, borderWidth));
    painter.drawPath(path);
    
    QPixmap dummyFrame = getDummyFrame();
    if (!dummyFrame.isNull())
    {
        QPixmap scaledFrame = dummyFrame.scaledToWidth(prefs.boxSize, Qt::SmoothTransformation);
        QRect imageRect(rect().center() - scaledFrame.rect().center(), scaledFrame.size());
        painter.setClipPath(path);
        painter.drawPixmap(imageRect, scaledFrame);
    }
}