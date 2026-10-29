#define Q_(a,b) QString::fromUtf8(_(a))
/********************************************************************************
** Form generated from reading UI file 'sprefs_seekbar_preview.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SPREFS_SEEKBAR_PREVIEW_H
#define SPREFS_SEEKBAR_PREVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SPrefsSeekbarPreview
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *generalTab;
    QVBoxLayout *verticalLayout_generalTab;
    QGroupBox *generalGroup;
    QVBoxLayout *verticalLayoutGeneral;
    QCheckBox *enableSeekbarPreview;
    QHBoxLayout *hboxLayout;
    QPushButton *resetToDefaults;
    QSpacerItem *spacerItem;
    QSpacerItem *spacerItem1;
    QWidget *frameTab;
    QVBoxLayout *verticalLayout_frameTab;
    QGroupBox *frameExtractionGroup;
    QFormLayout *formLayoutFE;
    QLabel *labelSeekMode;
    QWidget *seekModeContainer;
    QVBoxLayout *seekModeLayout;
    QRadioButton *seekModeExact;
    QLabel *seekModeExactDesc;
    QRadioButton *seekModeIframe;
    QLabel *seekModeIframeDesc;
    QRadioButton *seekModeDynamic;
    QWidget *dynamicSeekContainer;
    QHBoxLayout *dynamicSeekLayout;
    QLabel *dynamicSeekPrefix;
    QSpinBox *dynamicSeekThreshold;
    QLabel *dynamicSeekSuffix;
    QLabel *labelCacheLimit;
    QWidget *cacheLimitContainer;
    QHBoxLayout *cacheLimitLayout;
    QSlider *cacheLimit;
    QLabel *cacheLimitValue;
    QLabel *labelFrameRes;
    QWidget *frameResolutionContainer;
    QVBoxLayout *frameResolutionLayout;
    QWidget *frameResolutionRowWidget;
    QHBoxLayout *frameResolutionRow;
    QSlider *frameResolution;
    QLabel *frameResolutionValue;
    QWidget *previewTab;
    QVBoxLayout *verticalLayout_previewTab;
    QGroupBox *previewScalingGroup;
    QFormLayout *formLayoutPreviewScaling;
    QLabel *labelBoxSize;
    QWidget *boxSizeContainer;
    QHBoxLayout *boxSizeLayout;
    QSlider *boxSize;
    QLabel *boxSizeValue;
    QGroupBox *borderSettingsGroup;
    QFormLayout *formLayoutBorderSettings;
    QLabel *labelBorderWidth;
    QWidget *borderWidthContainer;
    QHBoxLayout *borderWidthLayout;
    QSlider *previewBorderWidth;
    QLabel *previewBorderWidthValue;
    QLabel *labelBorderColor;
    QPushButton *previewBorderColor;
    QLabel *labelBorderRadius;
    QWidget *borderRadiusContainer;
    QHBoxLayout *borderRadiusLayout;
    QSlider *previewBorderRadius;
    QLabel *previewBorderRadiusValue;
    QSpacerItem *verticalSpacerPreviewTab;
    QWidget *timestampTab;
    QVBoxLayout *verticalLayout_timestampTab;
    QGroupBox *fontSettingsGroup;
    QFormLayout *formLayoutFontSettings;
    QLabel *labelFontSizeScale;
    QWidget *fontSizeScaleContainer;
    QHBoxLayout *fontSizeScaleLayout;
    QSlider *fontSizeScale;
    QLabel *fontSizeScaleValue;
    QLabel *labelTextCol;
    QPushButton *textColor;
    QGroupBox *backgroundBorderGroup;
    QFormLayout *formLayoutBackgroundBorder;
    QLabel *labelTSBgColor;
    QPushButton *timestampBackgroundColor;
    QLabel *labelTSBorderWidth;
    QWidget *timestampBorderWidthContainer;
    QHBoxLayout *timestampBorderWidthLayout;
    QSlider *timestampBorderWidth;
    QLabel *timestampBorderWidthValue;
    QLabel *labelTSBorderRadius;
    QWidget *timestampBorderRadiusContainer;
    QHBoxLayout *timestampBorderRadiusLayout;
    QSlider *timestampBorderRadius;
    QLabel *timestampBorderRadiusValue;
    QLabel *labelTSBorderColor;
    QPushButton *timestampBorderColor;
    QGroupBox *spacingInsideGroup;
    QFormLayout *formLayoutSpacingInside;
    QLabel *labelPaddingY;
    QWidget *paddingYContainer;
    QHBoxLayout *paddingYLayout;
    QSlider *paddingY;
    QLabel *paddingYValue;
    QLabel *labelPaddingX;
    QWidget *paddingXContainer;
    QHBoxLayout *paddingXLayout;
    QSlider *paddingX;
    QLabel *paddingXValue;
    QGroupBox *spacingOutsideGroup;
    QFormLayout *formLayoutSpacingOutside;
    QLabel *labelTopMargin;
    QWidget *topMarginContainer;
    QHBoxLayout *topMarginLayout;
    QSlider *topMargin;
    QLabel *topMarginValue;
    QLabel *labelBottomMargin;
    QWidget *bottomMarginContainer;
    QHBoxLayout *bottomMarginLayout;
    QSlider *bottomMargin;
    QLabel *bottomMarginValue;
    QSpacerItem *verticalSpacerTimestampTab;
    QWidget *behaviourTab;
    QVBoxLayout *verticalLayout_behaviourTab;
    QGroupBox *behaviourGroup;
    QFormLayout *formLayoutB;
    QCheckBox *interactivePreview;
    QLabel *interactivePreviewDesc;
    QCheckBox *handCursorOnHover;
    QLabel *labelShowDelay;
    QWidget *showDelayContainer;
    QHBoxLayout *showDelayLayout;
    QSlider *showDelay;
    QLabel *showDelayValue;

    void setupUi(QWidget *SPrefsSeekbarPreview)
    {
        if (SPrefsSeekbarPreview->objectName().isEmpty())
            SPrefsSeekbarPreview->setObjectName(QString::fromUtf8("SPrefsSeekbarPreview"));
        SPrefsSeekbarPreview->resize(682, 679);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SPrefsSeekbarPreview->sizePolicy().hasHeightForWidth());
        SPrefsSeekbarPreview->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(SPrefsSeekbarPreview);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(SPrefsSeekbarPreview);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::North);
        generalTab = new QWidget();
        generalTab->setObjectName(QString::fromUtf8("generalTab"));
        verticalLayout_generalTab = new QVBoxLayout(generalTab);
        verticalLayout_generalTab->setObjectName(QString::fromUtf8("verticalLayout_generalTab"));
        generalGroup = new QGroupBox(generalTab);
        generalGroup->setObjectName(QString::fromUtf8("generalGroup"));
        verticalLayoutGeneral = new QVBoxLayout(generalGroup);
        verticalLayoutGeneral->setObjectName(QString::fromUtf8("verticalLayoutGeneral"));
        enableSeekbarPreview = new QCheckBox(generalGroup);
        enableSeekbarPreview->setObjectName(QString::fromUtf8("enableSeekbarPreview"));
        enableSeekbarPreview->setChecked(false);

        verticalLayoutGeneral->addWidget(enableSeekbarPreview);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        resetToDefaults = new QPushButton(generalGroup);
        resetToDefaults->setObjectName(QString::fromUtf8("resetToDefaults"));

        hboxLayout->addWidget(resetToDefaults);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);


        verticalLayoutGeneral->addLayout(hboxLayout);

        spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayoutGeneral->addItem(spacerItem1);


        verticalLayout_generalTab->addWidget(generalGroup);

        tabWidget->addTab(generalTab, QString());
        frameTab = new QWidget();
        frameTab->setObjectName(QString::fromUtf8("frameTab"));
        verticalLayout_frameTab = new QVBoxLayout(frameTab);
        verticalLayout_frameTab->setObjectName(QString::fromUtf8("verticalLayout_frameTab"));
        frameExtractionGroup = new QGroupBox(frameTab);
        frameExtractionGroup->setObjectName(QString::fromUtf8("frameExtractionGroup"));
        formLayoutFE = new QFormLayout(frameExtractionGroup);
        formLayoutFE->setObjectName(QString::fromUtf8("formLayoutFE"));
        labelSeekMode = new QLabel(frameExtractionGroup);
        labelSeekMode->setObjectName(QString::fromUtf8("labelSeekMode"));

        formLayoutFE->setWidget(0, QFormLayout::LabelRole, labelSeekMode);

        seekModeContainer = new QWidget(frameExtractionGroup);
        seekModeContainer->setObjectName(QString::fromUtf8("seekModeContainer"));
        seekModeLayout = new QVBoxLayout(seekModeContainer);
        seekModeLayout->setObjectName(QString::fromUtf8("seekModeLayout"));
        seekModeLayout->setContentsMargins(0, 0, 0, 0);
        seekModeExact = new QRadioButton(seekModeContainer);
        seekModeExact->setObjectName(QString::fromUtf8("seekModeExact"));

        seekModeLayout->addWidget(seekModeExact);

        seekModeExactDesc = new QLabel(seekModeContainer);
        seekModeExactDesc->setObjectName(QString::fromUtf8("seekModeExactDesc"));
        seekModeExactDesc->setWordWrap(true);

        seekModeLayout->addWidget(seekModeExactDesc);

        seekModeIframe = new QRadioButton(seekModeContainer);
        seekModeIframe->setObjectName(QString::fromUtf8("seekModeIframe"));

        seekModeLayout->addWidget(seekModeIframe);

        seekModeIframeDesc = new QLabel(seekModeContainer);
        seekModeIframeDesc->setObjectName(QString::fromUtf8("seekModeIframeDesc"));
        seekModeIframeDesc->setWordWrap(true);

        seekModeLayout->addWidget(seekModeIframeDesc);

        seekModeDynamic = new QRadioButton(seekModeContainer);
        seekModeDynamic->setObjectName(QString::fromUtf8("seekModeDynamic"));

        seekModeLayout->addWidget(seekModeDynamic);

        dynamicSeekContainer = new QWidget(seekModeContainer);
        dynamicSeekContainer->setObjectName(QString::fromUtf8("dynamicSeekContainer"));
        dynamicSeekLayout = new QHBoxLayout(dynamicSeekContainer);
        dynamicSeekLayout->setObjectName(QString::fromUtf8("dynamicSeekLayout"));
        dynamicSeekLayout->setContentsMargins(0, 0, 0, 0);
        dynamicSeekPrefix = new QLabel(dynamicSeekContainer);
        dynamicSeekPrefix->setObjectName(QString::fromUtf8("dynamicSeekPrefix"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dynamicSeekPrefix->sizePolicy().hasHeightForWidth());
        dynamicSeekPrefix->setSizePolicy(sizePolicy1);

        dynamicSeekLayout->addWidget(dynamicSeekPrefix);

        dynamicSeekThreshold = new QSpinBox(dynamicSeekContainer);
        dynamicSeekThreshold->setObjectName(QString::fromUtf8("dynamicSeekThreshold"));
        dynamicSeekThreshold->setMinimum(1);
        dynamicSeekThreshold->setMaximum(60);
        dynamicSeekThreshold->setValue(10);
        dynamicSeekThreshold->setMaximumWidth(50);

        dynamicSeekLayout->addWidget(dynamicSeekThreshold);

        dynamicSeekSuffix = new QLabel(dynamicSeekContainer);
        dynamicSeekSuffix->setObjectName(QString::fromUtf8("dynamicSeekSuffix"));

        dynamicSeekLayout->addWidget(dynamicSeekSuffix);


        seekModeLayout->addWidget(dynamicSeekContainer);


        formLayoutFE->setWidget(0, QFormLayout::FieldRole, seekModeContainer);

        labelCacheLimit = new QLabel(frameExtractionGroup);
        labelCacheLimit->setObjectName(QString::fromUtf8("labelCacheLimit"));

        formLayoutFE->setWidget(1, QFormLayout::LabelRole, labelCacheLimit);

        cacheLimitContainer = new QWidget(frameExtractionGroup);
        cacheLimitContainer->setObjectName(QString::fromUtf8("cacheLimitContainer"));
        cacheLimitLayout = new QHBoxLayout(cacheLimitContainer);
        cacheLimitLayout->setObjectName(QString::fromUtf8("cacheLimitLayout"));
        cacheLimitLayout->setContentsMargins(0, 0, 0, 0);
        cacheLimit = new QSlider(cacheLimitContainer);
        cacheLimit->setObjectName(QString::fromUtf8("cacheLimit"));
        cacheLimit->setMinimum(10);
        cacheLimit->setMaximum(300);
        cacheLimit->setSingleStep(10);
        cacheLimit->setPageStep(10);
        cacheLimit->setTickPosition(QSlider::TicksBelow);
        cacheLimit->setTickInterval(10);
        cacheLimit->setOrientation(Qt::Horizontal);

        cacheLimitLayout->addWidget(cacheLimit);

        cacheLimitValue = new QLabel(cacheLimitContainer);
        cacheLimitValue->setObjectName(QString::fromUtf8("cacheLimitValue"));
        cacheLimitValue->setMinimumSize(QSize(52, 0));
        cacheLimitValue->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        cacheLimitLayout->addWidget(cacheLimitValue);


        formLayoutFE->setWidget(1, QFormLayout::FieldRole, cacheLimitContainer);

        labelFrameRes = new QLabel(frameExtractionGroup);
        labelFrameRes->setObjectName(QString::fromUtf8("labelFrameRes"));

        formLayoutFE->setWidget(2, QFormLayout::LabelRole, labelFrameRes);

        frameResolutionContainer = new QWidget(frameExtractionGroup);
        frameResolutionContainer->setObjectName(QString::fromUtf8("frameResolutionContainer"));
        frameResolutionLayout = new QVBoxLayout(frameResolutionContainer);
        frameResolutionLayout->setObjectName(QString::fromUtf8("frameResolutionLayout"));
        frameResolutionLayout->setContentsMargins(0, 0, 0, 0);
        frameResolutionRowWidget = new QWidget(frameResolutionContainer);
        frameResolutionRowWidget->setObjectName(QString::fromUtf8("frameResolutionRowWidget"));
        frameResolutionRow = new QHBoxLayout(frameResolutionRowWidget);
        frameResolutionRow->setObjectName(QString::fromUtf8("frameResolutionRow"));
        frameResolutionRow->setContentsMargins(0, 0, 0, 0);
        frameResolution = new QSlider(frameResolutionRowWidget);
        frameResolution->setObjectName(QString::fromUtf8("frameResolution"));
        frameResolution->setMinimum(0);
        frameResolution->setMaximum(5);
        frameResolution->setTickPosition(QSlider::TicksBelow);
        frameResolution->setTickInterval(1);
        frameResolution->setOrientation(Qt::Horizontal);

        frameResolutionRow->addWidget(frameResolution);

        frameResolutionValue = new QLabel(frameResolutionRowWidget);
        frameResolutionValue->setObjectName(QString::fromUtf8("frameResolutionValue"));
        frameResolutionValue->setMinimumSize(QSize(52, 0));
        frameResolutionValue->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        frameResolutionRow->addWidget(frameResolutionValue);


        frameResolutionLayout->addWidget(frameResolutionRowWidget);


        formLayoutFE->setWidget(2, QFormLayout::FieldRole, frameResolutionContainer);


        verticalLayout_frameTab->addWidget(frameExtractionGroup);

        tabWidget->addTab(frameTab, QString());
        previewTab = new QWidget();
        previewTab->setObjectName(QString::fromUtf8("previewTab"));
        verticalLayout_previewTab = new QVBoxLayout(previewTab);
        verticalLayout_previewTab->setObjectName(QString::fromUtf8("verticalLayout_previewTab"));
        previewScalingGroup = new QGroupBox(previewTab);
        previewScalingGroup->setObjectName(QString::fromUtf8("previewScalingGroup"));
        formLayoutPreviewScaling = new QFormLayout(previewScalingGroup);
        formLayoutPreviewScaling->setObjectName(QString::fromUtf8("formLayoutPreviewScaling"));
        labelBoxSize = new QLabel(previewScalingGroup);
        labelBoxSize->setObjectName(QString::fromUtf8("labelBoxSize"));

        formLayoutPreviewScaling->setWidget(0, QFormLayout::LabelRole, labelBoxSize);

        boxSizeContainer = new QWidget(previewScalingGroup);
        boxSizeContainer->setObjectName(QString::fromUtf8("boxSizeContainer"));
        boxSizeLayout = new QHBoxLayout(boxSizeContainer);
        boxSizeLayout->setObjectName(QString::fromUtf8("boxSizeLayout"));
        boxSizeLayout->setContentsMargins(0, 0, 0, 0);
        boxSize = new QSlider(boxSizeContainer);
        boxSize->setObjectName(QString::fromUtf8("boxSize"));
        boxSize->setMinimum(100);
        boxSize->setMaximum(600);
        boxSize->setSingleStep(10);
        boxSize->setPageStep(50);
        boxSize->setTickPosition(QSlider::TicksBelow);
        boxSize->setTickInterval(50);
        boxSize->setOrientation(Qt::Horizontal);

        boxSizeLayout->addWidget(boxSize);

        boxSizeValue = new QLabel(boxSizeContainer);
        boxSizeValue->setObjectName(QString::fromUtf8("boxSizeValue"));
        boxSizeValue->setMinimumSize(QSize(52, 0));
        boxSizeValue->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        boxSizeLayout->addWidget(boxSizeValue);


        formLayoutPreviewScaling->setWidget(0, QFormLayout::FieldRole, boxSizeContainer);


        verticalLayout_previewTab->addWidget(previewScalingGroup);

        borderSettingsGroup = new QGroupBox(previewTab);
        borderSettingsGroup->setObjectName(QString::fromUtf8("borderSettingsGroup"));
        formLayoutBorderSettings = new QFormLayout(borderSettingsGroup);
        formLayoutBorderSettings->setObjectName(QString::fromUtf8("formLayoutBorderSettings"));
        labelBorderWidth = new QLabel(borderSettingsGroup);
        labelBorderWidth->setObjectName(QString::fromUtf8("labelBorderWidth"));

        formLayoutBorderSettings->setWidget(0, QFormLayout::LabelRole, labelBorderWidth);

        borderWidthContainer = new QWidget(borderSettingsGroup);
        borderWidthContainer->setObjectName(QString::fromUtf8("borderWidthContainer"));
        borderWidthLayout = new QHBoxLayout(borderWidthContainer);
        borderWidthLayout->setObjectName(QString::fromUtf8("borderWidthLayout"));
        borderWidthLayout->setContentsMargins(0, 0, 0, 0);
        previewBorderWidth = new QSlider(borderWidthContainer);
        previewBorderWidth->setObjectName(QString::fromUtf8("previewBorderWidth"));
        previewBorderWidth->setMinimum(0);
        previewBorderWidth->setMaximum(100);
        previewBorderWidth->setTickPosition(QSlider::TicksBelow);
        previewBorderWidth->setTickInterval(10);
        previewBorderWidth->setOrientation(Qt::Horizontal);

        borderWidthLayout->addWidget(previewBorderWidth);

        previewBorderWidthValue = new QLabel(borderWidthContainer);
        previewBorderWidthValue->setObjectName(QString::fromUtf8("previewBorderWidthValue"));
        previewBorderWidthValue->setMinimumSize(QSize(52, 0));
        previewBorderWidthValue->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        borderWidthLayout->addWidget(previewBorderWidthValue);


        formLayoutBorderSettings->setWidget(0, QFormLayout::FieldRole, borderWidthContainer);

        labelBorderColor = new QLabel(borderSettingsGroup);
        labelBorderColor->setObjectName(QString::fromUtf8("labelBorderColor"));

        formLayoutBorderSettings->setWidget(1, QFormLayout::LabelRole, labelBorderColor);

        previewBorderColor = new QPushButton(borderSettingsGroup);
        previewBorderColor->setObjectName(QString::fromUtf8("previewBorderColor"));

        formLayoutBorderSettings->setWidget(1, QFormLayout::FieldRole, previewBorderColor);

        labelBorderRadius = new QLabel(borderSettingsGroup);
        labelBorderRadius->setObjectName(QString::fromUtf8("labelBorderRadius"));

        formLayoutBorderSettings->setWidget(2, QFormLayout::LabelRole, labelBorderRadius);

        borderRadiusContainer = new QWidget(borderSettingsGroup);
        borderRadiusContainer->setObjectName(QString::fromUtf8("borderRadiusContainer"));
        borderRadiusLayout = new QHBoxLayout(borderRadiusContainer);
        borderRadiusLayout->setObjectName(QString::fromUtf8("borderRadiusLayout"));
        borderRadiusLayout->setContentsMargins(0, 0, 0, 0);
        previewBorderRadius = new QSlider(borderRadiusContainer);
        previewBorderRadius->setObjectName(QString::fromUtf8("previewBorderRadius"));
        previewBorderRadius->setMinimum(0);
        previewBorderRadius->setMaximum(200);
        previewBorderRadius->setTickPosition(QSlider::TicksBelow);
        previewBorderRadius->setTickInterval(10);
        previewBorderRadius->setOrientation(Qt::Horizontal);

        borderRadiusLayout->addWidget(previewBorderRadius);

        previewBorderRadiusValue = new QLabel(borderRadiusContainer);
        previewBorderRadiusValue->setObjectName(QString::fromUtf8("previewBorderRadiusValue"));
        previewBorderRadiusValue->setMinimumSize(QSize(52, 0));
        previewBorderRadiusValue->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        borderRadiusLayout->addWidget(previewBorderRadiusValue);


        formLayoutBorderSettings->setWidget(2, QFormLayout::FieldRole, borderRadiusContainer);


        verticalLayout_previewTab->addWidget(borderSettingsGroup);

        verticalSpacerPreviewTab = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_previewTab->addItem(verticalSpacerPreviewTab);

        tabWidget->addTab(previewTab, QString());
        timestampTab = new QWidget();
        timestampTab->setObjectName(QString::fromUtf8("timestampTab"));
        verticalLayout_timestampTab = new QVBoxLayout(timestampTab);
        verticalLayout_timestampTab->setObjectName(QString::fromUtf8("verticalLayout_timestampTab"));
        fontSettingsGroup = new QGroupBox(timestampTab);
        fontSettingsGroup->setObjectName(QString::fromUtf8("fontSettingsGroup"));
        formLayoutFontSettings = new QFormLayout(fontSettingsGroup);
        formLayoutFontSettings->setObjectName(QString::fromUtf8("formLayoutFontSettings"));
        labelFontSizeScale = new QLabel(fontSettingsGroup);
        labelFontSizeScale->setObjectName(QString::fromUtf8("labelFontSizeScale"));

        formLayoutFontSettings->setWidget(0, QFormLayout::LabelRole, labelFontSizeScale);

        fontSizeScaleContainer = new QWidget(fontSettingsGroup);
        fontSizeScaleContainer->setObjectName(QString::fromUtf8("fontSizeScaleContainer"));
        fontSizeScaleLayout = new QHBoxLayout(fontSizeScaleContainer);
        fontSizeScaleLayout->setObjectName(QString::fromUtf8("fontSizeScaleLayout"));
        fontSizeScaleLayout->setContentsMargins(0, 0, 0, 0);
        fontSizeScale = new QSlider(fontSizeScaleContainer);
        fontSizeScale->setObjectName(QString::fromUtf8("fontSizeScale"));
        fontSizeScale->setMinimum(0);
        fontSizeScale->setMaximum(40);
        fontSizeScale->setTickPosition(QSlider::TicksBelow);
        fontSizeScale->setTickInterval(1);
        fontSizeScale->setOrientation(Qt::Horizontal);

        fontSizeScaleLayout->addWidget(fontSizeScale);

        fontSizeScaleValue = new QLabel(fontSizeScaleContainer);
        fontSizeScaleValue->setObjectName(QString::fromUtf8("fontSizeScaleValue"));
        fontSizeScaleValue->setMinimumSize(QSize(52, 0));
        fontSizeScaleValue->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        fontSizeScaleLayout->addWidget(fontSizeScaleValue);


        formLayoutFontSettings->setWidget(0, QFormLayout::FieldRole, fontSizeScaleContainer);

        labelTextCol = new QLabel(fontSettingsGroup);
        labelTextCol->setObjectName(QString::fromUtf8("labelTextCol"));

        formLayoutFontSettings->setWidget(1, QFormLayout::LabelRole, labelTextCol);

        textColor = new QPushButton(fontSettingsGroup);
        textColor->setObjectName(QString::fromUtf8("textColor"));

        formLayoutFontSettings->setWidget(1, QFormLayout::FieldRole, textColor);


        verticalLayout_timestampTab->addWidget(fontSettingsGroup);

        backgroundBorderGroup = new QGroupBox(timestampTab);
        backgroundBorderGroup->setObjectName(QString::fromUtf8("backgroundBorderGroup"));
        formLayoutBackgroundBorder = new QFormLayout(backgroundBorderGroup);
        formLayoutBackgroundBorder->setObjectName(QString::fromUtf8("formLayoutBackgroundBorder"));
        labelTSBgColor = new QLabel(backgroundBorderGroup);
        labelTSBgColor->setObjectName(QString::fromUtf8("labelTSBgColor"));

        formLayoutBackgroundBorder->setWidget(0, QFormLayout::LabelRole, labelTSBgColor);

        timestampBackgroundColor = new QPushButton(backgroundBorderGroup);
        timestampBackgroundColor->setObjectName(QString::fromUtf8("timestampBackgroundColor"));

        formLayoutBackgroundBorder->setWidget(0, QFormLayout::FieldRole, timestampBackgroundColor);

        labelTSBorderWidth = new QLabel(backgroundBorderGroup);
        labelTSBorderWidth->setObjectName(QString::fromUtf8("labelTSBorderWidth"));

        formLayoutBackgroundBorder->setWidget(1, QFormLayout::LabelRole, labelTSBorderWidth);

        timestampBorderWidthContainer = new QWidget(backgroundBorderGroup);
        timestampBorderWidthContainer->setObjectName(QString::fromUtf8("timestampBorderWidthContainer"));
        timestampBorderWidthLayout = new QHBoxLayout(timestampBorderWidthContainer);
        timestampBorderWidthLayout->setObjectName(QString::fromUtf8("timestampBorderWidthLayout"));
        timestampBorderWidthLayout->setContentsMargins(0, 0, 0, 0);
        timestampBorderWidth = new QSlider(timestampBorderWidthContainer);
        timestampBorderWidth->setObjectName(QString::fromUtf8("timestampBorderWidth"));
        timestampBorderWidth->setMinimum(0);
        timestampBorderWidth->setMaximum(20);
        timestampBorderWidth->setTickPosition(QSlider::TicksBelow);
        timestampBorderWidth->setTickInterval(1);
        timestampBorderWidth->setOrientation(Qt::Horizontal);

        timestampBorderWidthLayout->addWidget(timestampBorderWidth);

        timestampBorderWidthValue = new QLabel(timestampBorderWidthContainer);
        timestampBorderWidthValue->setObjectName(QString::fromUtf8("timestampBorderWidthValue"));
        timestampBorderWidthValue->setMinimumSize(QSize(52, 0));
        timestampBorderWidthValue->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        timestampBorderWidthLayout->addWidget(timestampBorderWidthValue);


        formLayoutBackgroundBorder->setWidget(1, QFormLayout::FieldRole, timestampBorderWidthContainer);

        labelTSBorderRadius = new QLabel(backgroundBorderGroup);
        labelTSBorderRadius->setObjectName(QString::fromUtf8("labelTSBorderRadius"));

        formLayoutBackgroundBorder->setWidget(2, QFormLayout::LabelRole, labelTSBorderRadius);

        timestampBorderRadiusContainer = new QWidget(backgroundBorderGroup);
        timestampBorderRadiusContainer->setObjectName(QString::fromUtf8("timestampBorderRadiusContainer"));
        timestampBorderRadiusLayout = new QHBoxLayout(timestampBorderRadiusContainer);
        timestampBorderRadiusLayout->setObjectName(QString::fromUtf8("timestampBorderRadiusLayout"));
        timestampBorderRadiusLayout->setContentsMargins(0, 0, 0, 0);
        timestampBorderRadius = new QSlider(timestampBorderRadiusContainer);
        timestampBorderRadius->setObjectName(QString::fromUtf8("timestampBorderRadius"));
        timestampBorderRadius->setMinimum(0);
        timestampBorderRadius->setMaximum(20);
        timestampBorderRadius->setTickPosition(QSlider::TicksBelow);
        timestampBorderRadius->setTickInterval(1);
        timestampBorderRadius->setOrientation(Qt::Horizontal);

        timestampBorderRadiusLayout->addWidget(timestampBorderRadius);

        timestampBorderRadiusValue = new QLabel(timestampBorderRadiusContainer);
        timestampBorderRadiusValue->setObjectName(QString::fromUtf8("timestampBorderRadiusValue"));
        timestampBorderRadiusValue->setMinimumSize(QSize(52, 0));
        timestampBorderRadiusValue->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        timestampBorderRadiusLayout->addWidget(timestampBorderRadiusValue);


        formLayoutBackgroundBorder->setWidget(2, QFormLayout::FieldRole, timestampBorderRadiusContainer);

        labelTSBorderColor = new QLabel(backgroundBorderGroup);
        labelTSBorderColor->setObjectName(QString::fromUtf8("labelTSBorderColor"));

        formLayoutBackgroundBorder->setWidget(3, QFormLayout::LabelRole, labelTSBorderColor);

        timestampBorderColor = new QPushButton(backgroundBorderGroup);
        timestampBorderColor->setObjectName(QString::fromUtf8("timestampBorderColor"));

        formLayoutBackgroundBorder->setWidget(3, QFormLayout::FieldRole, timestampBorderColor);


        verticalLayout_timestampTab->addWidget(backgroundBorderGroup);

        spacingInsideGroup = new QGroupBox(timestampTab);
        spacingInsideGroup->setObjectName(QString::fromUtf8("spacingInsideGroup"));
        formLayoutSpacingInside = new QFormLayout(spacingInsideGroup);
        formLayoutSpacingInside->setObjectName(QString::fromUtf8("formLayoutSpacingInside"));
        labelPaddingY = new QLabel(spacingInsideGroup);
        labelPaddingY->setObjectName(QString::fromUtf8("labelPaddingY"));

        formLayoutSpacingInside->setWidget(0, QFormLayout::LabelRole, labelPaddingY);

        paddingYContainer = new QWidget(spacingInsideGroup);
        paddingYContainer->setObjectName(QString::fromUtf8("paddingYContainer"));
        paddingYLayout = new QHBoxLayout(paddingYContainer);
        paddingYLayout->setObjectName(QString::fromUtf8("paddingYLayout"));
        paddingYLayout->setContentsMargins(0, 0, 0, 0);
        paddingY = new QSlider(paddingYContainer);
        paddingY->setObjectName(QString::fromUtf8("paddingY"));
        paddingY->setMinimum(0);
        paddingY->setMaximum(100);
        paddingY->setTickPosition(QSlider::TicksBelow);
        paddingY->setTickInterval(5);
        paddingY->setOrientation(Qt::Horizontal);

        paddingYLayout->addWidget(paddingY);

        paddingYValue = new QLabel(paddingYContainer);
        paddingYValue->setObjectName(QString::fromUtf8("paddingYValue"));
        paddingYValue->setMinimumSize(QSize(52, 0));
        paddingYValue->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        paddingYLayout->addWidget(paddingYValue);


        formLayoutSpacingInside->setWidget(0, QFormLayout::FieldRole, paddingYContainer);

        labelPaddingX = new QLabel(spacingInsideGroup);
        labelPaddingX->setObjectName(QString::fromUtf8("labelPaddingX"));

        formLayoutSpacingInside->setWidget(1, QFormLayout::LabelRole, labelPaddingX);

        paddingXContainer = new QWidget(spacingInsideGroup);
        paddingXContainer->setObjectName(QString::fromUtf8("paddingXContainer"));
        paddingXLayout = new QHBoxLayout(paddingXContainer);
        paddingXLayout->setObjectName(QString::fromUtf8("paddingXLayout"));
        paddingXLayout->setContentsMargins(0, 0, 0, 0);
        paddingX = new QSlider(paddingXContainer);
        paddingX->setObjectName(QString::fromUtf8("paddingX"));
        paddingX->setMinimum(0);
        paddingX->setMaximum(100);
        paddingX->setTickPosition(QSlider::TicksBelow);
        paddingX->setTickInterval(5);
        paddingX->setOrientation(Qt::Horizontal);

        paddingXLayout->addWidget(paddingX);

        paddingXValue = new QLabel(paddingXContainer);
        paddingXValue->setObjectName(QString::fromUtf8("paddingXValue"));
        paddingXValue->setMinimumSize(QSize(52, 0));
        paddingXValue->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        paddingXLayout->addWidget(paddingXValue);


        formLayoutSpacingInside->setWidget(1, QFormLayout::FieldRole, paddingXContainer);


        verticalLayout_timestampTab->addWidget(spacingInsideGroup);

        spacingOutsideGroup = new QGroupBox(timestampTab);
        spacingOutsideGroup->setObjectName(QString::fromUtf8("spacingOutsideGroup"));
        formLayoutSpacingOutside = new QFormLayout(spacingOutsideGroup);
        formLayoutSpacingOutside->setObjectName(QString::fromUtf8("formLayoutSpacingOutside"));
        labelTopMargin = new QLabel(spacingOutsideGroup);
        labelTopMargin->setObjectName(QString::fromUtf8("labelTopMargin"));

        formLayoutSpacingOutside->setWidget(0, QFormLayout::LabelRole, labelTopMargin);

        topMarginContainer = new QWidget(spacingOutsideGroup);
        topMarginContainer->setObjectName(QString::fromUtf8("topMarginContainer"));
        topMarginLayout = new QHBoxLayout(topMarginContainer);
        topMarginLayout->setObjectName(QString::fromUtf8("topMarginLayout"));
        topMarginLayout->setContentsMargins(0, 0, 0, 0);
        topMargin = new QSlider(topMarginContainer);
        topMargin->setObjectName(QString::fromUtf8("topMargin"));
        topMargin->setMinimum(0);
        topMargin->setMaximum(80);
        topMargin->setTickPosition(QSlider::TicksBelow);
        topMargin->setTickInterval(4);
        topMargin->setOrientation(Qt::Horizontal);

        topMarginLayout->addWidget(topMargin);

        topMarginValue = new QLabel(topMarginContainer);
        topMarginValue->setObjectName(QString::fromUtf8("topMarginValue"));
        topMarginValue->setMinimumSize(QSize(52, 0));
        topMarginValue->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        topMarginLayout->addWidget(topMarginValue);


        formLayoutSpacingOutside->setWidget(0, QFormLayout::FieldRole, topMarginContainer);

        labelBottomMargin = new QLabel(spacingOutsideGroup);
        labelBottomMargin->setObjectName(QString::fromUtf8("labelBottomMargin"));

        formLayoutSpacingOutside->setWidget(1, QFormLayout::LabelRole, labelBottomMargin);

        bottomMarginContainer = new QWidget(spacingOutsideGroup);
        bottomMarginContainer->setObjectName(QString::fromUtf8("bottomMarginContainer"));
        bottomMarginLayout = new QHBoxLayout(bottomMarginContainer);
        bottomMarginLayout->setObjectName(QString::fromUtf8("bottomMarginLayout"));
        bottomMarginLayout->setContentsMargins(0, 0, 0, 0);
        bottomMargin = new QSlider(bottomMarginContainer);
        bottomMargin->setObjectName(QString::fromUtf8("bottomMargin"));
        bottomMargin->setMinimum(0);
        bottomMargin->setMaximum(80);
        bottomMargin->setTickPosition(QSlider::TicksBelow);
        bottomMargin->setTickInterval(4);
        bottomMargin->setOrientation(Qt::Horizontal);

        bottomMarginLayout->addWidget(bottomMargin);

        bottomMarginValue = new QLabel(bottomMarginContainer);
        bottomMarginValue->setObjectName(QString::fromUtf8("bottomMarginValue"));
        bottomMarginValue->setMinimumSize(QSize(52, 0));
        bottomMarginValue->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        bottomMarginLayout->addWidget(bottomMarginValue);


        formLayoutSpacingOutside->setWidget(1, QFormLayout::FieldRole, bottomMarginContainer);


        verticalLayout_timestampTab->addWidget(spacingOutsideGroup);

        verticalSpacerTimestampTab = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_timestampTab->addItem(verticalSpacerTimestampTab);

        tabWidget->addTab(timestampTab, QString());
        behaviourTab = new QWidget();
        behaviourTab->setObjectName(QString::fromUtf8("behaviourTab"));
        verticalLayout_behaviourTab = new QVBoxLayout(behaviourTab);
        verticalLayout_behaviourTab->setObjectName(QString::fromUtf8("verticalLayout_behaviourTab"));
        behaviourGroup = new QGroupBox(behaviourTab);
        behaviourGroup->setObjectName(QString::fromUtf8("behaviourGroup"));
        formLayoutB = new QFormLayout(behaviourGroup);
        formLayoutB->setObjectName(QString::fromUtf8("formLayoutB"));
        interactivePreview = new QCheckBox(behaviourGroup);
        interactivePreview->setObjectName(QString::fromUtf8("interactivePreview"));

        formLayoutB->setWidget(0, QFormLayout::LabelRole, interactivePreview);

        interactivePreviewDesc = new QLabel(behaviourGroup);
        interactivePreviewDesc->setObjectName(QString::fromUtf8("interactivePreviewDesc"));
        interactivePreviewDesc->setWordWrap(false);

        formLayoutB->setWidget(1, QFormLayout::LabelRole, interactivePreviewDesc);

        handCursorOnHover = new QCheckBox(behaviourGroup);
        handCursorOnHover->setObjectName(QString::fromUtf8("handCursorOnHover"));

        formLayoutB->setWidget(2, QFormLayout::LabelRole, handCursorOnHover);

        labelShowDelay = new QLabel(behaviourGroup);
        labelShowDelay->setObjectName(QString::fromUtf8("labelShowDelay"));

        formLayoutB->setWidget(3, QFormLayout::LabelRole, labelShowDelay);

        showDelayContainer = new QWidget(behaviourGroup);
        showDelayContainer->setObjectName(QString::fromUtf8("showDelayContainer"));
        showDelayLayout = new QHBoxLayout(showDelayContainer);
        showDelayLayout->setObjectName(QString::fromUtf8("showDelayLayout"));
        showDelayLayout->setContentsMargins(0, 0, 0, 0);
        showDelay = new QSlider(showDelayContainer);
        showDelay->setObjectName(QString::fromUtf8("showDelay"));
        showDelay->setMinimum(0);
        showDelay->setMaximum(3000);
        showDelay->setSingleStep(50);
        showDelay->setPageStep(250);
        showDelay->setTickPosition(QSlider::TicksBelow);
        showDelay->setTickInterval(50);
        showDelay->setOrientation(Qt::Horizontal);
        showDelay->setValue(0);

        showDelayLayout->addWidget(showDelay);

        showDelayValue = new QLabel(showDelayContainer);
        showDelayValue->setObjectName(QString::fromUtf8("showDelayValue"));
        showDelayValue->setMinimumSize(QSize(68, 0));
        showDelayValue->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        showDelayLayout->addWidget(showDelayValue);


        formLayoutB->setWidget(3, QFormLayout::FieldRole, showDelayContainer);


        verticalLayout_behaviourTab->addWidget(behaviourGroup);

        tabWidget->addTab(behaviourTab, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(SPrefsSeekbarPreview);

        QMetaObject::connectSlotsByName(SPrefsSeekbarPreview);
    } // setupUi

    void retranslateUi(QWidget *SPrefsSeekbarPreview)
    {
        SPrefsSeekbarPreview->setWindowTitle(Q_("Seekbar Preview Settings", nullptr));
        generalGroup->setTitle(Q_("General", nullptr));
        enableSeekbarPreview->setText(Q_("Enable seekbar preview", nullptr));
        resetToDefaults->setText(Q_("Reset Seekbar Preview Preferences", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(generalTab), Q_("General", nullptr));
        frameExtractionGroup->setTitle(Q_("Frame Extraction", nullptr));
        labelSeekMode->setText(Q_("Seek Mode", nullptr));
        seekModeExact->setText(Q_("Exact frame", nullptr));
        seekModeExactDesc->setText(Q_("Slower extraction; the farther the timestamp is from the previous I-frame, the longer it can take.", nullptr));
        seekModeExactDesc->setStyleSheet(Q_("color: #777777;", nullptr));
        seekModeIframe->setText(Q_("Nearest I-frame", nullptr));
        seekModeIframeDesc->setText(Q_("Faster extraction; the preview may be offset depending on the video's keyframe spacing.", nullptr));
        seekModeIframeDesc->setStyleSheet(Q_("color: #777777;", nullptr));
        seekModeDynamic->setText(Q_("Dynamic", nullptr));
        dynamicSeekPrefix->setText(Q_("Use exact seeking only when the nearest I-frame is more than", nullptr));
        dynamicSeekPrefix->setStyleSheet(Q_("color: #777777;", nullptr));
        dynamicSeekSuffix->setText(Q_("seconds away from the hovered position.", nullptr));
        dynamicSeekSuffix->setStyleSheet(Q_("color: #777777;", nullptr));
        labelCacheLimit->setText(Q_("Cache Limit (MB)", nullptr));
        labelFrameRes->setText(Q_("Frame Resolution", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(frameTab), Q_("Frame Extraction", nullptr));
        previewScalingGroup->setTitle(Q_("Preview Scaling", nullptr));
        labelBoxSize->setText(Q_("Box Size (px)", nullptr));
        borderSettingsGroup->setTitle(Q_("Border Settings", nullptr));
        labelBorderWidth->setText(Q_("Border Width (px)", nullptr));
        labelBorderColor->setText(Q_("Border Color", nullptr));
        previewBorderColor->setText(Q_("Choose Color...", nullptr));
        labelBorderRadius->setText(Q_("Border Radius (px)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(previewTab), Q_("Preview Image", nullptr));
        fontSettingsGroup->setTitle(Q_("Font Settings", nullptr));
        labelFontSizeScale->setText(Q_("Font Size Scale", nullptr));
        labelTextCol->setText(Q_("Color", nullptr));
        textColor->setText(Q_("Choose Color...", nullptr));
        backgroundBorderGroup->setTitle(Q_("Background & Border", nullptr));
        labelTSBgColor->setText(Q_("Background Color", nullptr));
        timestampBackgroundColor->setText(Q_("Choose Color...", nullptr));
        labelTSBorderWidth->setText(Q_("Border Width", nullptr));
        labelTSBorderRadius->setText(Q_("Border Radius", nullptr));
        labelTSBorderColor->setText(Q_("Border Color", nullptr));
        timestampBorderColor->setText(Q_("Choose Color...", nullptr));
        spacingInsideGroup->setTitle(Q_("Spacing (inside)", nullptr));
        labelPaddingY->setText(Q_("Padding Y", nullptr));
        labelPaddingX->setText(Q_("Padding X", nullptr));
        spacingOutsideGroup->setTitle(Q_("Spacing (outside)", nullptr));
        labelTopMargin->setText(Q_("Margin Top", nullptr));
        labelBottomMargin->setText(Q_("Margin Bottom", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(timestampTab), Q_("Timestamp", nullptr));
        behaviourGroup->setTitle(Q_("Behaviour", nullptr));
        interactivePreview->setText(Q_("Interactive Preview", nullptr));
        interactivePreviewDesc->setText(Q_("When enabled, the preview box is included in the hover area", nullptr));
        interactivePreviewDesc->setStyleSheet(Q_("color: #777777;", nullptr));
        handCursorOnHover->setText(Q_("Hand Cursor on Hover", nullptr));
        labelShowDelay->setText(Q_("Show Delay (ms)", nullptr));
        showDelayValue->setText(Q_("0 ms", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(behaviourTab), Q_("Behaviour", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SPrefsSeekbarPreview: public Ui_SPrefsSeekbarPreview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SPREFS_SEEKBAR_PREVIEW_H
