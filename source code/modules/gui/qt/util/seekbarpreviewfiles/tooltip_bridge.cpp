/*****************************************************************************
 * Copyright © 2026 VideoLAN
 *****************************************************************************/

#include "tooltip_bridge.hpp"

#include "../timetooltip.hpp"
#include "seekbar_time_tooltip.hpp"
#include "preview_box.hpp"
#include "../../components/simple_preferences_seekbar.hpp"
#include <QDebug>

TooltipBridge::TooltipBridge( QWidget *parent, intf_thread_t *p_intf )
    : QWidget( parent )
    , mTimeTooltip( new TimeTooltip( parent ) )
    , mSeekbarTimeTooltip( new SeekbarTimeTooltip( parent, p_intf ) )
    , mPreviewBox( new PreviewBox( parent, p_intf ) )
    , m_p_intf( p_intf )
    , mHoverTimer( new QTimer( this ) )
{
    mTimeTooltip->hide();
    mSeekbarTimeTooltip->hide();
    mPreviewBox->hide();
    
    mHoverTimer->setInterval( 20 );
    connect( mHoverTimer, &QTimer::timeout, this, &TooltipBridge::onHoverTimerTick );
    
    // Install event filters to detect clicks on tooltip widgets
    mTimeTooltip->installEventFilter( this );
    mSeekbarTimeTooltip->installEventFilter( this );
    mPreviewBox->installEventFilter( this );
    
    mWindowRect = QRect(); // Initialize as invalid
}

TooltipBridge::~TooltipBridge()
{
    mHoverTimer->stop();
    delete mTimeTooltip;
    delete mSeekbarTimeTooltip;
    delete mPreviewBox;
}

bool TooltipBridge::useSeekbarPreview() const
{
    if( m_p_intf == nullptr )
        return false;

    SeekbarPreviewPreferences prefs = loadSeekbarPreviewPreferences( m_p_intf );
    return prefs.enableSeekbarPreview;
}

void TooltipBridge::setTip( const QPoint& target, const QString& time, const QString& text )
{
    if( useSeekbarPreview() )
    {
        mTimeTooltip->hide();
        mSeekbarTimeTooltip->setTip( target, time, text );
        mPreviewBox->setPosition(target, mSeekbarTimeTooltip->y(), mWindowRect);
    }
    else
    {
        mSeekbarTimeTooltip->hide();
        mPreviewBox->hide();
        mTimeTooltip->setTip( target, time, text );
    }
}

void TooltipBridge::show()
{
    if( useSeekbarPreview() )
    {
        mSeekbarTimeTooltip->show();
        mPreviewBox->show();
        
        SeekbarPreviewPreferences prefs = loadSeekbarPreviewPreferences( m_p_intf );
        if( prefs.interactivePreview )
        {
            mHoverTimer->start();
        }
    }
    else
    {
        mTimeTooltip->show();
    }
}

void TooltipBridge::hide()
{
    mHoverTimer->stop();
    mTimeTooltip->hide();
    mSeekbarTimeTooltip->hide();
    mPreviewBox->hide();
}

void TooltipBridge::setMouseTracking( bool enable )
{
    mTimeTooltip->setMouseTracking( enable );
    mSeekbarTimeTooltip->setMouseTracking( enable );
}

void TooltipBridge::installEventFilter( QObject *filterObj )
{
    mTimeTooltip->installEventFilter( filterObj );
    mSeekbarTimeTooltip->installEventFilter( filterObj );
}

void TooltipBridge::setBarGeometry(const QPoint& barBottomLeft, const QPoint& barBottomRight)
{
    mBarBottomLeft = barBottomLeft;
    mBarBottomRight = barBottomRight;
}

void TooltipBridge::setWindowRect(const QRect& rect)
{
    mWindowRect = rect;
}

bool TooltipBridge::isActiveInstance( QObject *obj ) const
{
    if( useSeekbarPreview() )
        return obj == mSeekbarTimeTooltip;

    return obj == mTimeTooltip;
}

void TooltipBridge::onHoverTimerTick()
{
    QPoint cursorPos = QCursor::pos();
    
    if( isCursorInHoverArea( cursorPos, mBarBottomLeft, mBarBottomRight ) )
    {
        // Cursor is still in hover area, keep tooltip visible
        // Emit signal to forward mouse event to slider
        emit forwardMouseEvent(cursorPos);
        return;
    }
    else
    {
        // Cursor has left hover area, hide tooltip
        hide();
    }
}

bool TooltipBridge::isCursorInHoverArea(const QPoint& cursorScreenPos, const QPoint& barBottomLeft, const QPoint& barBottomRight)
{
    if( !useSeekbarPreview() )
        return false;

    SeekbarPreviewPreferences prefs = loadSeekbarPreviewPreferences( m_p_intf );
    if( !prefs.interactivePreview )
        return false;

    int cursorx = cursorScreenPos.x();
    int cursory = cursorScreenPos.y();
    
    int barleftx = barBottomLeft.x();
    int barrightx = barBottomRight.x();
    int barbottomy = barBottomLeft.y();
    
    int previewBoxWidth = mPreviewBox->width();
    int boxleftx = barleftx - (previewBoxWidth / 2);
    int boxrightx = barrightx + (previewBoxWidth / 2);
    
    // Clamp to window bounds if in windowed mode
    if (mWindowRect.isValid())
    {
        boxleftx = qMax(boxleftx, mWindowRect.left());
        boxrightx = qMin(boxrightx, mWindowRect.right());
    }
    
    int boxtopy = mPreviewBox->geometry().top();
    int boxbottomy = mPreviewBox->geometry().bottom();

    // Region 1: Box area
    bool inBoxArea = cursorx >= boxleftx && cursorx <= boxrightx && 
                     cursory >= boxtopy && cursory <= boxbottomy;
    
    // Region 2: Bar area (between box bottom and bar bottom)
    bool inBarArea = cursorx >= barleftx && cursorx <= barrightx && 
                     cursory >= boxbottomy && cursory <= barbottomy;


    bool result = inBoxArea || inBarArea;
    
    return result;
}

bool TooltipBridge::eventFilter(QObject *obj, QEvent *event)
{
    // Handle click events on tooltip widgets
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        
        // Only handle left button presses
        if (mouseEvent->button() == Qt::LeftButton)
        {
            // Check if click is in hover area
            if (isCursorInHoverArea(mouseEvent->globalPos(), mBarBottomLeft, mBarBottomRight))
            {
                // Forward the click event to the slider
                emit forwardMouseClick(mouseEvent->globalPos());
                return true; // Event handled
            }
        }
    }
    
    return QWidget::eventFilter(obj, event);
}
