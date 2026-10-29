#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "simple_preferences_seekbar.hpp"
#include "simple_preferences.hpp"
#include "preferences_widgets.hpp"

#include <vlc_config_cat.h>
#include <vlc_configuration.h>

#include "ui/sprefs_seekbar_preview.h"
#include "components/flowlayout.hpp"

#include <QButtonGroup>
#include <QCheckBox>
#include <QLabel>
#include <QDialog>
#include <QDialogButtonBox>
#include <QAbstractButton>
#include <QSignalBlocker>
#include <QSettings>
#include <QString>
#include <QSlider>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QTabBar>
#include <cstring>

// Forward declarations for reset functions
void resetSeekbarPreviewFrameExtractionDefaults(QWidget *panel);
void resetSeekbarPreviewImageDefaults(QWidget *panel, QList<ConfigControl *> &controls);
void resetSeekbarPreviewTimestampDefaults(QWidget *panel, QList<ConfigControl *> &controls);
void resetSeekbarPreviewBehaviourDefaults(QWidget *panel);
void testloadSeekbarPreviewPreferences(intf_thread_t *p_intf);

namespace
{
QString frameResolutionText( int value )
{
    switch( value )
    {
        case 0: return "144p";
        case 1: return "240p";
        case 2: return "360p";
        case 3: return "480p";
        case 4: return "720p";
        case 5: return "1080p";
        default: return "360p";
    }
}

void focusPreferencesSaveButton( QWidget *panel )
{
    QWidget *window = panel ? panel->window() : nullptr;
    if( !window )
        return;

    QTimer::singleShot( 0, window, [window]() {
        QDialogButtonBox *buttonsBox = window->findChild<QDialogButtonBox *>();
        if( !buttonsBox )
            return;

        for( QAbstractButton *button : buttonsBox->buttons() )
        {
            if( buttonsBox->buttonRole( button ) == QDialogButtonBox::AcceptRole )
            {
                button->setFocus( Qt::OtherFocusReason );
                break;
            }
        }
    } );
}

void resetColorControl( QList<ConfigControl *> &controls, const char *name, int value )
{
    for( ConfigControl *control : controls )
    {
        if( strcmp( control->getName(), name ) == 0 )
        {
            if( ColorConfigControl *colorControl = qobject_cast<ColorConfigControl *>( control ) )
                colorControl->setValue( value );
            break;
        }
    }
}
}

#define CONFIG_SPINBOX( option, label, qcontrol ) \
    do { \
        module_config_t *p_config = config_FindConfig( option ); \
        if( p_config ) { \
            ConfigControl *control = new IntegerConfigControl( VLC_OBJECT(p_intf), p_config, label, ui.qcontrol ); \
            controls.append( control ); \
        } else { \
            ui.qcontrol->setEnabled( true ); \
        } \
    } while(0)

#define CONFIG_SLIDER( option, label, qcontrol ) \
    do { \
        module_config_t *p_config = config_FindConfig( option ); \
        if( p_config ) { \
            ConfigControl *control = new IntegerRangeSliderConfigControl( VLC_OBJECT(p_intf), p_config, label, ui.qcontrol ); \
            controls.append( control ); \
        } else { \
            ui.qcontrol->setEnabled( true ); \
        } \
    } while(0)

#define CONFIG_BOOL( option, qcontrol ) \
    do { \
        module_config_t *p_config = config_FindConfig( option ); \
        if( p_config ) { \
            ConfigControl *control = new BoolConfigControl( VLC_OBJECT(p_intf), p_config, NULL, ui.qcontrol ); \
            controls.append( control ); \
        } else { \
            ui.qcontrol->setEnabled( true ); \
        } \
    } while(0)

#define CONFIG_COLOR( option, label, qcontrol ) \
    do { \
        module_config_t *p_config = config_FindConfig( option ); \
        if( p_config ) { \
            ConfigControl *control = new ColorConfigControl( VLC_OBJECT(p_intf), p_config, label, ui.qcontrol ); \
            controls.append( control ); \
        } else { \
            ui.qcontrol->setEnabled( true ); \
        } \
    } while(0)

void setupSeekbarPreviewPrefs(QWidget *panel,
                              intf_thread_t *p_intf,
                              QList<ConfigControl *> &controls,
                              QHash<QString, QWidget *> &optionWidgets)
{
    Ui::SPrefsSeekbarPreview ui;
    ui.setupUi( panel );

    // Replace QHBoxLayout with FlowLayout for dynamicSeekContainer
    if (ui.dynamicSeekContainer && ui.dynamicSeekContainer->layout()) {
        delete ui.dynamicSeekContainer->layout();
    }
    FlowLayout *flowLayout = new FlowLayout(ui.dynamicSeekContainer);
    flowLayout->setContentsMargins(0, 0, 0, 0);
    flowLayout->setSpacing(6); // Use appropriate spacing
    
    // Add the existing widgets to the flow layout
    if (ui.dynamicSeekPrefix) flowLayout->addWidget(ui.dynamicSeekPrefix);
    if (ui.dynamicSeekThreshold) flowLayout->addWidget(ui.dynamicSeekThreshold);
    if (ui.dynamicSeekSuffix) flowLayout->addWidget(ui.dynamicSeekSuffix);
    
    ui.dynamicSeekContainer->setLayout(flowLayout);

    const QString settingsKey = "MainWindow/SeekbarPreviewTab";
    QSettings *settings = getSettings();
    int lastTab = settings->value( settingsKey, 0 ).toInt();
    if( lastTab < 0 || lastTab >= ui.tabWidget->count() )
        lastTab = 0;
    ui.tabWidget->setCurrentIndex( lastTab );
    QObject::connect( ui.tabWidget, &QTabWidget::currentChanged, panel,
        [settings, settingsKey]( int index ) {
            settings->setValue( settingsKey, index );
        } );
    settings->setValue( settingsKey, lastTab );

    // Print seekbar preview preferences on panel initialization
    testloadSeekbarPreviewPreferences(p_intf);

    // Connect reset button to reset all seekbar preview preferences
    QObject::connect( ui.resetToDefaults, &QPushButton::clicked, panel,
        [panel, p_intf, &controls]() {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(
                panel,
                "Reset Seekbar Preview Preferences",
                "Are you sure you want to reset all seekbar preview preferences to their default values?",
                QMessageBox::Yes | QMessageBox::No,
                QMessageBox::Yes
            );
            if (reply == QMessageBox::Yes) {
                resetSeekbarPreviewFrameExtractionDefaults( panel );
                resetSeekbarPreviewImageDefaults( panel, controls );
                resetSeekbarPreviewTimestampDefaults( panel, controls );
                resetSeekbarPreviewBehaviourDefaults( panel );
                
                // Apply the changes by calling doApply on each ConfigControl
                for( ConfigControl *c : controls ) {
                    c->doApply();
                }
                
                // Save configuration to file
                config_SaveConfigFile( p_intf );
                
                QMessageBox::information(
                    panel,
                    "Preferences Reset",
                    "Seekbar preview preferences have been reset to default values and saved."
                );

                focusPreferencesSaveButton( panel );
            }
        } );

    // Disable tab switching on scroll when the cursor is on tabs
    class TabWidgetScrollEventFilter : public QObject {
    public:
        explicit TabWidgetScrollEventFilter( QTabBar *tabBar ) : QObject( tabBar ), m_tabBar( tabBar ) {}

        bool eventFilter( QObject *obj, QEvent *event ) override
        {
            if( event->type() == QEvent::Wheel && obj == m_tabBar )
            {
                return true;
            }

            return QObject::eventFilter(obj, event);
        }

    private:
        QTabBar *m_tabBar;
    };

    ui.tabWidget->tabBar()->installEventFilter( new TabWidgetScrollEventFilter( ui.tabWidget->tabBar() ) );

    QButtonGroup *seekModeGroup = new QButtonGroup( panel );
    seekModeGroup->setExclusive( true );
    seekModeGroup->addButton( ui.seekModeExact );
    seekModeGroup->addButton( ui.seekModeIframe );
    seekModeGroup->addButton( ui.seekModeDynamic );
    
    // Set up the seek mode based on the config value
    int seekMode = config_GetInt( p_intf, "seekbar-seek-mode" );
    switch( seekMode ) {
        case 0:
            ui.seekModeExact->setChecked( true );
            ui.dynamicSeekContainer->setEnabled( false );
            break;
        case 1:
            ui.seekModeIframe->setChecked( true );
            ui.dynamicSeekContainer->setEnabled( false );
            break;
        case 2:
            ui.seekModeDynamic->setChecked( true );
            ui.dynamicSeekContainer->setEnabled( true );
            break;
        default:
            ui.seekModeIframe->setChecked( true );
            ui.dynamicSeekContainer->setEnabled( false );
    }
    
    // Connect the radio buttons to enable/disable the dynamic seek container
    QObject::connect( ui.seekModeExact, &QRadioButton::toggled, [ui]() {
        ui.dynamicSeekContainer->setEnabled( false );
    } );
    
    QObject::connect( ui.seekModeIframe, &QRadioButton::toggled, [ui]() {
        ui.dynamicSeekContainer->setEnabled( false );
    } );
    
    QObject::connect( ui.seekModeDynamic, &QRadioButton::toggled, [ui, p_intf]() {
        ui.dynamicSeekContainer->setEnabled( true );
        // Update the config value when dynamic mode is selected
        config_PutInt( p_intf, "seekbar-seek-mode", 2 );
    } );
    
    QObject::connect( ui.seekModeExact, &QRadioButton::toggled, [ui, p_intf]( bool checked ) {
        if( checked ) {
            ui.dynamicSeekContainer->setEnabled( false );
            // Update the config value when exact mode is selected
            config_PutInt( p_intf, "seekbar-seek-mode", 0 );
        }
    } );
    
    QObject::connect( ui.seekModeIframe, &QRadioButton::toggled, [ui, p_intf]( bool checked ) {
        if( checked ) {
            ui.dynamicSeekContainer->setEnabled( false );
            // Update the config value when iframe mode is selected
            config_PutInt( p_intf, "seekbar-seek-mode", 1 );
        }
    } );

    // Maps widgets to config strings used in core VLC options
    // NOTE: Keep UI enabled even if config variables are missing during development.

    // General group
    CONFIG_BOOL( "seekbar-preview", enableSeekbarPreview );
    optionWidgets["seekbar-preview"] = ui.enableSeekbarPreview;

    // Frame Extraction group - Seek mode is now handled by radio buttons
    // The radio buttons are managed manually since they represent a single integer config
    
    CONFIG_SLIDER( "seekbar-cache-limit", ui.labelCacheLimit, cacheLimit );
    CONFIG_SLIDER( "seekbar-frame-res", ui.labelFrameRes, frameResolution );

    ui.cacheLimitValue->setText( QString::number( ui.cacheLimit->value() ) + " MB" );
    QObject::connect( ui.cacheLimit, &QSlider::valueChanged, ui.cacheLimitValue,
        [label = ui.cacheLimitValue]( int value ) {
            label->setText( QString::number( value ) + " MB" );
        } );

    ui.frameResolutionValue->setText( frameResolutionText( ui.frameResolution->value() ) );
    QObject::connect( ui.frameResolution, &QSlider::valueChanged, ui.frameResolutionValue,
        [label = ui.frameResolutionValue]( int value ) {
            label->setText( frameResolutionText( value ) );
        } );

    optionWidgets["seekbar-seek-mode"] = ui.seekModeExact;
    optionWidgets["seekbar-dynamic-threshold"] = ui.dynamicSeekThreshold;
    optionWidgets["seekbar-cache-limit"] = ui.cacheLimit;
    optionWidgets["seekbar-frame-res"] = ui.frameResolution;

    // Add ConfigControl for dynamic threshold
    CONFIG_SPINBOX( "seekbar-dynamic-threshold", NULL, dynamicSeekThreshold );

    // Preview Image widgets
    optionWidgets["seekbar-box-size"] = ui.boxSize;
    optionWidgets["seekbar-border-width"] = ui.previewBorderWidth;
    optionWidgets["seekbar-border-color"] = ui.previewBorderColor;
    optionWidgets["seekbar-border-radius"] = ui.previewBorderRadius;

    // Preview Image group - Preview Scaling
    CONFIG_SLIDER( "seekbar-box-size", ui.labelBoxSize, boxSize );
    ui.boxSizeValue->setText( QString::number( ui.boxSize->value() ) + " px" );
    QObject::connect( ui.boxSize, &QSlider::valueChanged, ui.boxSizeValue,
        [label = ui.boxSizeValue]( int value ) {
            label->setText( QString::number( value ) + " px" );
        } );

    // Preview Image group - Border Settings
    CONFIG_SLIDER( "seekbar-border-width", ui.labelBorderWidth, previewBorderWidth );
    ui.previewBorderWidthValue->setText( QString::number( ui.previewBorderWidth->value() / 10.0, 'f', 1 ) + " px" );
    QObject::connect( ui.previewBorderWidth, &QSlider::valueChanged, ui.previewBorderWidthValue,
        [label = ui.previewBorderWidthValue]( int value ) {
            label->setText( QString::number( value / 10.0, 'f', 1 ) + " px" );
        } );

    CONFIG_COLOR( "seekbar-border-color", ui.labelBorderColor, previewBorderColor );

    CONFIG_SLIDER( "seekbar-border-radius", ui.labelBorderRadius, previewBorderRadius );
    ui.previewBorderRadiusValue->setText( QString::number( ui.previewBorderRadius->value() / 10.0, 'f', 1 ) + " px" );
    QObject::connect( ui.previewBorderRadius, &QSlider::valueChanged, ui.previewBorderRadiusValue,
        [label = ui.previewBorderRadiusValue]( int value ) {
            label->setText( QString::number( value / 10.0, 'f', 1 ) + " px" );
        } );

    // Timestamp group
    CONFIG_SLIDER( "seekbar-font-size-scale", ui.labelFontSizeScale, fontSizeScale );
    ui.fontSizeScaleValue->setText( QString::number( ui.fontSizeScale->value() / 4.0, 'f', 2 ) );
    QObject::connect( ui.fontSizeScale, &QSlider::valueChanged, ui.fontSizeScaleValue,
        [label = ui.fontSizeScaleValue]( int value ) {
            label->setText( QString::number( value / 4.0, 'f', 2 ) );
        } );

    CONFIG_COLOR( "seekbar-text-color", ui.labelTextCol, textColor );
    CONFIG_COLOR( "seekbar-ts-bg-color", ui.labelTSBgColor, timestampBackgroundColor );

    CONFIG_SLIDER( "seekbar-ts-border-width", ui.labelTSBorderWidth, timestampBorderWidth );
    ui.timestampBorderWidthValue->setText( QString::number( ui.timestampBorderWidth->value() / 4.0, 'f', 2 ) + " px" );
    QObject::connect( ui.timestampBorderWidth, &QSlider::valueChanged, ui.timestampBorderWidthValue,
        [label = ui.timestampBorderWidthValue]( int value ) {
            label->setText( QString::number( value / 4.0, 'f', 2 ) + " px" );
        } );

    CONFIG_COLOR( "seekbar-ts-border-color", ui.labelTSBorderColor, timestampBorderColor );

    CONFIG_SLIDER( "seekbar-ts-border-radius", ui.labelTSBorderRadius, timestampBorderRadius );
    ui.timestampBorderRadiusValue->setText( QString::number( ui.timestampBorderRadius->value() / 4.0, 'f', 2 ) + " px" );
    QObject::connect( ui.timestampBorderRadius, &QSlider::valueChanged, ui.timestampBorderRadiusValue,
        [label = ui.timestampBorderRadiusValue]( int value ) {
            label->setText( QString::number( value / 4.0, 'f', 2 ) + " px" );
        } );

    CONFIG_SLIDER( "seekbar-padding-y", ui.labelPaddingY, paddingY );
    ui.paddingYValue->setText( QString::number( ui.paddingY->value() / 10.0, 'f', 1 ) + " px" );
    QObject::connect( ui.paddingY, &QSlider::valueChanged, ui.paddingYValue,
        [label = ui.paddingYValue]( int value ) {
            label->setText( QString::number( value / 10.0, 'f', 1 ) + " px" );
        } );

    CONFIG_SLIDER( "seekbar-padding-x", ui.labelPaddingX, paddingX );
    ui.paddingXValue->setText( QString::number( ui.paddingX->value() / 10.0, 'f', 1 ) + " px" );
    QObject::connect( ui.paddingX, &QSlider::valueChanged, ui.paddingXValue,
        [label = ui.paddingXValue]( int value ) {
            label->setText( QString::number( value / 10.0, 'f', 1 ) + " px" );
        } );

    CONFIG_SLIDER( "seekbar-bottom-margin", ui.labelBottomMargin, bottomMargin );
    ui.bottomMarginValue->setText( QString::number( ui.bottomMargin->value() / 4.0, 'f', 2 ) + " px" );
    QObject::connect( ui.bottomMargin, &QSlider::valueChanged, ui.bottomMarginValue,
        [label = ui.bottomMarginValue]( int value ) {
            label->setText( QString::number( value / 4.0, 'f', 2 ) + " px" );
        } );

    CONFIG_SLIDER( "seekbar-top-margin", ui.labelTopMargin, topMargin );
    ui.topMarginValue->setText( QString::number( ui.topMargin->value() / 4.0, 'f', 2 ) + " px" );
    QObject::connect( ui.topMargin, &QSlider::valueChanged, ui.topMarginValue,
        [label = ui.topMarginValue]( int value ) {
            label->setText( QString::number( value / 4.0, 'f', 2 ) + " px" );
        } );

    // Behaviour group
    CONFIG_BOOL( "seekbar-interactive-preview", interactivePreview );
    CONFIG_BOOL( "seekbar-hand-cursor", handCursorOnHover );
    CONFIG_SLIDER( "seekbar-show-delay", ui.labelShowDelay, showDelay );
    ui.showDelayValue->setText( QString::number( ui.showDelay->value() ) + " ms" );
    QObject::connect( ui.showDelay, &QSlider::valueChanged, ui.showDelayValue,
        [label = ui.showDelayValue]( int value ) {
            label->setText( QString::number( value ) + " ms" );
        } );
}

static int64_t configDefault( const char *name )
{
    module_config_t *cfg = config_FindConfig( name );
    return cfg ? cfg->orig.i : 0;
}

static bool configDefaultBool( const char *name )
{
    module_config_t *cfg = config_FindConfig( name );
    return cfg ? cfg->orig.i : false;
}

void resetSeekbarPreviewFrameExtractionDefaults( QWidget *panel )
{
    QRadioButton *exactFrame = panel->findChild<QRadioButton *>( "seekModeExact" );
    QRadioButton *iframeFrame = panel->findChild<QRadioButton *>( "seekModeIframe" );
    QRadioButton *dynamicFrame = panel->findChild<QRadioButton *>( "seekModeDynamic" );
    QSlider *cacheLimit = panel->findChild<QSlider *>( "cacheLimit" );
    QSlider *frameResolution = panel->findChild<QSlider *>( "frameResolution" );
    QSpinBox *dynamicThreshold = panel->findChild<QSpinBox *>( "dynamicSeekThreshold" );
    QLabel *cacheLimitValue = panel->findChild<QLabel *>( "cacheLimitValue" );

    if( exactFrame && iframeFrame && dynamicFrame )
    {
        QSignalBlocker exactBlocker( exactFrame );
        QSignalBlocker iframeBlocker( iframeFrame );
        QSignalBlocker dynamicBlocker( dynamicFrame );
        int seekMode = configDefault( "seekbar-seek-mode" );
        exactFrame->setChecked( seekMode == 0 );
        iframeFrame->setChecked( seekMode == 1 );
        dynamicFrame->setChecked( seekMode == 2 );
    }

    if( cacheLimit )
    {
        QSignalBlocker sliderBlocker( cacheLimit );
        int val = configDefault( "seekbar-cache-limit" );
        cacheLimit->setValue( val );
        if( cacheLimitValue )
            cacheLimitValue->setText( QString::number( val ) + " MB" );
    }

    if( frameResolution )
    {
        QSignalBlocker sliderBlocker( frameResolution );
        int val = configDefault( "seekbar-frame-res" );
        frameResolution->setValue( val );
        if( QLabel *frameResolutionValue = panel->findChild<QLabel *>( "frameResolutionValue" ) )
            frameResolutionValue->setText( frameResolutionText( val ) );
    }

    if( dynamicThreshold )
    {
        QSignalBlocker spinboxBlocker( dynamicThreshold );
        dynamicThreshold->setValue( configDefault( "seekbar-dynamic-threshold" ) );
    }
}

void resetSeekbarPreviewImageDefaults( QWidget *panel, QList<ConfigControl *> &controls )
{
    QSlider *boxSize = panel->findChild<QSlider *>( "boxSize" );
    QSlider *borderWidth = panel->findChild<QSlider *>( "previewBorderWidth" );
    QSlider *borderRadius = panel->findChild<QSlider *>( "previewBorderRadius" );
    QLabel *boxSizeValue = panel->findChild<QLabel *>( "boxSizeValue" );
    QLabel *borderWidthValue = panel->findChild<QLabel *>( "previewBorderWidthValue" );
    QLabel *borderRadiusValue = panel->findChild<QLabel *>( "previewBorderRadiusValue" );

    if( boxSize )
    {
        QSignalBlocker sliderBlocker( boxSize );
        int val = configDefault( "seekbar-box-size" );
        boxSize->setValue( val );
        if( boxSizeValue )
            boxSizeValue->setText( QString::number( val ) + " px" );
    }

    if( borderWidth )
    {
        QSignalBlocker sliderBlocker( borderWidth );
        int val = configDefault( "seekbar-border-width" );
        borderWidth->setValue( val );
        if( borderWidthValue )
            borderWidthValue->setText( QString::number( val / 10.0, 'f', 1 ) + " px" );
    }

    if( borderRadius )
    {
        QSignalBlocker sliderBlocker( borderRadius );
        int val = configDefault( "seekbar-border-radius" );
        borderRadius->setValue( val );
        if( borderRadiusValue )
            borderRadiusValue->setText( QString::number( val / 10.0, 'f', 1 ) + " px" );
    }

    resetColorControl( controls, "seekbar-border-color", configDefault( "seekbar-border-color" ) );
}

void resetSeekbarPreviewTimestampDefaults( QWidget *panel, QList<ConfigControl *> &controls )
{
    QSlider *fontSizeScale = panel->findChild<QSlider *>( "fontSizeScale" );
    QSlider *timestampBorderWidth = panel->findChild<QSlider *>( "timestampBorderWidth" );
    QSlider *timestampBorderRadius = panel->findChild<QSlider *>( "timestampBorderRadius" );
    QSlider *paddingY = panel->findChild<QSlider *>( "paddingY" );
    QSlider *paddingX = panel->findChild<QSlider *>( "paddingX" );
    QSlider *bottomMargin = panel->findChild<QSlider *>( "bottomMargin" );
    QSlider *topMargin = panel->findChild<QSlider *>( "topMargin" );
    QLabel *fontSizeScaleValue = panel->findChild<QLabel *>( "fontSizeScaleValue" );
    QLabel *timestampBorderWidthValue = panel->findChild<QLabel *>( "timestampBorderWidthValue" );
    QLabel *timestampBorderRadiusValue = panel->findChild<QLabel *>( "timestampBorderRadiusValue" );
    QLabel *paddingYValue = panel->findChild<QLabel *>( "paddingYValue" );
    QLabel *paddingXValue = panel->findChild<QLabel *>( "paddingXValue" );
    QLabel *bottomMarginValue = panel->findChild<QLabel *>( "bottomMarginValue" );
    QLabel *topMarginValue = panel->findChild<QLabel *>( "topMarginValue" );

    if( fontSizeScale )
    {
        QSignalBlocker sliderBlocker( fontSizeScale );
        int val = configDefault( "seekbar-font-size-scale" );
        fontSizeScale->setValue( val );
        if( fontSizeScaleValue )
            fontSizeScaleValue->setText( QString::number( val / 4.0, 'f', 2 ) );
    }

    resetColorControl( controls, "seekbar-text-color", configDefault( "seekbar-text-color" ) );
    resetColorControl( controls, "seekbar-ts-bg-color", configDefault( "seekbar-ts-bg-color" ) );

    if( timestampBorderWidth )
    {
        QSignalBlocker sliderBlocker( timestampBorderWidth );
        int val = configDefault( "seekbar-ts-border-width" );
        timestampBorderWidth->setValue( val );
        if( timestampBorderWidthValue )
            timestampBorderWidthValue->setText( QString::number( val / 4.0, 'f', 2 ) + " px" );
    }

    resetColorControl( controls, "seekbar-ts-border-color", configDefault( "seekbar-ts-border-color" ) );

    if( timestampBorderRadius )
    {
        QSignalBlocker sliderBlocker( timestampBorderRadius );
        int val = configDefault( "seekbar-ts-border-radius" );
        timestampBorderRadius->setValue( val );
        if( timestampBorderRadiusValue )
            timestampBorderRadiusValue->setText( QString::number( val / 4.0, 'f', 2 ) + " px" );
    }

    if( paddingY )
    {
        QSignalBlocker sliderBlocker( paddingY );
        int val = configDefault( "seekbar-padding-y" );
        paddingY->setValue( val );
        if( paddingYValue )
            paddingYValue->setText( QString::number( val / 10.0, 'f', 1 ) + " px" );
    }

    if( paddingX )
    {
        QSignalBlocker sliderBlocker( paddingX );
        int val = configDefault( "seekbar-padding-x" );
        paddingX->setValue( val );
        if( paddingXValue )
            paddingXValue->setText( QString::number( val / 10.0, 'f', 1 ) + " px" );
    }

    if( bottomMargin )
    {
        QSignalBlocker sliderBlocker( bottomMargin );
        int val = configDefault( "seekbar-bottom-margin" );
        bottomMargin->setValue( val );
        if( bottomMarginValue )
            bottomMarginValue->setText( QString::number( val / 4.0, 'f', 2 ) + " px" );
    }

    if( topMargin )
    {
        QSignalBlocker sliderBlocker( topMargin );
        int val = configDefault( "seekbar-top-margin" );
        topMargin->setValue( val );
        if( topMarginValue )
            topMarginValue->setText( QString::number( val / 4.0, 'f', 2 ) + " px" );
    }
}

void resetSeekbarPreviewBehaviourDefaults( QWidget *panel )
{
    QCheckBox *interactivePreview = panel->findChild<QCheckBox *>( "interactivePreview" );
    QCheckBox *handCursorOnHover = panel->findChild<QCheckBox *>( "handCursorOnHover" );
    QSlider *showDelay = panel->findChild<QSlider *>( "showDelay" );
    QLabel *showDelayValue = panel->findChild<QLabel *>( "showDelayValue" );

    if( interactivePreview )
    {
        QSignalBlocker checkboxBlocker( interactivePreview );
        interactivePreview->setChecked( configDefaultBool( "seekbar-interactive-preview" ) );
    }

    if( handCursorOnHover )
    {
        QSignalBlocker checkboxBlocker( handCursorOnHover );
        handCursorOnHover->setChecked( configDefaultBool( "seekbar-hand-cursor" ) );
    }

    if( showDelay )
    {
        QSignalBlocker sliderBlocker( showDelay );
        int val = configDefault( "seekbar-show-delay" );
        showDelay->setValue( val );
        if( showDelayValue )
            showDelayValue->setText( QString::number( val ) + " ms" );
    }
}
// Function to load all seekbar preview preferences into a struct
SeekbarPreviewPreferences loadSeekbarPreviewPreferences(intf_thread_t *p_intf)
{
    SeekbarPreviewPreferences prefs;
    
    // Load preferences using config_Get* functions
    prefs.enableSeekbarPreview = config_GetInt(p_intf, "seekbar-preview") != 0;
    
    prefs.seekMode = config_GetInt(p_intf, "seekbar-seek-mode");
    prefs.dynamicThreshold = config_GetInt(p_intf, "seekbar-dynamic-threshold");
    prefs.cacheLimit = config_GetInt(p_intf, "seekbar-cache-limit");
    prefs.frameResolution = config_GetInt(p_intf, "seekbar-frame-res");
    
    prefs.boxSize = config_GetInt(p_intf, "seekbar-box-size");
    prefs.previewBorderWidth = config_GetInt(p_intf, "seekbar-border-width");
    prefs.previewBorderColor = QColor(config_GetInt(p_intf, "seekbar-border-color"));
    prefs.previewBorderRadius = config_GetInt(p_intf, "seekbar-border-radius");
    
    prefs.fontSizeScale = config_GetInt(p_intf, "seekbar-font-size-scale");
    prefs.textColor = QColor(config_GetInt(p_intf, "seekbar-text-color"));
    prefs.timestampBackgroundColor = QColor(config_GetInt(p_intf, "seekbar-ts-bg-color"));
    prefs.timestampBorderWidth = config_GetInt(p_intf, "seekbar-ts-border-width");
    prefs.timestampBorderColor = QColor(config_GetInt(p_intf, "seekbar-ts-border-color"));
    prefs.timestampBorderRadius = config_GetInt(p_intf, "seekbar-ts-border-radius");
    prefs.paddingY = config_GetInt(p_intf, "seekbar-padding-y");
    prefs.paddingX = config_GetInt(p_intf, "seekbar-padding-x");
    prefs.bottomMargin = config_GetInt(p_intf, "seekbar-bottom-margin");
    prefs.topMargin = config_GetInt(p_intf, "seekbar-top-margin");
    
    prefs.interactivePreview = config_GetInt(p_intf, "seekbar-interactive-preview") != 0;
    prefs.handCursorOnHover = config_GetInt(p_intf, "seekbar-hand-cursor") != 0;
    prefs.showDelay = config_GetInt(p_intf, "seekbar-show-delay");
    
    return prefs;
}

// Test function to demonstrate loading and printing seekbar preferences
void testloadSeekbarPreviewPreferences(intf_thread_t *p_intf)
{
    SeekbarPreviewPreferences prefs = loadSeekbarPreviewPreferences(p_intf);

    qDebug() << "Seekbar Preview Preferences:";
    qDebug() << "General:";
    qDebug() << "  Enable Seekbar Preview:" << prefs.enableSeekbarPreview;

    qDebug() << "Frame Extraction:";
    qDebug() << "  Seek Mode:" << prefs.seekMode << "(0=Exact, 1=I-frame, 2=Dynamic)";
    qDebug() << "  Dynamic Threshold:" << prefs.dynamicThreshold << " seconds";
    qDebug() << "  Cache Limit:" << prefs.cacheLimit << " MB";
    qDebug() << "  Frame Resolution:" << prefs.frameResolution;

    qDebug() << "Preview Image:";
    qDebug() << "  Box Size:" << prefs.boxSize << " px";
    qDebug() << "  Border Width:" << (prefs.previewBorderWidth / 10.0) << " px";
    qDebug() << "  Border Color:" << prefs.previewBorderColor.name();
    qDebug() << "  Border Radius:" << (prefs.previewBorderRadius / 10.0) << " px";

    qDebug() << "Timestamp:";
    qDebug() << "  Font Size Scale:" << (prefs.fontSizeScale / 4.0);
    qDebug() << "  Text Color:" << prefs.textColor.name();
    qDebug() << "  Background Color:" << prefs.timestampBackgroundColor.name();
    qDebug() << "  Border Width:" << (prefs.timestampBorderWidth / 4.0) << " px";
    qDebug() << "  Border Color:" << prefs.timestampBorderColor.name();
    qDebug() << "  Border Radius:" << (prefs.timestampBorderRadius / 4.0) << " px";
    qDebug() << "  Padding Y:" << (prefs.paddingY / 10.0) << " px";
    qDebug() << "  Padding X:" << (prefs.paddingX / 10.0) << " px";
    qDebug() << "  Bottom Margin:" << (prefs.bottomMargin / 4.0) << " px";
    qDebug() << "  Top Margin:" << (prefs.topMargin / 4.0) << " px";

    qDebug() << "Behaviour:";
    qDebug() << "  Interactive Preview:" << prefs.interactivePreview;
    qDebug() << "  Hand Cursor on Hover:" << prefs.handCursorOnHover;
    qDebug() << "  Show Delay:" << prefs.showDelay << " ms";
}

