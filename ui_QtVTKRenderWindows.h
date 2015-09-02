/********************************************************************************
** Form generated from reading UI file 'QtVTKRenderWindows.ui'
**
** Created: Tue 25. Nov 14:20:31 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTVTKRENDERWINDOWS_H
#define UI_QTVTKRENDERWINDOWS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_QtVTKRenderWindows
{
public:
    QAction *actionOpenFile;
    QAction *actionExit;
    QAction *actionPrint;
    QAction *actionHelp;
    QAction *actionSave;
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QVTKWidget *view2;
    QVTKWidget *view4;
    QVTKWidget *view3;
    QVTKWidget *view1;
    QFrame *frame;
    QCheckBox *resliceModeCheckBox;
    QCheckBox *thickModeCheckBox;
    QGroupBox *blendModeGroupBox;
    QRadioButton *radioButton_Min;
    QRadioButton *radioButton_Max;
    QRadioButton *radioButton_Mean;
    QPushButton *resetButton;
    QFrame *frame_2;
    QPushButton *AddDistance1Button;

    void setupUi(QMainWindow *QtVTKRenderWindows)
    {
        if (QtVTKRenderWindows->objectName().isEmpty())
            QtVTKRenderWindows->setObjectName(QString::fromUtf8("QtVTKRenderWindows"));
        QtVTKRenderWindows->resize(990, 583);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icons/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        QtVTKRenderWindows->setWindowIcon(icon);
        QtVTKRenderWindows->setIconSize(QSize(22, 22));
        actionOpenFile = new QAction(QtVTKRenderWindows);
        actionOpenFile->setObjectName(QString::fromUtf8("actionOpenFile"));
        actionOpenFile->setEnabled(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icons/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenFile->setIcon(icon1);
        actionExit = new QAction(QtVTKRenderWindows);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(""), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon2);
        actionPrint = new QAction(QtVTKRenderWindows);
        actionPrint->setObjectName(QString::fromUtf8("actionPrint"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icons/print.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrint->setIcon(icon3);
        actionHelp = new QAction(QtVTKRenderWindows);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionHelp->setIcon(icon);
        actionSave = new QAction(QtVTKRenderWindows);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icons/filesave.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon4);
        centralwidget = new QWidget(QtVTKRenderWindows);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 591, 531));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        view2 = new QVTKWidget(gridLayoutWidget);
        view2->setObjectName(QString::fromUtf8("view2"));

        gridLayout_2->addWidget(view2, 1, 0, 1, 1);

        view4 = new QVTKWidget(gridLayoutWidget);
        view4->setObjectName(QString::fromUtf8("view4"));

        gridLayout_2->addWidget(view4, 0, 1, 1, 1);

        view3 = new QVTKWidget(gridLayoutWidget);
        view3->setObjectName(QString::fromUtf8("view3"));

        gridLayout_2->addWidget(view3, 1, 1, 1, 1);

        view1 = new QVTKWidget(gridLayoutWidget);
        view1->setObjectName(QString::fromUtf8("view1"));

        gridLayout_2->addWidget(view1, 0, 0, 1, 1);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(629, 39, 161, 521));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        resliceModeCheckBox = new QCheckBox(frame);
        resliceModeCheckBox->setObjectName(QString::fromUtf8("resliceModeCheckBox"));
        resliceModeCheckBox->setGeometry(QRect(30, 20, 101, 17));
        thickModeCheckBox = new QCheckBox(frame);
        thickModeCheckBox->setObjectName(QString::fromUtf8("thickModeCheckBox"));
        thickModeCheckBox->setGeometry(QRect(30, 80, 101, 17));
        blendModeGroupBox = new QGroupBox(frame);
        blendModeGroupBox->setObjectName(QString::fromUtf8("blendModeGroupBox"));
        blendModeGroupBox->setGeometry(QRect(10, 120, 141, 91));
        radioButton_Min = new QRadioButton(blendModeGroupBox);
        radioButton_Min->setObjectName(QString::fromUtf8("radioButton_Min"));
        radioButton_Min->setGeometry(QRect(10, 20, 111, 17));
        radioButton_Max = new QRadioButton(blendModeGroupBox);
        radioButton_Max->setObjectName(QString::fromUtf8("radioButton_Max"));
        radioButton_Max->setGeometry(QRect(10, 40, 121, 17));
        radioButton_Mean = new QRadioButton(blendModeGroupBox);
        radioButton_Mean->setObjectName(QString::fromUtf8("radioButton_Mean"));
        radioButton_Mean->setGeometry(QRect(10, 60, 111, 17));
        resetButton = new QPushButton(frame);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(10, 220, 51, 21));
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(0, 250, 161, 211));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        AddDistance1Button = new QPushButton(frame_2);
        AddDistance1Button->setObjectName(QString::fromUtf8("AddDistance1Button"));
        AddDistance1Button->setGeometry(QRect(0, 0, 131, 21));
        QtVTKRenderWindows->setCentralWidget(centralwidget);

        retranslateUi(QtVTKRenderWindows);

        QMetaObject::connectSlotsByName(QtVTKRenderWindows);
    } // setupUi

    void retranslateUi(QMainWindow *QtVTKRenderWindows)
    {
        QtVTKRenderWindows->setWindowTitle(QApplication::translate("QtVTKRenderWindows", "QtVTKRenderWindows", 0, QApplication::UnicodeUTF8));
        actionOpenFile->setText(QApplication::translate("QtVTKRenderWindows", "Open File...", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("QtVTKRenderWindows", "Exit", 0, QApplication::UnicodeUTF8));
        actionPrint->setText(QApplication::translate("QtVTKRenderWindows", "Print", 0, QApplication::UnicodeUTF8));
        actionHelp->setText(QApplication::translate("QtVTKRenderWindows", "Help", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("QtVTKRenderWindows", "Save", 0, QApplication::UnicodeUTF8));
        resliceModeCheckBox->setText(QApplication::translate("QtVTKRenderWindows", "Oblique Reslice", 0, QApplication::UnicodeUTF8));
        thickModeCheckBox->setText(QApplication::translate("QtVTKRenderWindows", "Thick Slab", 0, QApplication::UnicodeUTF8));
        blendModeGroupBox->setTitle(QApplication::translate("QtVTKRenderWindows", "Blend mode", 0, QApplication::UnicodeUTF8));
        radioButton_Min->setText(QApplication::translate("QtVTKRenderWindows", "Min Intensity Blend", 0, QApplication::UnicodeUTF8));
        radioButton_Max->setText(QApplication::translate("QtVTKRenderWindows", "Max Intensity Blend", 0, QApplication::UnicodeUTF8));
        radioButton_Mean->setText(QApplication::translate("QtVTKRenderWindows", "Mean Blend", 0, QApplication::UnicodeUTF8));
        resetButton->setText(QApplication::translate("QtVTKRenderWindows", "Reset", 0, QApplication::UnicodeUTF8));
        AddDistance1Button->setText(QApplication::translate("QtVTKRenderWindows", "Add Distance On View 1", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtVTKRenderWindows: public Ui_QtVTKRenderWindows {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTVTKRENDERWINDOWS_H
