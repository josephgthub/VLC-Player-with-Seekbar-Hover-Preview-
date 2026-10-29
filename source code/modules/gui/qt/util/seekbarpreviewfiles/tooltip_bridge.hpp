/*****************************************************************************
 * Copyright © 2026 VideoLAN
 *****************************************************************************/

#ifndef SEEKBAR_TOOLTIP_BRIDGE_H
#define SEEKBAR_TOOLTIP_BRIDGE_H

#include "qt.hpp"

#include <QWidget>
#include <QTimer>
#include <QEvent>
#include <QMouseEvent>

class QObject;
class TimeTooltip;
class SeekbarTimeTooltip;
class PreviewBox;

class TooltipBridge : public QWidget
{
    Q_OBJECT

public:
    explicit TooltipBridge( QWidget *parent, intf_thread_t *p_intf );
    ~TooltipBridge();

    void setTip( const QPoint& target, const QString& time, const QString& text );
    void show();
    void hide();
    void setMouseTracking( bool enable );
    void installEventFilter( QObject *filterObj );
    void setBarGeometry(const QPoint& barBottomLeft, const QPoint& barBottomRight);
    void setWindowRect(const QRect& rect);

    bool isActiveInstance( QObject *obj ) const;
    bool isCursorInHoverArea(const QPoint& cursorScreenPos, const QPoint& barBottomLeft, const QPoint& barBottomRight);

signals:
    void forwardMouseEvent(const QPoint& cursorPos);
    void forwardMouseClick(const QPoint& cursorPos);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void onHoverTimerTick();

private:
    bool useSeekbarPreview() const;

    TimeTooltip *mTimeTooltip;
    SeekbarTimeTooltip *mSeekbarTimeTooltip;
    PreviewBox *mPreviewBox;
    intf_thread_t *m_p_intf;
    
    QTimer* mHoverTimer;
    QPoint mBarBottomLeft;
    QPoint mBarBottomRight;
    QRect mWindowRect;
};

#endif // SEEKBAR_TOOLTIP_BRIDGE_H
