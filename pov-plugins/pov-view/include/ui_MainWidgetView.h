/********************************************************************************
** Form generated from reading UI file 'MainWidgetViewC31375.ui'
**
** Created: Tue Oct 21 17:55:29 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWIDGETVIEWC31375_H
#define MAINWIDGETVIEWC31375_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_mainWidgetView
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *toolBarWidget;
    QHBoxLayout *horizontalLayout;
    QToolButton *loadPovButton;
    QToolButton *configurePoVButton;
    QToolButton *resetConfigurationButton;
    QFrame *line;
    QToolButton *startButton;
    QToolButton *stepButton;
    QToolButton *stopButton;
    QSpacerItem *horizontalSpacer;
    QTabWidget *mainTabs;
    QWidget *summaryTab;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_9;
    QWidget *widget_3;
    QGridLayout *gridLayout_2;
    QLabel *nbNodesLabel;
    QLabel *nbEdgesLabel;
    QLabel *nbEdgesInfo;
    QLabel *nbNodesInfo;
    QLabel *modularityLabel;
    QLabel *nbCommuntiesLabel;
    QLabel *nbCommunitiesInfo;
    QLabel *modularityInfo;
    QSpacerItem *verticalSpacer;
    QFrame *degreeDistSpace;
    QHBoxLayout *horizontalLayout_13;
    QCustomPlot *degreeDistSpaceW;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *featuresFilenameLabel;
    QLabel *featuresFileNameInfo;
    QLabel *nbFeaturesLabel;
    QLabel *nbFeaturesInfo;
    QLabel *featuresHeaderLabel;
    QListWidget *povHeaderList;
    QLabel *nbPoVLabel;
    QLabel *nbPoVInfo;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QWidget *povTab;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *povListGroup;
    QHBoxLayout *horizontalLayout_3;
    QTreeWidget *povTreeList;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *nullPoVReportGroup;
    QVBoxLayout *verticalLayout_4;
    QCustomPlot *barGraphSpacePoVNull;
    QFrame *infoFramePoVNull;
    QHBoxLayout *horizontalLayout_5;
    QLabel *povNullModLabel;
    QLabel *povNullModValue;
    QFrame *line_2;
    QLabel *povNullEntropyLabel;
    QLabel *povNullEntropyValue;
    QGroupBox *selPoVReportGroup;
    QVBoxLayout *verticalLayout_5;
    QCustomPlot *barGraphSpacePoVSel;
    QFrame *infoFramePoVSel;
    QHBoxLayout *horizontalLayout_6;
    QLabel *povSelModLabel;
    QLabel *povSelModValue;
    QFrame *line_3;
    QLabel *povSelEntropyLabel;
    QLabel *povSelEntropyValue;
    QWidget *rolesTab;
    QHBoxLayout *horizontalLayout_8;
    QGroupBox *roleComparisonBox;
    QVBoxLayout *verticalLayout_6;
    QFrame *pov1RolesDist;
    QHBoxLayout *horizontalLayout_10;
    QCustomPlot *pov1RolesDistW;
    QFrame *line_6;
    QFrame *pov2RolesDist;
    QHBoxLayout *horizontalLayout_11;
    QCustomPlot *pov2RolesDistW;
    QGroupBox *roleGalleryBox;
    QVBoxLayout *verticalLayout_12;
    QScrollArea *scrollArea;
    QWidget *roleThumbnailArea;
    QWidget *layoutsTab;

    void setupUi(QWidget *mainWidgetView)
    {
        if (mainWidgetView->objectName().isEmpty())
            mainWidgetView->setObjectName(QString::fromUtf8("mainWidgetView"));
        mainWidgetView->resize(653, 700);
        mainWidgetView->setMinimumSize(QSize(630, 600));
        mainWidgetView->setMaximumSize(QSize(653, 700));
        verticalLayout = new QVBoxLayout(mainWidgetView);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        toolBarWidget = new QWidget(mainWidgetView);
        toolBarWidget->setObjectName(QString::fromUtf8("toolBarWidget"));
        horizontalLayout = new QHBoxLayout(toolBarWidget);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        loadPovButton = new QToolButton(toolBarWidget);
        loadPovButton->setObjectName(QString::fromUtf8("loadPovButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/addpov16.png"), QSize(), QIcon::Normal, QIcon::Off);
        loadPovButton->setIcon(icon);

        horizontalLayout->addWidget(loadPovButton);

        configurePoVButton = new QToolButton(toolBarWidget);
        configurePoVButton->setObjectName(QString::fromUtf8("configurePoVButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/conf1616.png"), QSize(), QIcon::Normal, QIcon::Off);
        configurePoVButton->setIcon(icon1);

        horizontalLayout->addWidget(configurePoVButton);

        resetConfigurationButton = new QToolButton(toolBarWidget);
        resetConfigurationButton->setObjectName(QString::fromUtf8("resetConfigurationButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/reset16.png"), QSize(), QIcon::Normal, QIcon::Off);
        resetConfigurationButton->setIcon(icon2);

        horizontalLayout->addWidget(resetConfigurationButton);

        line = new QFrame(toolBarWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShadow(QFrame::Raised);
        line->setLineWidth(1);
        line->setMidLineWidth(1);
        line->setFrameShape(QFrame::VLine);

        horizontalLayout->addWidget(line);

        startButton = new QToolButton(toolBarWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/play1616.png"), QSize(), QIcon::Normal, QIcon::Off);
        startButton->setIcon(icon3);

        horizontalLayout->addWidget(startButton);

        stepButton = new QToolButton(toolBarWidget);
        stepButton->setObjectName(QString::fromUtf8("stepButton"));
        stepButton->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/step1616.png"), QSize(), QIcon::Normal, QIcon::Off);
        stepButton->setIcon(icon4);

        horizontalLayout->addWidget(stepButton);

        stopButton = new QToolButton(toolBarWidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        stopButton->setEnabled(false);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/stop16.png"), QSize(), QIcon::Normal, QIcon::Off);
        stopButton->setIcon(icon5);

        horizontalLayout->addWidget(stopButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(toolBarWidget);

        mainTabs = new QTabWidget(mainWidgetView);
        mainTabs->setObjectName(QString::fromUtf8("mainTabs"));
        mainTabs->setContextMenuPolicy(Qt::CustomContextMenu);
        summaryTab = new QWidget();
        summaryTab->setObjectName(QString::fromUtf8("summaryTab"));
        verticalLayout_2 = new QVBoxLayout(summaryTab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(summaryTab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(560, 246));
        groupBox->setMaximumSize(QSize(1120, 300));
        horizontalLayout_9 = new QHBoxLayout(groupBox);
        horizontalLayout_9->setSpacing(1);
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        widget_3 = new QWidget(groupBox);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout_2 = new QGridLayout(widget_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        nbNodesLabel = new QLabel(widget_3);
        nbNodesLabel->setObjectName(QString::fromUtf8("nbNodesLabel"));

        gridLayout_2->addWidget(nbNodesLabel, 0, 0, 1, 1);

        nbEdgesLabel = new QLabel(widget_3);
        nbEdgesLabel->setObjectName(QString::fromUtf8("nbEdgesLabel"));

        gridLayout_2->addWidget(nbEdgesLabel, 1, 0, 1, 1);

        nbEdgesInfo = new QLabel(widget_3);
        nbEdgesInfo->setObjectName(QString::fromUtf8("nbEdgesInfo"));
        nbEdgesInfo->setMinimumSize(QSize(60, 13));
        nbEdgesInfo->setMaximumSize(QSize(60, 13));

        gridLayout_2->addWidget(nbEdgesInfo, 0, 1, 1, 1);

        nbNodesInfo = new QLabel(widget_3);
        nbNodesInfo->setObjectName(QString::fromUtf8("nbNodesInfo"));
        nbNodesInfo->setMinimumSize(QSize(60, 13));
        nbNodesInfo->setMaximumSize(QSize(60, 13));

        gridLayout_2->addWidget(nbNodesInfo, 1, 1, 1, 1);

        modularityLabel = new QLabel(widget_3);
        modularityLabel->setObjectName(QString::fromUtf8("modularityLabel"));

        gridLayout_2->addWidget(modularityLabel, 4, 0, 1, 1);

        nbCommuntiesLabel = new QLabel(widget_3);
        nbCommuntiesLabel->setObjectName(QString::fromUtf8("nbCommuntiesLabel"));

        gridLayout_2->addWidget(nbCommuntiesLabel, 3, 0, 1, 1);

        nbCommunitiesInfo = new QLabel(widget_3);
        nbCommunitiesInfo->setObjectName(QString::fromUtf8("nbCommunitiesInfo"));
        nbCommunitiesInfo->setMinimumSize(QSize(60, 13));
        nbCommunitiesInfo->setMaximumSize(QSize(60, 13));

        gridLayout_2->addWidget(nbCommunitiesInfo, 3, 1, 1, 1);

        modularityInfo = new QLabel(widget_3);
        modularityInfo->setObjectName(QString::fromUtf8("modularityInfo"));
        modularityInfo->setMinimumSize(QSize(60, 13));
        modularityInfo->setMaximumSize(QSize(60, 13));

        gridLayout_2->addWidget(modularityInfo, 4, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 5, 0, 1, 1);


        horizontalLayout_9->addWidget(widget_3);

        degreeDistSpace = new QFrame(groupBox);
        degreeDistSpace->setObjectName(QString::fromUtf8("degreeDistSpace"));
        degreeDistSpace->setMinimumSize(QSize(350, 100));
        degreeDistSpace->setFrameShape(QFrame::StyledPanel);
        degreeDistSpace->setFrameShadow(QFrame::Raised);
        horizontalLayout_13 = new QHBoxLayout(degreeDistSpace);
        horizontalLayout_13->setSpacing(0);
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        degreeDistSpaceW = new QCustomPlot(degreeDistSpace);
        degreeDistSpaceW->setObjectName(QString::fromUtf8("degreeDistSpaceW"));

        horizontalLayout_13->addWidget(degreeDistSpaceW);


        horizontalLayout_9->addWidget(degreeDistSpace);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(summaryTab);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(560, 247));
        groupBox_2->setMaximumSize(QSize(1120, 300));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        featuresFilenameLabel = new QLabel(groupBox_2);
        featuresFilenameLabel->setObjectName(QString::fromUtf8("featuresFilenameLabel"));

        gridLayout->addWidget(featuresFilenameLabel, 0, 0, 1, 1);

        featuresFileNameInfo = new QLabel(groupBox_2);
        featuresFileNameInfo->setObjectName(QString::fromUtf8("featuresFileNameInfo"));

        gridLayout->addWidget(featuresFileNameInfo, 0, 1, 1, 1);

        nbFeaturesLabel = new QLabel(groupBox_2);
        nbFeaturesLabel->setObjectName(QString::fromUtf8("nbFeaturesLabel"));

        gridLayout->addWidget(nbFeaturesLabel, 1, 0, 1, 1);

        nbFeaturesInfo = new QLabel(groupBox_2);
        nbFeaturesInfo->setObjectName(QString::fromUtf8("nbFeaturesInfo"));

        gridLayout->addWidget(nbFeaturesInfo, 1, 1, 1, 1);

        featuresHeaderLabel = new QLabel(groupBox_2);
        featuresHeaderLabel->setObjectName(QString::fromUtf8("featuresHeaderLabel"));

        gridLayout->addWidget(featuresHeaderLabel, 2, 0, 1, 1);

        povHeaderList = new QListWidget(groupBox_2);
        povHeaderList->setObjectName(QString::fromUtf8("povHeaderList"));
        povHeaderList->setMinimumSize(QSize(300, 100));
        povHeaderList->setMaximumSize(QSize(300, 100));

        gridLayout->addWidget(povHeaderList, 2, 1, 1, 1);

        nbPoVLabel = new QLabel(groupBox_2);
        nbPoVLabel->setObjectName(QString::fromUtf8("nbPoVLabel"));

        gridLayout->addWidget(nbPoVLabel, 3, 0, 1, 1);

        nbPoVInfo = new QLabel(groupBox_2);
        nbPoVInfo->setObjectName(QString::fromUtf8("nbPoVInfo"));

        gridLayout->addWidget(nbPoVInfo, 3, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 4, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 2, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);

        mainTabs->addTab(summaryTab, QString());
        povTab = new QWidget();
        povTab->setObjectName(QString::fromUtf8("povTab"));
        horizontalLayout_2 = new QHBoxLayout(povTab);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        povListGroup = new QGroupBox(povTab);
        povListGroup->setObjectName(QString::fromUtf8("povListGroup"));
        povListGroup->setMinimumSize(QSize(310, 512));
        povListGroup->setMaximumSize(QSize(310, 512));
        horizontalLayout_3 = new QHBoxLayout(povListGroup);
        horizontalLayout_3->setContentsMargins(4, 4, 4, 4);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        povTreeList = new QTreeWidget(povListGroup);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(1, QString::fromUtf8("2"));
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        povTreeList->setHeaderItem(__qtreewidgetitem);
        povTreeList->setObjectName(QString::fromUtf8("povTreeList"));
        povTreeList->setColumnCount(2);

        horizontalLayout_3->addWidget(povTreeList);


        horizontalLayout_2->addWidget(povListGroup);

        widget = new QWidget(povTab);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(310, 512));
        widget->setMaximumSize(QSize(310, 512));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(4, 0, 4, 4);
        nullPoVReportGroup = new QGroupBox(widget);
        nullPoVReportGroup->setObjectName(QString::fromUtf8("nullPoVReportGroup"));
        nullPoVReportGroup->setMinimumSize(QSize(302, 249));
        verticalLayout_4 = new QVBoxLayout(nullPoVReportGroup);
        verticalLayout_4->setSpacing(3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(3, -1, -1, 3);
        barGraphSpacePoVNull = new QCustomPlot(nullPoVReportGroup);
        barGraphSpacePoVNull->setObjectName(QString::fromUtf8("barGraphSpacePoVNull"));
        barGraphSpacePoVNull->setMinimumSize(QSize(280, 170));

        verticalLayout_4->addWidget(barGraphSpacePoVNull);

        infoFramePoVNull = new QFrame(nullPoVReportGroup);
        infoFramePoVNull->setObjectName(QString::fromUtf8("infoFramePoVNull"));
        infoFramePoVNull->setMinimumSize(QSize(280, 33));
        infoFramePoVNull->setFrameShape(QFrame::StyledPanel);
        infoFramePoVNull->setFrameShadow(QFrame::Plain);
        horizontalLayout_5 = new QHBoxLayout(infoFramePoVNull);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        povNullModLabel = new QLabel(infoFramePoVNull);
        povNullModLabel->setObjectName(QString::fromUtf8("povNullModLabel"));

        horizontalLayout_5->addWidget(povNullModLabel);

        povNullModValue = new QLabel(infoFramePoVNull);
        povNullModValue->setObjectName(QString::fromUtf8("povNullModValue"));
        povNullModValue->setMinimumSize(QSize(50, 25));
        povNullModValue->setMaximumSize(QSize(50, 25));
        povNullModValue->setWordWrap(true);

        horizontalLayout_5->addWidget(povNullModValue);

        line_2 = new QFrame(infoFramePoVNull);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_5->addWidget(line_2);

        povNullEntropyLabel = new QLabel(infoFramePoVNull);
        povNullEntropyLabel->setObjectName(QString::fromUtf8("povNullEntropyLabel"));

        horizontalLayout_5->addWidget(povNullEntropyLabel);

        povNullEntropyValue = new QLabel(infoFramePoVNull);
        povNullEntropyValue->setObjectName(QString::fromUtf8("povNullEntropyValue"));
        povNullEntropyValue->setMinimumSize(QSize(50, 25));
        povNullEntropyValue->setMaximumSize(QSize(50, 25));
        povNullEntropyValue->setWordWrap(true);

        horizontalLayout_5->addWidget(povNullEntropyValue);


        verticalLayout_4->addWidget(infoFramePoVNull);


        verticalLayout_3->addWidget(nullPoVReportGroup);

        selPoVReportGroup = new QGroupBox(widget);
        selPoVReportGroup->setObjectName(QString::fromUtf8("selPoVReportGroup"));
        selPoVReportGroup->setMinimumSize(QSize(302, 248));
        verticalLayout_5 = new QVBoxLayout(selPoVReportGroup);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        barGraphSpacePoVSel = new QCustomPlot(selPoVReportGroup);
        barGraphSpacePoVSel->setObjectName(QString::fromUtf8("barGraphSpacePoVSel"));
        barGraphSpacePoVSel->setMinimumSize(QSize(280, 170));

        verticalLayout_5->addWidget(barGraphSpacePoVSel);

        infoFramePoVSel = new QFrame(selPoVReportGroup);
        infoFramePoVSel->setObjectName(QString::fromUtf8("infoFramePoVSel"));
        infoFramePoVSel->setMinimumSize(QSize(280, 33));
        infoFramePoVSel->setFrameShape(QFrame::StyledPanel);
        infoFramePoVSel->setFrameShadow(QFrame::Plain);
        horizontalLayout_6 = new QHBoxLayout(infoFramePoVSel);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        povSelModLabel = new QLabel(infoFramePoVSel);
        povSelModLabel->setObjectName(QString::fromUtf8("povSelModLabel"));

        horizontalLayout_6->addWidget(povSelModLabel);

        povSelModValue = new QLabel(infoFramePoVSel);
        povSelModValue->setObjectName(QString::fromUtf8("povSelModValue"));
        povSelModValue->setMinimumSize(QSize(50, 25));
        povSelModValue->setMaximumSize(QSize(50, 25));
        povSelModValue->setWordWrap(true);

        horizontalLayout_6->addWidget(povSelModValue);

        line_3 = new QFrame(infoFramePoVSel);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_6->addWidget(line_3);

        povSelEntropyLabel = new QLabel(infoFramePoVSel);
        povSelEntropyLabel->setObjectName(QString::fromUtf8("povSelEntropyLabel"));

        horizontalLayout_6->addWidget(povSelEntropyLabel);

        povSelEntropyValue = new QLabel(infoFramePoVSel);
        povSelEntropyValue->setObjectName(QString::fromUtf8("povSelEntropyValue"));
        povSelEntropyValue->setMinimumSize(QSize(50, 25));
        povSelEntropyValue->setMaximumSize(QSize(50, 25));
        povSelEntropyValue->setWordWrap(true);

        horizontalLayout_6->addWidget(povSelEntropyValue);


        verticalLayout_5->addWidget(infoFramePoVSel);


        verticalLayout_3->addWidget(selPoVReportGroup);


        horizontalLayout_2->addWidget(widget);

        mainTabs->addTab(povTab, QString());
        rolesTab = new QWidget();
        rolesTab->setObjectName(QString::fromUtf8("rolesTab"));
        horizontalLayout_8 = new QHBoxLayout(rolesTab);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        roleComparisonBox = new QGroupBox(rolesTab);
        roleComparisonBox->setObjectName(QString::fromUtf8("roleComparisonBox"));
        roleComparisonBox->setMinimumSize(QSize(400, 500));
        roleComparisonBox->setMaximumSize(QSize(400, 16777215));
        verticalLayout_6 = new QVBoxLayout(roleComparisonBox);
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        pov1RolesDist = new QFrame(roleComparisonBox);
        pov1RolesDist->setObjectName(QString::fromUtf8("pov1RolesDist"));
        pov1RolesDist->setMinimumSize(QSize(395, 271));
        pov1RolesDist->setMaximumSize(QSize(395, 271));
        pov1RolesDist->setFrameShape(QFrame::StyledPanel);
        pov1RolesDist->setFrameShadow(QFrame::Raised);
        horizontalLayout_10 = new QHBoxLayout(pov1RolesDist);
        horizontalLayout_10->setSpacing(0);
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        pov1RolesDistW = new QCustomPlot(pov1RolesDist);
        pov1RolesDistW->setObjectName(QString::fromUtf8("pov1RolesDistW"));
        pov1RolesDistW->setContextMenuPolicy(Qt::CustomContextMenu);

        horizontalLayout_10->addWidget(pov1RolesDistW);


        verticalLayout_6->addWidget(pov1RolesDist);

        line_6 = new QFrame(roleComparisonBox);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_6);

        pov2RolesDist = new QFrame(roleComparisonBox);
        pov2RolesDist->setObjectName(QString::fromUtf8("pov2RolesDist"));
        pov2RolesDist->setMinimumSize(QSize(398, 271));
        pov2RolesDist->setMaximumSize(QSize(398, 271));
        pov2RolesDist->setFrameShape(QFrame::StyledPanel);
        pov2RolesDist->setFrameShadow(QFrame::Raised);
        horizontalLayout_11 = new QHBoxLayout(pov2RolesDist);
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        pov2RolesDistW = new QCustomPlot(pov2RolesDist);
        pov2RolesDistW->setObjectName(QString::fromUtf8("pov2RolesDistW"));

        horizontalLayout_11->addWidget(pov2RolesDistW);


        verticalLayout_6->addWidget(pov2RolesDist);


        horizontalLayout_8->addWidget(roleComparisonBox);

        roleGalleryBox = new QGroupBox(rolesTab);
        roleGalleryBox->setObjectName(QString::fromUtf8("roleGalleryBox"));
        verticalLayout_12 = new QVBoxLayout(roleGalleryBox);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        scrollArea = new QScrollArea(roleGalleryBox);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        roleThumbnailArea = new QWidget();
        roleThumbnailArea->setObjectName(QString::fromUtf8("roleThumbnailArea"));
        roleThumbnailArea->setGeometry(QRect(0, 0, 179, 549));
        roleThumbnailArea->setAutoFillBackground(true);
        scrollArea->setWidget(roleThumbnailArea);

        verticalLayout_12->addWidget(scrollArea);


        horizontalLayout_8->addWidget(roleGalleryBox);

        mainTabs->addTab(rolesTab, QString());
        layoutsTab = new QWidget();
        layoutsTab->setObjectName(QString::fromUtf8("layoutsTab"));
        mainTabs->addTab(layoutsTab, QString());

        verticalLayout->addWidget(mainTabs);


        retranslateUi(mainWidgetView);

        mainTabs->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(mainWidgetView);
    } // setupUi

    void retranslateUi(QWidget *mainWidgetView)
    {
        mainWidgetView->setWindowTitle(QApplication::translate("mainWidgetView", "MainWidgetView", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        loadPovButton->setToolTip(QApplication::translate("mainWidgetView", "Load a new set of features", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        loadPovButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        configurePoVButton->setToolTip(QApplication::translate("mainWidgetView", "Configure the points of view", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        configurePoVButton->setText(QApplication::translate("mainWidgetView", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        resetConfigurationButton->setToolTip(QApplication::translate("mainWidgetView", "Reset the point of view configuration (must re-load the features file)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        resetConfigurationButton->setText(QApplication::translate("mainWidgetView", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        startButton->setToolTip(QApplication::translate("mainWidgetView", "Start the process", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        startButton->setText(QApplication::translate("mainWidgetView", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        stepButton->setToolTip(QApplication::translate("mainWidgetView", "Execute the process step-by-step", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        stepButton->setText(QApplication::translate("mainWidgetView", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        stopButton->setToolTip(QApplication::translate("mainWidgetView", "Stop the process", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        stopButton->setText(QApplication::translate("mainWidgetView", "...", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("mainWidgetView", "Graph Information", 0, QApplication::UnicodeUTF8));
        nbNodesLabel->setText(QApplication::translate("mainWidgetView", "Nodes:", 0, QApplication::UnicodeUTF8));
        nbEdgesLabel->setText(QApplication::translate("mainWidgetView", "Edges:", 0, QApplication::UnicodeUTF8));
        nbEdgesInfo->setText(QApplication::translate("mainWidgetView", "000000", 0, QApplication::UnicodeUTF8));
        nbNodesInfo->setText(QApplication::translate("mainWidgetView", "000000", 0, QApplication::UnicodeUTF8));
        modularityLabel->setText(QApplication::translate("mainWidgetView", "Modularity:", 0, QApplication::UnicodeUTF8));
        nbCommuntiesLabel->setText(QApplication::translate("mainWidgetView", "Communities:", 0, QApplication::UnicodeUTF8));
        nbCommunitiesInfo->setText(QApplication::translate("mainWidgetView", "000000", 0, QApplication::UnicodeUTF8));
        modularityInfo->setText(QApplication::translate("mainWidgetView", "0.0000", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("mainWidgetView", "Features and Points of View Information", 0, QApplication::UnicodeUTF8));
        featuresFilenameLabel->setText(QApplication::translate("mainWidgetView", "File name:", 0, QApplication::UnicodeUTF8));
        featuresFileNameInfo->setText(QApplication::translate("mainWidgetView", "N/A", 0, QApplication::UnicodeUTF8));
        nbFeaturesLabel->setText(QApplication::translate("mainWidgetView", "Number of features (columns):", 0, QApplication::UnicodeUTF8));
        nbFeaturesInfo->setText(QApplication::translate("mainWidgetView", "N/A", 0, QApplication::UnicodeUTF8));
        featuresHeaderLabel->setText(QApplication::translate("mainWidgetView", "Headers:", 0, QApplication::UnicodeUTF8));
        nbPoVLabel->setText(QApplication::translate("mainWidgetView", "Defined points of view:", 0, QApplication::UnicodeUTF8));
        nbPoVInfo->setText(QApplication::translate("mainWidgetView", "N/A", 0, QApplication::UnicodeUTF8));
        mainTabs->setTabText(mainTabs->indexOf(summaryTab), QApplication::translate("mainWidgetView", "Summary", 0, QApplication::UnicodeUTF8));
        povListGroup->setTitle(QApplication::translate("mainWidgetView", "PoV List", 0, QApplication::UnicodeUTF8));
        nullPoVReportGroup->setTitle(QApplication::translate("mainWidgetView", "Composition of communities PoV null", 0, QApplication::UnicodeUTF8));
        povNullModLabel->setText(QApplication::translate("mainWidgetView", "Modularity:", 0, QApplication::UnicodeUTF8));
        povNullModValue->setText(QApplication::translate("mainWidgetView", "0.0000", 0, QApplication::UnicodeUTF8));
        povNullEntropyLabel->setText(QApplication::translate("mainWidgetView", "Entropy:", 0, QApplication::UnicodeUTF8));
        povNullEntropyValue->setText(QApplication::translate("mainWidgetView", "0.0000", 0, QApplication::UnicodeUTF8));
        selPoVReportGroup->setTitle(QApplication::translate("mainWidgetView", "Composition of communities selected PoV", 0, QApplication::UnicodeUTF8));
        povSelModLabel->setText(QApplication::translate("mainWidgetView", "Modularity:", 0, QApplication::UnicodeUTF8));
        povSelModValue->setText(QApplication::translate("mainWidgetView", "0.0000", 0, QApplication::UnicodeUTF8));
        povSelEntropyLabel->setText(QApplication::translate("mainWidgetView", "Entropy:", 0, QApplication::UnicodeUTF8));
        povSelEntropyValue->setText(QApplication::translate("mainWidgetView", "0.0000", 0, QApplication::UnicodeUTF8));
        mainTabs->setTabText(mainTabs->indexOf(povTab), QApplication::translate("mainWidgetView", "Points of View", 0, QApplication::UnicodeUTF8));
        roleComparisonBox->setTitle(QApplication::translate("mainWidgetView", "Roles distribution comparison", 0, QApplication::UnicodeUTF8));
        roleGalleryBox->setTitle(QApplication::translate("mainWidgetView", "Roles distribution gallery", 0, QApplication::UnicodeUTF8));
        mainTabs->setTabText(mainTabs->indexOf(rolesTab), QApplication::translate("mainWidgetView", "Roles Browser", 0, QApplication::UnicodeUTF8));
        mainTabs->setTabText(mainTabs->indexOf(layoutsTab), QApplication::translate("mainWidgetView", "Layout Change", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainWidgetView: public Ui_mainWidgetView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWIDGETVIEWC31375_H
