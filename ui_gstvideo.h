/********************************************************************************
** Form generated from reading UI file 'gstvideo.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSTVIDEO_H
#define UI_GSTVIDEO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gstvideo
{
public:
    QSlider *slider1;
    QSlider *slider2;
    QSlider *slider3;
    QSlider *slider4;
    QToolButton *bplay;
    QToolButton *bstop;
    QProgressBar *progressBar1;
    QProgressBar *progressBar2;
    QProgressBar *progressBar3;
    QProgressBar *progressBar4;
    QWidget *widget;
    QComboBox *comboBox;
    QSlider *slider5;

    void setupUi(QWidget *gstvideo)
    {
        if (gstvideo->objectName().isEmpty())
            gstvideo->setObjectName(QStringLiteral("gstvideo"));
        gstvideo->resize(741, 832);
        gstvideo->setMinimumSize(QSize(741, 0));
        slider1 = new QSlider(gstvideo);
        slider1->setObjectName(QStringLiteral("slider1"));
        slider1->setGeometry(QRect(50, 510, 88, 27));
        slider1->setMaximumSize(QSize(16777215, 27));
        slider1->setOrientation(Qt::Horizontal);
        slider2 = new QSlider(gstvideo);
        slider2->setObjectName(QStringLiteral("slider2"));
        slider2->setGeometry(QRect(50, 580, 88, 27));
        slider2->setMaximumSize(QSize(160, 16777215));
        slider2->setOrientation(Qt::Horizontal);
        slider3 = new QSlider(gstvideo);
        slider3->setObjectName(QStringLiteral("slider3"));
        slider3->setGeometry(QRect(450, 510, 88, 27));
        slider3->setOrientation(Qt::Horizontal);
        slider4 = new QSlider(gstvideo);
        slider4->setObjectName(QStringLiteral("slider4"));
        slider4->setGeometry(QRect(450, 580, 88, 27));
        slider4->setMaximumSize(QSize(160, 16777215));
        slider4->setOrientation(Qt::Horizontal);
        bplay = new QToolButton(gstvideo);
        bplay->setObjectName(QStringLiteral("bplay"));
        bplay->setGeometry(QRect(350, 510, 33, 21));
        bstop = new QToolButton(gstvideo);
        bstop->setObjectName(QStringLiteral("bstop"));
        bstop->setGeometry(QRect(350, 570, 43, 21));
        bstop->setMaximumSize(QSize(81, 16777215));
        progressBar1 = new QProgressBar(gstvideo);
        progressBar1->setObjectName(QStringLiteral("progressBar1"));
        progressBar1->setGeometry(QRect(210, 510, 91, 23));
        progressBar1->setValue(24);
        progressBar2 = new QProgressBar(gstvideo);
        progressBar2->setObjectName(QStringLiteral("progressBar2"));
        progressBar2->setGeometry(QRect(210, 580, 91, 23));
        progressBar2->setMaximumSize(QSize(118, 16777215));
        progressBar2->setValue(24);
        progressBar3 = new QProgressBar(gstvideo);
        progressBar3->setObjectName(QStringLiteral("progressBar3"));
        progressBar3->setGeometry(QRect(610, 510, 91, 23));
        progressBar3->setValue(24);
        progressBar4 = new QProgressBar(gstvideo);
        progressBar4->setObjectName(QStringLiteral("progressBar4"));
        progressBar4->setGeometry(QRect(610, 580, 91, 23));
        progressBar4->setMaximumSize(QSize(118, 16777215));
        progressBar4->setValue(24);
        widget = new QWidget(gstvideo);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(40, 0, 640, 480));
        comboBox = new QComboBox(gstvideo);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(350, 620, 77, 27));
        slider5 = new QSlider(gstvideo);
        slider5->setObjectName(QStringLiteral("slider5"));
        slider5->setGeometry(QRect(50, 640, 88, 27));
        slider5->setOrientation(Qt::Horizontal);

        retranslateUi(gstvideo);

        QMetaObject::connectSlotsByName(gstvideo);
    } // setupUi

    void retranslateUi(QWidget *gstvideo)
    {
        gstvideo->setWindowTitle(QApplication::translate("gstvideo", "gstvideo", 0));
        bplay->setText(QApplication::translate("gstvideo", "Play", 0));
        bstop->setText(QApplication::translate("gstvideo", "Pause", 0));
    } // retranslateUi

};

namespace Ui {
    class gstvideo: public Ui_gstvideo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSTVIDEO_H
