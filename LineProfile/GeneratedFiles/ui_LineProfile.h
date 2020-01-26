/********************************************************************************
** Form generated from reading UI file 'LineProfile.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINEPROFILE_H
#define UI_LINEPROFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LineProfileClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QComboBox *cmbTrendDirection;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_18;
    QCheckBox *checkBox_5;
    QLineEdit *lineEdit_5;
    QLabel *label_21;
    QComboBox *cmbScanDirection;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_19;
    QCheckBox *checkBox_6;
    QLineEdit *lineEdit_6;
    QLabel *label_22;
    QComboBox *cmbEdgeDirection;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_20;
    QCheckBox *checkBox_7;
    QLineEdit *lineEdit_7;
    QLabel *label_23;
    QSpinBox *spbSpecifiedEdge;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_8;
    QCheckBox *checkBox;
    QLineEdit *lineEdit;
    QLabel *label_16;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_15;
    QCheckBox *checkBox_2;
    QLineEdit *lineEdit_2;
    QLabel *label_17;
    QSpinBox *spbEdgeFilterWidth;
    QLabel *label_6;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_16;
    QCheckBox *checkBox_3;
    QLineEdit *lineEdit_3;
    QLabel *label_18;
    QLabel *label_20;
    QHBoxLayout *horizontalLayout_17;
    QCheckBox *checkBox_4;
    QLineEdit *lineEdit_4;
    QLabel *label_19;
    QDoubleSpinBox *dsbEdgeIntensityLowerLimit;
    QSpinBox *spbEdgeSensitivity;
    QDoubleSpinBox *dsbEdgeIntensityUpperLimit;
    QLabel *label_8;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QLabel *label_25;
    QLabel *label_24;
    QHBoxLayout *horizontalLayout_10;
    QCheckBox *checkBox_9;
    QLineEdit *lineEdit_9;
    QLabel *label_26;
    QComboBox *cmbPrimaryTarget;
    QDoubleSpinBox *dsbSegmentShift;
    QHBoxLayout *horizontalLayout_9;
    QCheckBox *checkBox_8;
    QLineEdit *lineEdit_8;
    QSpinBox *spbPrimaryTargetSpecified;
    QLabel *label_9;
    QSpinBox *spbMaxNoSegments;
    QLabel *label_10;
    QLabel *label_14;
    QHBoxLayout *horizontalLayout_11;
    QCheckBox *checkBox_10;
    QLineEdit *lineEdit_10;
    QLabel *label_13;
    QLabel *label_15;
    QLabel *label_12;
    QDoubleSpinBox *dsbSegmentOffset;
    QLabel *label_11;
    QSpinBox *spbSegmentSize;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LineProfileClass)
    {
        if (LineProfileClass->objectName().isEmpty())
            LineProfileClass->setObjectName(QString::fromUtf8("LineProfileClass"));
        LineProfileClass->resize(1228, 788);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(9);
        LineProfileClass->setFont(font);
        centralWidget = new QWidget(LineProfileClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setMinimumSize(QSize(445, 0));
        scrollArea->setMaximumSize(QSize(445, 16777215));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 443, 711));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(1);
        gridLayout_2->setContentsMargins(-1, 0, -1, -1);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(0, 24));
        label->setMaximumSize(QSize(16777215, 24));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        cmbTrendDirection = new QComboBox(groupBox);
        cmbTrendDirection->addItem(QString());
        cmbTrendDirection->addItem(QString());
        cmbTrendDirection->addItem(QString());
        cmbTrendDirection->addItem(QString());
        cmbTrendDirection->setObjectName(QString::fromUtf8("cmbTrendDirection"));
        cmbTrendDirection->setMinimumSize(QSize(100, 24));
        cmbTrendDirection->setMaximumSize(QSize(100, 24));

        gridLayout_2->addWidget(cmbTrendDirection, 0, 3, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setMinimumSize(QSize(0, 24));
        label_2->setMaximumSize(QSize(16777215, 24));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(0);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        checkBox_5 = new QCheckBox(groupBox);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setMinimumSize(QSize(16, 0));
        checkBox_5->setMaximumSize(QSize(16, 16777215));

        horizontalLayout_18->addWidget(checkBox_5);

        lineEdit_5 = new QLineEdit(groupBox);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setMinimumSize(QSize(108, 0));
        lineEdit_5->setMaximumSize(QSize(108, 16777215));
        lineEdit_5->setReadOnly(true);

        horizontalLayout_18->addWidget(lineEdit_5);


        gridLayout_2->addLayout(horizontalLayout_18, 1, 1, 1, 1);

        label_21 = new QLabel(groupBox);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_21, 1, 2, 1, 1);

        cmbScanDirection = new QComboBox(groupBox);
        cmbScanDirection->addItem(QString());
        cmbScanDirection->addItem(QString());
        cmbScanDirection->setObjectName(QString::fromUtf8("cmbScanDirection"));
        cmbScanDirection->setMinimumSize(QSize(100, 24));
        cmbScanDirection->setMaximumSize(QSize(100, 24));

        gridLayout_2->addWidget(cmbScanDirection, 1, 3, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(0, 24));
        label_3->setMaximumSize(QSize(16777215, 24));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(0);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        checkBox_6 = new QCheckBox(groupBox);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));
        checkBox_6->setMinimumSize(QSize(16, 0));
        checkBox_6->setMaximumSize(QSize(16, 16777215));

        horizontalLayout_19->addWidget(checkBox_6);

        lineEdit_6 = new QLineEdit(groupBox);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setMinimumSize(QSize(108, 0));
        lineEdit_6->setMaximumSize(QSize(108, 16777215));
        lineEdit_6->setReadOnly(true);

        horizontalLayout_19->addWidget(lineEdit_6);


        gridLayout_2->addLayout(horizontalLayout_19, 2, 1, 1, 1);

        label_22 = new QLabel(groupBox);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_22, 2, 2, 1, 1);

        cmbEdgeDirection = new QComboBox(groupBox);
        cmbEdgeDirection->addItem(QString());
        cmbEdgeDirection->addItem(QString());
        cmbEdgeDirection->addItem(QString());
        cmbEdgeDirection->setObjectName(QString::fromUtf8("cmbEdgeDirection"));
        cmbEdgeDirection->setMinimumSize(QSize(100, 24));
        cmbEdgeDirection->setMaximumSize(QSize(100, 24));

        gridLayout_2->addWidget(cmbEdgeDirection, 2, 3, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(0, 24));
        label_4->setMaximumSize(QSize(16777215, 24));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(0);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        checkBox_7 = new QCheckBox(groupBox);
        checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));
        checkBox_7->setMinimumSize(QSize(16, 0));
        checkBox_7->setMaximumSize(QSize(16, 16777215));

        horizontalLayout_20->addWidget(checkBox_7);

        lineEdit_7 = new QLineEdit(groupBox);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setMinimumSize(QSize(108, 0));
        lineEdit_7->setMaximumSize(QSize(108, 16777215));
        lineEdit_7->setReadOnly(true);

        horizontalLayout_20->addWidget(lineEdit_7);


        gridLayout_2->addLayout(horizontalLayout_20, 3, 1, 1, 1);

        label_23 = new QLabel(groupBox);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_23, 3, 2, 1, 1);

        spbSpecifiedEdge = new QSpinBox(groupBox);
        spbSpecifiedEdge->setObjectName(QString::fromUtf8("spbSpecifiedEdge"));
        spbSpecifiedEdge->setMinimumSize(QSize(100, 24));
        spbSpecifiedEdge->setMaximumSize(QSize(100, 24));
        spbSpecifiedEdge->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(spbSpecifiedEdge, 3, 3, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(1);
        gridLayout->setContentsMargins(-1, 0, -1, -1);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setMinimumSize(QSize(16, 0));
        checkBox->setMaximumSize(QSize(16, 16777215));

        horizontalLayout_8->addWidget(checkBox);

        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(108, 0));
        lineEdit->setMaximumSize(QSize(108, 16777215));
        lineEdit->setReadOnly(true);

        horizontalLayout_8->addWidget(lineEdit);


        gridLayout->addLayout(horizontalLayout_8, 0, 2, 1, 1);

        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_16, 0, 3, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        label_5->setMinimumSize(QSize(0, 24));
        label_5->setMaximumSize(QSize(16777215, 24));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(0);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        checkBox_2 = new QCheckBox(groupBox_2);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setMinimumSize(QSize(16, 0));
        checkBox_2->setMaximumSize(QSize(16, 16777215));

        horizontalLayout_15->addWidget(checkBox_2);

        lineEdit_2 = new QLineEdit(groupBox_2);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setMinimumSize(QSize(108, 0));
        lineEdit_2->setMaximumSize(QSize(108, 16777215));
        lineEdit_2->setReadOnly(true);

        horizontalLayout_15->addWidget(lineEdit_2);


        gridLayout->addLayout(horizontalLayout_15, 1, 2, 1, 1);

        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_17, 1, 3, 1, 1);

        spbEdgeFilterWidth = new QSpinBox(groupBox_2);
        spbEdgeFilterWidth->setObjectName(QString::fromUtf8("spbEdgeFilterWidth"));
        spbEdgeFilterWidth->setMinimumSize(QSize(100, 24));
        spbEdgeFilterWidth->setMaximumSize(QSize(100, 24));
        spbEdgeFilterWidth->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spbEdgeFilterWidth->setMaximum(100);
        spbEdgeFilterWidth->setValue(3);

        gridLayout->addWidget(spbEdgeFilterWidth, 1, 4, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);
        label_6->setMinimumSize(QSize(0, 24));
        label_6->setMaximumSize(QSize(16777215, 24));

        gridLayout->addWidget(label_6, 2, 0, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(0, 24));
        label_7->setMaximumSize(QSize(16777215, 24));
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_7, 2, 1, 1, 1);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(0);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        checkBox_3 = new QCheckBox(groupBox_2);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setMinimumSize(QSize(16, 0));
        checkBox_3->setMaximumSize(QSize(16, 16777215));

        horizontalLayout_16->addWidget(checkBox_3);

        lineEdit_3 = new QLineEdit(groupBox_2);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setMinimumSize(QSize(108, 0));
        lineEdit_3->setMaximumSize(QSize(108, 16777215));
        lineEdit_3->setReadOnly(true);

        horizontalLayout_16->addWidget(lineEdit_3);


        gridLayout->addLayout(horizontalLayout_16, 2, 2, 1, 1);

        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_18, 2, 3, 1, 1);

        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setMinimumSize(QSize(0, 24));
        label_20->setMaximumSize(QSize(16777215, 24));
        label_20->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_20, 3, 1, 1, 1);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(0);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        checkBox_4 = new QCheckBox(groupBox_2);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setMinimumSize(QSize(16, 0));
        checkBox_4->setMaximumSize(QSize(16, 16777215));

        horizontalLayout_17->addWidget(checkBox_4);

        lineEdit_4 = new QLineEdit(groupBox_2);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setMinimumSize(QSize(108, 0));
        lineEdit_4->setMaximumSize(QSize(108, 16777215));
        lineEdit_4->setReadOnly(true);

        horizontalLayout_17->addWidget(lineEdit_4);


        gridLayout->addLayout(horizontalLayout_17, 3, 2, 1, 1);

        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_19, 3, 3, 1, 1);

        dsbEdgeIntensityLowerLimit = new QDoubleSpinBox(groupBox_2);
        dsbEdgeIntensityLowerLimit->setObjectName(QString::fromUtf8("dsbEdgeIntensityLowerLimit"));
        dsbEdgeIntensityLowerLimit->setMinimumSize(QSize(100, 24));
        dsbEdgeIntensityLowerLimit->setMaximumSize(QSize(100, 24));
        dsbEdgeIntensityLowerLimit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dsbEdgeIntensityLowerLimit->setDecimals(3);
        dsbEdgeIntensityLowerLimit->setMaximum(255.000000000000000);
        dsbEdgeIntensityLowerLimit->setValue(100.000000000000000);

        gridLayout->addWidget(dsbEdgeIntensityLowerLimit, 3, 4, 1, 1);

        spbEdgeSensitivity = new QSpinBox(groupBox_2);
        spbEdgeSensitivity->setObjectName(QString::fromUtf8("spbEdgeSensitivity"));
        spbEdgeSensitivity->setMinimumSize(QSize(100, 24));
        spbEdgeSensitivity->setMaximumSize(QSize(100, 24));
        spbEdgeSensitivity->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spbEdgeSensitivity->setMaximum(100);
        spbEdgeSensitivity->setValue(5);

        gridLayout->addWidget(spbEdgeSensitivity, 0, 4, 1, 1);

        dsbEdgeIntensityUpperLimit = new QDoubleSpinBox(groupBox_2);
        dsbEdgeIntensityUpperLimit->setObjectName(QString::fromUtf8("dsbEdgeIntensityUpperLimit"));
        dsbEdgeIntensityUpperLimit->setMinimumSize(QSize(100, 24));
        dsbEdgeIntensityUpperLimit->setMaximumSize(QSize(100, 24));
        dsbEdgeIntensityUpperLimit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dsbEdgeIntensityUpperLimit->setDecimals(3);
        dsbEdgeIntensityUpperLimit->setMaximum(255.000000000000000);
        dsbEdgeIntensityUpperLimit->setSingleStep(1.000000000000000);
        dsbEdgeIntensityUpperLimit->setValue(255.000000000000000);

        gridLayout->addWidget(dsbEdgeIntensityUpperLimit, 2, 4, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy3);
        label_8->setMinimumSize(QSize(0, 24));
        label_8->setMaximumSize(QSize(16777215, 24));

        gridLayout->addWidget(label_8, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setVerticalSpacing(1);
        gridLayout_4->setContentsMargins(-1, 0, -1, -1);
        label_25 = new QLabel(groupBox_3);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_25, 1, 2, 1, 1);

        label_24 = new QLabel(groupBox_3);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_24, 0, 2, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(0);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        checkBox_9 = new QCheckBox(groupBox_3);
        checkBox_9->setObjectName(QString::fromUtf8("checkBox_9"));
        checkBox_9->setMinimumSize(QSize(16, 13));
        checkBox_9->setMaximumSize(QSize(16, 13));

        horizontalLayout_10->addWidget(checkBox_9);

        lineEdit_9 = new QLineEdit(groupBox_3);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lineEdit_9->sizePolicy().hasHeightForWidth());
        lineEdit_9->setSizePolicy(sizePolicy4);
        lineEdit_9->setMinimumSize(QSize(108, 0));
        lineEdit_9->setMaximumSize(QSize(108, 16777215));
        lineEdit_9->setReadOnly(true);

        horizontalLayout_10->addWidget(lineEdit_9);


        gridLayout_4->addLayout(horizontalLayout_10, 1, 1, 1, 1);

        label_26 = new QLabel(groupBox_3);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_26, 3, 2, 1, 1);

        cmbPrimaryTarget = new QComboBox(groupBox_3);
        cmbPrimaryTarget->addItem(QString());
        cmbPrimaryTarget->addItem(QString());
        cmbPrimaryTarget->addItem(QString());
        cmbPrimaryTarget->setObjectName(QString::fromUtf8("cmbPrimaryTarget"));
        cmbPrimaryTarget->setMinimumSize(QSize(124, 24));
        cmbPrimaryTarget->setMaximumSize(QSize(124, 24));

        gridLayout_4->addWidget(cmbPrimaryTarget, 6, 1, 1, 1);

        dsbSegmentShift = new QDoubleSpinBox(groupBox_3);
        dsbSegmentShift->setObjectName(QString::fromUtf8("dsbSegmentShift"));
        dsbSegmentShift->setMinimumSize(QSize(100, 24));
        dsbSegmentShift->setMaximumSize(QSize(100, 24));
        dsbSegmentShift->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(dsbSegmentShift, 1, 3, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        checkBox_8 = new QCheckBox(groupBox_3);
        checkBox_8->setObjectName(QString::fromUtf8("checkBox_8"));
        checkBox_8->setMinimumSize(QSize(16, 13));
        checkBox_8->setMaximumSize(QSize(16, 13));

        horizontalLayout_9->addWidget(checkBox_8);

        lineEdit_8 = new QLineEdit(groupBox_3);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        lineEdit_8->setMinimumSize(QSize(108, 0));
        lineEdit_8->setMaximumSize(QSize(108, 16777215));
        lineEdit_8->setReadOnly(true);

        horizontalLayout_9->addWidget(lineEdit_8);


        gridLayout_4->addLayout(horizontalLayout_9, 0, 1, 1, 1);

        spbPrimaryTargetSpecified = new QSpinBox(groupBox_3);
        spbPrimaryTargetSpecified->setObjectName(QString::fromUtf8("spbPrimaryTargetSpecified"));
        spbPrimaryTargetSpecified->setMinimumSize(QSize(100, 24));
        spbPrimaryTargetSpecified->setMaximumSize(QSize(100, 24));
        spbPrimaryTargetSpecified->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(spbPrimaryTargetSpecified, 6, 3, 1, 1);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy3.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy3);
        label_9->setMinimumSize(QSize(0, 24));
        label_9->setMaximumSize(QSize(16777215, 24));

        gridLayout_4->addWidget(label_9, 0, 0, 1, 1);

        spbMaxNoSegments = new QSpinBox(groupBox_3);
        spbMaxNoSegments->setObjectName(QString::fromUtf8("spbMaxNoSegments"));
        spbMaxNoSegments->setMinimumSize(QSize(100, 24));
        spbMaxNoSegments->setMaximumSize(QSize(100, 24));
        spbMaxNoSegments->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(spbMaxNoSegments, 7, 3, 1, 1);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(0, 24));
        label_10->setMaximumSize(QSize(16777215, 24));

        gridLayout_4->addWidget(label_10, 1, 0, 1, 1);

        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMinimumSize(QSize(0, 24));
        label_14->setMaximumSize(QSize(16777215, 24));

        gridLayout_4->addWidget(label_14, 6, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(0);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        checkBox_10 = new QCheckBox(groupBox_3);
        checkBox_10->setObjectName(QString::fromUtf8("checkBox_10"));
        checkBox_10->setMinimumSize(QSize(16, 13));
        checkBox_10->setMaximumSize(QSize(16, 13));

        horizontalLayout_11->addWidget(checkBox_10);

        lineEdit_10 = new QLineEdit(groupBox_3);
        lineEdit_10->setObjectName(QString::fromUtf8("lineEdit_10"));
        lineEdit_10->setMinimumSize(QSize(108, 0));
        lineEdit_10->setMaximumSize(QSize(108, 16777215));
        lineEdit_10->setReadOnly(true);

        horizontalLayout_11->addWidget(lineEdit_10);


        gridLayout_4->addLayout(horizontalLayout_11, 3, 1, 1, 1);

        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMinimumSize(QSize(100, 24));
        label_13->setMaximumSize(QSize(100, 24));
        label_13->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_13, 5, 3, 1, 1);

        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setMinimumSize(QSize(0, 24));
        label_15->setMaximumSize(QSize(16777215, 24));

        gridLayout_4->addWidget(label_15, 7, 0, 1, 1);

        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMinimumSize(QSize(0, 24));
        label_12->setMaximumSize(QSize(16777215, 24));

        gridLayout_4->addWidget(label_12, 5, 0, 1, 1);

        dsbSegmentOffset = new QDoubleSpinBox(groupBox_3);
        dsbSegmentOffset->setObjectName(QString::fromUtf8("dsbSegmentOffset"));
        dsbSegmentOffset->setMinimumSize(QSize(100, 24));
        dsbSegmentOffset->setMaximumSize(QSize(100, 24));
        dsbSegmentOffset->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(dsbSegmentOffset, 3, 3, 1, 1);

        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMinimumSize(QSize(0, 24));
        label_11->setMaximumSize(QSize(16777215, 24));

        gridLayout_4->addWidget(label_11, 3, 0, 1, 1);

        spbSegmentSize = new QSpinBox(groupBox_3);
        spbSegmentSize->setObjectName(QString::fromUtf8("spbSegmentSize"));
        spbSegmentSize->setMinimumSize(QSize(100, 24));
        spbSegmentSize->setMaximumSize(QSize(100, 24));
        spbSegmentSize->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spbSegmentSize->setMinimum(1);
        spbSegmentSize->setMaximum(9999);
        spbSegmentSize->setValue(3);

        gridLayout_4->addWidget(spbSegmentSize, 0, 3, 1, 1);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalSpacer = new QSpacerItem(20, 4, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_4);

        verticalSpacer_2 = new QSpacerItem(20, 111, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);

        scrollArea_2 = new QScrollArea(centralWidget);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 757, 711));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        horizontalLayout->addWidget(scrollArea_2);

        LineProfileClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LineProfileClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1228, 23));
        LineProfileClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LineProfileClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        LineProfileClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LineProfileClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        LineProfileClass->setStatusBar(statusBar);

        retranslateUi(LineProfileClass);

        cmbPrimaryTarget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LineProfileClass);
    } // setupUi

    void retranslateUi(QMainWindow *LineProfileClass)
    {
        LineProfileClass->setWindowTitle(QApplication::translate("LineProfileClass", "LineProfile", nullptr));
        groupBox->setTitle(QApplication::translate("LineProfileClass", "Direction", nullptr));
        label->setText(QApplication::translate("LineProfileClass", "Trend Direction", nullptr));
        cmbTrendDirection->setItemText(0, QApplication::translate("LineProfileClass", "\342\206\223", nullptr));
        cmbTrendDirection->setItemText(1, QApplication::translate("LineProfileClass", "\342\206\221", nullptr));
        cmbTrendDirection->setItemText(2, QApplication::translate("LineProfileClass", "\342\206\222", nullptr));
        cmbTrendDirection->setItemText(3, QApplication::translate("LineProfileClass", "\342\206\220", nullptr));

        label_2->setText(QApplication::translate("LineProfileClass", "Scan Direction", nullptr));
        checkBox_5->setText(QString());
        label_21->setText(QApplication::translate("LineProfileClass", "=", nullptr));
        cmbScanDirection->setItemText(0, QApplication::translate("LineProfileClass", "Forward", nullptr));
        cmbScanDirection->setItemText(1, QApplication::translate("LineProfileClass", "Reverse", nullptr));

        label_3->setText(QApplication::translate("LineProfileClass", "Edge Direction", nullptr));
        checkBox_6->setText(QString());
        label_22->setText(QApplication::translate("LineProfileClass", "=", nullptr));
        cmbEdgeDirection->setItemText(0, QApplication::translate("LineProfileClass", "Light\342\206\222Dark", nullptr));
        cmbEdgeDirection->setItemText(1, QApplication::translate("LineProfileClass", "Dark\342\206\222Light", nullptr));
        cmbEdgeDirection->setItemText(2, QApplication::translate("LineProfileClass", "Both", nullptr));

        label_4->setText(QApplication::translate("LineProfileClass", "Specified Edge", nullptr));
        checkBox_7->setText(QString());
        label_23->setText(QApplication::translate("LineProfileClass", "=", nullptr));
        groupBox_2->setTitle(QApplication::translate("LineProfileClass", "Edge Strength", nullptr));
        checkBox->setText(QString());
        label_16->setText(QApplication::translate("LineProfileClass", "=", nullptr));
        label_5->setText(QApplication::translate("LineProfileClass", "EdgeFilterWidth", nullptr));
        checkBox_2->setText(QString());
        label_17->setText(QApplication::translate("LineProfileClass", "=", nullptr));
        label_6->setText(QApplication::translate("LineProfileClass", "Edge Intensity", nullptr));
        label_7->setText(QApplication::translate("LineProfileClass", "Upper", nullptr));
        checkBox_3->setText(QString());
        label_18->setText(QApplication::translate("LineProfileClass", "=", nullptr));
        label_20->setText(QApplication::translate("LineProfileClass", "Lower", nullptr));
        checkBox_4->setText(QString());
        label_19->setText(QApplication::translate("LineProfileClass", "=", nullptr));
        label_8->setText(QApplication::translate("LineProfileClass", "Edge Sensitivity(%)", nullptr));
        groupBox_3->setTitle(QApplication::translate("LineProfileClass", "Segment Options", nullptr));
        label_25->setText(QApplication::translate("LineProfileClass", "=", nullptr));
        label_24->setText(QApplication::translate("LineProfileClass", "=", nullptr));
        checkBox_9->setText(QString());
        label_26->setText(QApplication::translate("LineProfileClass", "=", nullptr));
        cmbPrimaryTarget->setItemText(0, QApplication::translate("LineProfileClass", "Max", nullptr));
        cmbPrimaryTarget->setItemText(1, QApplication::translate("LineProfileClass", "Min", nullptr));
        cmbPrimaryTarget->setItemText(2, QApplication::translate("LineProfileClass", "Specified", nullptr));

        checkBox_8->setText(QString());
        label_9->setText(QApplication::translate("LineProfileClass", "Segment Size", nullptr));
        label_10->setText(QApplication::translate("LineProfileClass", "Segment Shift", nullptr));
        label_14->setText(QApplication::translate("LineProfileClass", "Primary Target", nullptr));
        checkBox_10->setText(QString());
        label_13->setText(QApplication::translate("LineProfileClass", "0", nullptr));
        label_15->setText(QApplication::translate("LineProfileClass", "Max No. Segments", nullptr));
        label_12->setText(QApplication::translate("LineProfileClass", "No. Segments", nullptr));
        label_11->setText(QApplication::translate("LineProfileClass", "Segment Offset", nullptr));
        groupBox_4->setTitle(QApplication::translate("LineProfileClass", "Circle/Line Detection", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LineProfileClass: public Ui_LineProfileClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINEPROFILE_H
