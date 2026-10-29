/*****************************************************************************
 * Copyright © 2011-2012 VideoLAN
 * $Id$
 *
 * Authors: Ludovic Fauvet <etix@l0cal.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include "seekbar_time_tooltip.hpp"
#include "../../components/simple_preferences_seekbar.hpp"

#include <QApplication>
#include <QPainter>
#include <QBitmap>
#include <QFontMetrics>
#if QT_VERSION < QT_VERSION_CHECK(5, 10, 0)
#include <QDesktopWidget>
#else
#include <QScreen>
#endif

static inline qreal tipHeightForBox(const QRectF &box)
{
    const qreal minTipHeight = 3.0;
    const qreal maxTipHeight = 9.0;
    const qreal scale = 0.25; // pointer height is 16% of box height
    return qBound(minTipHeight, box.height() * scale, maxTipHeight);
}

static inline qreal tipHalfWidthForHeight(qreal tipHeight)
{
    const qreal widthToHeightRatio = 0.8;
    return tipHeight * widthToHeightRatio;
}

SeekbarTimeTooltip::SeekbarTimeTooltip( QWidget *parent, intf_thread_t *p_intf ) :
    QWidget( parent ), m_p_intf( p_intf )
{
    setWindowFlags( Qt::ToolTip                 |
                    Qt::WindowStaysOnTopHint    |
                    Qt::FramelessWindowHint     );

    // Tell Qt that it doesn't need to erase the background before
    // a paintEvent occurs. This should save some CPU cycles.
    setAttribute( Qt::WA_OpaquePaintEvent );
    setAttribute( Qt::WA_TranslucentBackground );
    setAttribute( Qt::WA_TransparentForMouseEvents );

    // Inherit from the system default font size -5
    mFont = QFont( "Verdana", qMax( qApp->font().pointSize() - 5, 7 ) );
    mTipX = -1;
    mTextColor = qApp->palette().text().color();
    mBackgroundColor = qApp->palette().base().color();
    mBorderWidth = 0.0;
    mBorderColor = Qt::black;
    mBorderRadius = 0.0;
    mPaddingX = 2.0;
    mPaddingY = 2.0;
    mTopMargin = 0.0;
    mBottomMargin = 0.0;

    // By default the widget is unintialized and should not be displayed
    resize( 0, 0 );
}

static inline qreal clampTipX(qreal x, const QRectF &box, qreal radius)
{
    return qMin(qMax(x, box.left() + radius), box.right() - radius);
}

void SeekbarTimeTooltip::adjustPosition()
{
    if( mDisplayedText.isEmpty() )
    {
        resize( 0, 0 );
        return;
    }

    QFontMetrics metrics( mFont );
    QRectF textbox = metrics.boundingRect( mDisplayedText );
    textbox.moveTo( 0, 0 );
    textbox.adjust( -mPaddingX, -mPaddingY,
                     mPaddingX,  mPaddingY );

    QRectF oldBox = mBox;
    qreal halfBorder = mBorderWidth / 2.0;
    mBox = QRectF( halfBorder, halfBorder,
                   textbox.width(), textbox.height() );

    qreal tipHeight = tipHeightForBox( mBox );
    QSizeF size( mBox.width() + mBorderWidth + 1.0,
                 mBox.height() + tipHeight + mBorderWidth + 1.0 );

    QPointF position( mTarget.x() - size.width() / 2.0,
#if defined( Q_OS_WIN )
        mTarget.y() - size.height() - mBottomMargin );
#else
        mTarget.y() - size.height() - mBottomMargin );
#endif

#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
    QRect screen;
    auto *screenAt = QGuiApplication::screenAt( mTarget.toPoint() );
    if (screenAt != nullptr)
        screen = screenAt->geometry();
#else
    QRect screen = QApplication::desktop()->screenGeometry( mTarget.toPoint() );
#endif

    qreal maxX = screen.left() + screen.width() - size.width();
    qreal maxY = screen.top() + screen.height() - size.height();
    position.setX( qMin( qMax<qreal>( screen.left(), position.x() ), maxX ) );
    position.setY( qMin( qMax<qreal>( screen.top(), position.y() ), maxY ) );

    move( QPoint( qRound( position.x() ), qRound( position.y() ) ) );
    resize( QSize( qRound( size.width() ), qRound( size.height() ) ) );

    qreal tipX = mTarget.x() - position.x();
    if( mBox != oldBox || !qFuzzyCompare( mTipX + 1.0, tipX + 1.0 ) )
    {
        mTipX = clampTipX( tipX, mBox, qMin( mBorderRadius, qMin( mBox.width(), mBox.height() ) / 2.0 ) );
        buildPath();
    }
}

void SeekbarTimeTooltip::buildPath()
{
    qreal radius = qMin( mBorderRadius, qMin( mBox.width(), mBox.height() ) / 2.0 );
    qreal left = mBox.left();
    qreal top = mBox.top();
    qreal right = mBox.right();
    qreal bottom = mBox.bottom();

    qreal tipHeight = tipHeightForBox( mBox );
    qreal tipHalfWidth = tipHalfWidthForHeight( tipHeight );
    qreal tipLeft = clampTipX( mTipX - tipHalfWidth, mBox, radius );
    qreal tipRight = clampTipX( mTipX + tipHalfWidth, mBox, radius );

    mPainterPath = QPainterPath();
    mPainterPath.moveTo( left + radius, top );
    mPainterPath.lineTo( right - radius, top );
    if( radius > 0.0 )
        mPainterPath.arcTo( QRectF( right - 2.0 * radius, top, 2.0 * radius, 2.0 * radius ), 90.0, -90.0 );
    mPainterPath.lineTo( right, bottom - radius );
    if( radius > 0.0 )
        mPainterPath.arcTo( QRectF( right - 2.0 * radius, bottom - 2.0 * radius, 2.0 * radius, 2.0 * radius ), 0.0, -90.0 );
    mPainterPath.lineTo( tipRight, bottom );
    mPainterPath.lineTo( mTipX, bottom + tipHeight );
    mPainterPath.lineTo( tipLeft, bottom );
    mPainterPath.lineTo( left + radius, bottom );
    if( radius > 0.0 )
        mPainterPath.arcTo( QRectF( left, bottom - 2.0 * radius, 2.0 * radius, 2.0 * radius ), 270.0, -90.0 );
    mPainterPath.lineTo( left, top + radius );
    if( radius > 0.0 )
        mPainterPath.arcTo( QRectF( left, top, 2.0 * radius, 2.0 * radius ), 180.0, -90.0 );
    mPainterPath.closeSubpath();
}

void SeekbarTimeTooltip::setTip( const QPoint& target, const QString& time, const QString& text )
{
    QString displayedText = time;
    if ( !text.isEmpty() )
        displayedText.append( " - " ).append( text );

    bool contentChanged = ( mTarget != target || mDisplayedText != displayedText );

    qreal oldBorderWidth = mBorderWidth;
    qreal oldBorderRadius = mBorderRadius;
    qreal oldPaddingX = mPaddingX;
    qreal oldPaddingY = mPaddingY;
    qreal oldBottomMargin = mBottomMargin;
    qreal oldTopMargin = mTopMargin;
    QColor oldTextColor = mTextColor;
    QColor oldBackgroundColor = mBackgroundColor;
    QColor oldBorderColor = mBorderColor;
    qreal oldFontPointSize = mFont.pointSizeF();

    qreal fontAdjustment = 0.0;
    if( !m_p_intf )
    {
        mTextColor = qApp->palette().text().color();
        mBackgroundColor = qApp->palette().base().color();
        mBorderColor = Qt::black;
    }
    else
    {
        // Load preferences on every call to ensure real-time updates. This is efficient as VLC's config_Get* functions read from an in-memory cache, avoiding disk I/O overhead.
        SeekbarPreviewPreferences prefs = loadSeekbarPreviewPreferences( m_p_intf );
        fontAdjustment = prefs.fontSizeScale / 4.0;
        if( fontAdjustment < 0.0 )
            fontAdjustment = 0.0;
        mTextColor = prefs.textColor.isValid() ? prefs.textColor : qApp->palette().text().color();
        mBackgroundColor = prefs.timestampBackgroundColor.isValid() ? prefs.timestampBackgroundColor : qApp->palette().base().color();
        mBorderWidth = qMax<qreal>( 0.0, prefs.timestampBorderWidth / 4.0 );
        mBorderColor = prefs.timestampBorderColor.isValid() ? prefs.timestampBorderColor : Qt::black;
        mBorderRadius = qMax<qreal>( 0.0, prefs.timestampBorderRadius / 4.0 );
        mPaddingX = qMax<qreal>( 0.0, prefs.paddingX / 10.0 );
        mPaddingY = qMax<qreal>( 0.0, prefs.paddingY / 10.0 );
        mBottomMargin = qMax<qreal>( 0.0, prefs.bottomMargin / 4.0 );
        mTopMargin = qMax<qreal>( 0.0, prefs.topMargin / 4.0 );
    }

    float baseFontSize = qMax( qApp->font().pointSize() - 5, 7 );
    mFont.setPointSizeF( baseFontSize + fontAdjustment );

    bool styleChanged = ( oldBorderWidth != mBorderWidth || oldBorderRadius != mBorderRadius ||
                          oldPaddingX != mPaddingX || oldPaddingY != mPaddingY ||
                          oldBottomMargin != mBottomMargin || oldTopMargin != mTopMargin ||
                          oldTextColor != mTextColor || oldBackgroundColor != mBackgroundColor ||
                          oldBorderColor != mBorderColor || oldFontPointSize != mFont.pointSizeF() );

    mDisplayedText = displayedText;
    mTarget = target;
    mTime = time;
    mText = text;

    if( contentChanged || styleChanged )
        adjustPosition();

    update();
    raise();
}

void SeekbarTimeTooltip::show()
{
    setVisible( true );
    raise();
}

void SeekbarTimeTooltip::paintEvent( QPaintEvent * )
{
    QPainter p( this );
    p.setRenderHints( QPainter::Antialiasing | QPainter::TextAntialiasing );

    if( mBorderWidth > 0.0 )
    {
        QPen pen( mBorderColor, mBorderWidth );
        pen.setJoinStyle( Qt::MiterJoin );
        p.setPen( pen );
    }
    else
    {
        p.setPen( Qt::NoPen );
    }
    p.setBrush( mBackgroundColor );
    p.drawPath( mPainterPath );

    p.setFont( mFont );
    p.setPen( QPen( mTextColor, 1 ) );
    p.drawText( mBox, Qt::AlignCenter, mDisplayedText );
}
