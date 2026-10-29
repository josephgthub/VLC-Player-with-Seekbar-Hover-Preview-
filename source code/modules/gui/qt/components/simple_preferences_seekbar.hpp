#ifndef VLC_QT_SIMPLE_PREFS_SEEKBAR_HPP_
#define VLC_QT_SIMPLE_PREFS_SEEKBAR_HPP_

#include <QWidget>
#include <QList>
#include <QHash>
#include <QString>
#include <QColor>

class ConfigControl;
class intf_thread_t;

// Struct to hold all seekbar preview preferences
struct SeekbarPreviewPreferences {
    // General
    bool enableSeekbarPreview;
    
    // Frame Extraction
    int seekMode;            // 0=Exact, 1=I-frame, 2=Dynamic
    int dynamicThreshold;    // Threshold in seconds for dynamic mode
    int cacheLimit;          // MB
    int frameResolution;     // 0-5 (144p to 1080p)
    
    // Preview Image
    int boxSize;             // px
    int previewBorderWidth;  // px (stored as 10x actual value)
    QColor previewBorderColor;
    int previewBorderRadius; // px (stored as 10x actual value)
    
    // Timestamp
    int fontSizeScale;       // stored as 4x actual value
    QColor textColor;
    QColor timestampBackgroundColor;
    int timestampBorderWidth; // px (stored as 4x actual value)
    QColor timestampBorderColor;
    int timestampBorderRadius;// px (stored as 4x actual value)
    int paddingY;            // px (stored as 10x actual value)
    int paddingX;            // px (stored as 10x actual value)
    int bottomMargin;        // px (stored as 4x actual value)
    int topMargin;           // px (stored as 4x actual value)
    
    // Behaviour
    bool interactivePreview;
    bool handCursorOnHover;
    int showDelay;           // ms
};

void setupSeekbarPreviewPrefs(QWidget *panel,
                              intf_thread_t *p_intf,
                              QList<ConfigControl *> &controls,
                              QHash<QString, QWidget *> &optionWidgets);

void resetSeekbarPreviewFrameExtractionDefaults(QWidget *panel);
void resetSeekbarPreviewImageDefaults(QWidget *panel, QList<ConfigControl *> &controls);
void resetSeekbarPreviewTimestampDefaults(QWidget *panel, QList<ConfigControl *> &controls);
void resetSeekbarPreviewBehaviourDefaults(QWidget *panel);

// Function to load all seekbar preview preferences into a struct
SeekbarPreviewPreferences loadSeekbarPreviewPreferences(intf_thread_t *p_intf);

#endif
