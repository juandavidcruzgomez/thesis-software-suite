/********************************************************************************
** Form generated from reading UI file 'PatternLoadWindowB31375.ui'
**
** Created: Tue Oct 21 17:55:57 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef PATTERNLOADWINDOWB31375_H
#define PATTERNLOADWINDOWB31375_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PatternLoadWindow
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *nbPatternsLabel;
    QLabel *nbPatternsInfoLabel;
    QLabel *nbFeaturesLabel;
    QLabel *nbFeaturesInfoLabel;
    QLabel *nbPointsOfViewLabel;
    QSpinBox *nbPoVSpinBox;
    QLabel *startLabel;
    QSpinBox *povStartSpinBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *saveButton;
    QComboBox *povComboBox;
    QLabel *endLabel;
    QSpinBox *povEndSpinBox;
    QTableWidget *patternTable;
    QLabel *statusReportLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PatternLoadWindow)
    {
        if (PatternLoadWindow->objectName().isEmpty())
            PatternLoadWindow->setObjectName(QString::fromUtf8("PatternLoadWindow"));
        PatternLoadWindow->resize(611, 673);
        PatternLoadWindow->setModal(true);
        verticalLayout = new QVBoxLayout(PatternLoadWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(PatternLoadWindow);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget = new QWidget(groupBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        nbPatternsLabel = new QLabel(widget);
        nbPatternsLabel->setObjectName(QString::fromUtf8("nbPatternsLabel"));

        gridLayout->addWidget(nbPatternsLabel, 0, 0, 1, 1);

        nbPatternsInfoLabel = new QLabel(widget);
        nbPatternsInfoLabel->setObjectName(QString::fromUtf8("nbPatternsInfoLabel"));

        gridLayout->addWidget(nbPatternsInfoLabel, 0, 1, 1, 1);

        nbFeaturesLabel = new QLabel(widget);
        nbFeaturesLabel->setObjectName(QString::fromUtf8("nbFeaturesLabel"));

        gridLayout->addWidget(nbFeaturesLabel, 1, 0, 1, 1);

        nbFeaturesInfoLabel = new QLabel(widget);
        nbFeaturesInfoLabel->setObjectName(QString::fromUtf8("nbFeaturesInfoLabel"));

        gridLayout->addWidget(nbFeaturesInfoLabel, 1, 1, 1, 1);

        nbPointsOfViewLabel = new QLabel(widget);
        nbPointsOfViewLabel->setObjectName(QString::fromUtf8("nbPointsOfViewLabel"));

        gridLayout->addWidget(nbPointsOfViewLabel, 2, 0, 1, 1);

        nbPoVSpinBox = new QSpinBox(widget);
        nbPoVSpinBox->setObjectName(QString::fromUtf8("nbPoVSpinBox"));

        gridLayout->addWidget(nbPoVSpinBox, 2, 1, 1, 1);

        startLabel = new QLabel(widget);
        startLabel->setObjectName(QString::fromUtf8("startLabel"));

        gridLayout->addWidget(startLabel, 4, 0, 1, 1);

        povStartSpinBox = new QSpinBox(widget);
        povStartSpinBox->setObjectName(QString::fromUtf8("povStartSpinBox"));

        gridLayout->addWidget(povStartSpinBox, 4, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 3, 1, 1);

        saveButton = new QPushButton(widget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        gridLayout->addWidget(saveButton, 4, 3, 1, 1);

        povComboBox = new QComboBox(widget);
        povComboBox->setObjectName(QString::fromUtf8("povComboBox"));

        gridLayout->addWidget(povComboBox, 2, 3, 1, 1);

        endLabel = new QLabel(widget);
        endLabel->setObjectName(QString::fromUtf8("endLabel"));

        gridLayout->addWidget(endLabel, 5, 0, 1, 1);

        povEndSpinBox = new QSpinBox(widget);
        povEndSpinBox->setObjectName(QString::fromUtf8("povEndSpinBox"));

        gridLayout->addWidget(povEndSpinBox, 5, 1, 1, 1);


        verticalLayout_2->addWidget(widget);

        patternTable = new QTableWidget(groupBox);
        patternTable->setObjectName(QString::fromUtf8("patternTable"));
        patternTable->setMinimumSize(QSize(557, 300));
        patternTable->setMaximumSize(QSize(557, 300));

        verticalLayout_2->addWidget(patternTable);


        verticalLayout->addWidget(groupBox);

        statusReportLabel = new QLabel(PatternLoadWindow);
        statusReportLabel->setObjectName(QString::fromUtf8("statusReportLabel"));
        statusReportLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout->addWidget(statusReportLabel);

        buttonBox = new QDialogButtonBox(PatternLoadWindow);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(PatternLoadWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), PatternLoadWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PatternLoadWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(PatternLoadWindow);
    } // setupUi

    void retranslateUi(QDialog *PatternLoadWindow)
    {
        PatternLoadWindow->setWindowTitle(QApplication::translate("PatternLoadWindow", "Point of view configuration", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("PatternLoadWindow", "Configuration of points of view", 0, QApplication::UnicodeUTF8));
        nbPatternsLabel->setText(QApplication::translate("PatternLoadWindow", "Number of patterns:", 0, QApplication::UnicodeUTF8));
        nbPatternsInfoLabel->setText(QApplication::translate("PatternLoadWindow", "0", 0, QApplication::UnicodeUTF8));
        nbFeaturesLabel->setText(QApplication::translate("PatternLoadWindow", "Number of features (columns):", 0, QApplication::UnicodeUTF8));
        nbFeaturesInfoLabel->setText(QApplication::translate("PatternLoadWindow", "0", 0, QApplication::UnicodeUTF8));
        nbPointsOfViewLabel->setText(QApplication::translate("PatternLoadWindow", "Number of points of view:", 0, QApplication::UnicodeUTF8));
        startLabel->setText(QApplication::translate("PatternLoadWindow", "Start:", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("PatternLoadWindow", "Save changes", 0, QApplication::UnicodeUTF8));
        endLabel->setText(QApplication::translate("PatternLoadWindow", "End:", 0, QApplication::UnicodeUTF8));
        statusReportLabel->setText(QApplication::translate("PatternLoadWindow", "Ready.", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PatternLoadWindow: public Ui_PatternLoadWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // PATTERNLOADWINDOWB31375_H
