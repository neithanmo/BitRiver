/********************************************************************************
** Form generated from reading UI file 'gstvideo.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
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
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gstvideo
{
public:
    QWidget *widget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_5;
    QToolButton *bstop;
    QComboBox *comboBox;
    QToolButton *bplay;
    QSlider *slider2;
    QSlider *slider5;
    QProgressBar *progressBar2;
    QSlider *slider1;
    QProgressBar *progressBar1;
    QProgressBar *progressBar4;
    QSlider *slider4;
    QSlider *slider3;
    QProgressBar *progressBar3;
    QLabel *label_4;

    void setupUi(QWidget *gstvideo)
    {
        if (gstvideo->objectName().isEmpty())
            gstvideo->setObjectName(QStringLiteral("gstvideo"));
        gstvideo->resize(1024, 1024);
        gstvideo->setMinimumSize(QSize(1024, 0));
        gstvideo->setMaximumSize(QSize(2000, 1024));
        widget = new QWidget(gstvideo);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 1024, 768));
        widget->setMinimumSize(QSize(723, 0));
        widget->setMaximumSize(QSize(1024, 768));
        widget->setMouseTracking(true);
        label = new QLabel(gstvideo);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 800, 54, 15));
        label_2 = new QLabel(gstvideo);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 870, 61, 16));
        label_3 = new QLabel(gstvideo);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 940, 54, 15));
        label_5 = new QLabel(gstvideo);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(620, 880, 61, 16));
        bstop = new QToolButton(gstvideo);
        bstop->setObjectName(QStringLiteral("bstop"));
        bstop->setGeometry(QRect(450, 870, 55, 25));
        bstop->setMaximumSize(QSize(81, 16777215));
        comboBox = new QComboBox(gstvideo);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(440, 910, 87, 31));
        bplay = new QToolButton(gstvideo);
        bplay->setObjectName(QStringLiteral("bplay"));
        bplay->setGeometry(QRect(460, 820, 41, 25));
        slider2 = new QSlider(gstvideo);
        slider2->setObjectName(QStringLiteral("slider2"));
        slider2->setGeometry(QRect(10, 900, 160, 23));
        slider2->setMaximumSize(QSize(160, 16777215));
        slider2->setOrientation(Qt::Horizontal);
        slider5 = new QSlider(gstvideo);
        slider5->setObjectName(QStringLiteral("slider5"));
        slider5->setGeometry(QRect(10, 970, 160, 23));
        slider5->setMaximumSize(QSize(160, 16777215));
        slider5->setOrientation(Qt::Horizontal);
        progressBar2 = new QProgressBar(gstvideo);
        progressBar2->setObjectName(QStringLiteral("progressBar2"));
        progressBar2->setGeometry(QRect(230, 900, 99, 27));
        progressBar2->setMaximumSize(QSize(118, 16777215));
        progressBar2->setValue(24);
        slider1 = new QSlider(gstvideo);
        slider1->setObjectName(QStringLiteral("slider1"));
        slider1->setGeometry(QRect(10, 830, 160, 27));
        slider1->setMaximumSize(QSize(160, 27));
        slider1->setOrientation(Qt::Horizontal);
        progressBar1 = new QProgressBar(gstvideo);
        progressBar1->setObjectName(QStringLiteral("progressBar1"));
        progressBar1->setGeometry(QRect(230, 830, 99, 27));
        progressBar1->setValue(24);
        progressBar4 = new QProgressBar(gstvideo);
        progressBar4->setObjectName(QStringLiteral("progressBar4"));
        progressBar4->setGeometry(QRect(850, 910, 99, 27));
        progressBar4->setMaximumSize(QSize(118, 16777215));
        progressBar4->setValue(24);
        slider4 = new QSlider(gstvideo);
        slider4->setObjectName(QStringLiteral("slider4"));
        slider4->setGeometry(QRect(620, 910, 160, 23));
        slider4->setMaximumSize(QSize(160, 16777215));
        slider4->setOrientation(Qt::Horizontal);
        slider3 = new QSlider(gstvideo);
        slider3->setObjectName(QStringLiteral("slider3"));
        slider3->setGeometry(QRect(620, 830, 160, 23));
        slider3->setMaximumSize(QSize(160, 16777215));
        slider3->setOrientation(Qt::Horizontal);
        progressBar3 = new QProgressBar(gstvideo);
        progressBar3->setObjectName(QStringLiteral("progressBar3"));
        progressBar3->setGeometry(QRect(850, 820, 99, 27));
        progressBar3->setValue(24);
        label_4 = new QLabel(gstvideo);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(620, 800, 77, 27));
        bstop->raise();
        comboBox->raise();
        bplay->raise();
        slider2->raise();
        slider5->raise();
        progressBar2->raise();
        slider1->raise();
        progressBar1->raise();
        progressBar4->raise();
        slider4->raise();
        slider3->raise();
        progressBar3->raise();
        widget->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        label_5->raise();
        label_4->raise();

        retranslateUi(gstvideo);

        QMetaObject::connectSlotsByName(gstvideo);
    } // setupUi

    void retranslateUi(QWidget *gstvideo)
    {
        gstvideo->setWindowTitle(QApplication::translate("gstvideo", "gstvideo", 0));
        label->setText(QApplication::translate("gstvideo", "Contrast", 0));
        label_2->setText(QApplication::translate("gstvideo", "Brightness", 0));
        label_3->setText(QApplication::translate("gstvideo", "Volume", 0));
        label_5->setText(QApplication::translate("gstvideo", "Saturation", 0));
        bstop->setText(QApplication::translate("gstvideo", "Pause", 0));
#ifndef QT_NO_WHATSTHIS
        comboBox->setWhatsThis(QApplication::translate("gstvideo", "<html><head/><body><p>efectos</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        bplay->setWhatsThis(QApplication::translate("gstvideo", "<html><head/><body><p>Play</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        bplay->setText(QApplication::translate("gstvideo", "Play", 0));
#ifndef QT_NO_WHATSTHIS
        slider2->setWhatsThis(QApplication::translate("gstvideo", "<html><head/><body><p>Brillo</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        slider1->setWhatsThis(QApplication::translate("gstvideo", "<html><head/><body><p>Contraste</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        label_4->setText(QApplication::translate("gstvideo", "Hue", 0));
    } // retranslateUi

};

namespace Ui {
    class gstvideo: public Ui_gstvideo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSTVIDEO_H
