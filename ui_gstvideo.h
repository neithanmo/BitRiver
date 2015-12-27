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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gstvideo
{
public:
    QWidget *widget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QSlider *slider3;
    QProgressBar *progressBar3;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QSlider *slider4;
    QProgressBar *progressBar4;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QSlider *slider1;
    QProgressBar *progressBar1;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_4;
    QSlider *slider2;
    QProgressBar *progressBar2;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_5;
    QSlider *slider5;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout;
    QToolButton *bplay;
    QToolButton *bstop;
    QComboBox *comboBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QWidget *gstvideo)
    {
        if (gstvideo->objectName().isEmpty())
            gstvideo->setObjectName(QStringLiteral("gstvideo"));
        gstvideo->resize(660, 661);
        gstvideo->setMinimumSize(QSize(660, 0));
        gstvideo->setMaximumSize(QSize(660, 16777215));
        widget = new QWidget(gstvideo);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 0, 723, 425));
        widget->setMinimumSize(QSize(723, 0));
        layoutWidget = new QWidget(gstvideo);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(460, 510, 187, 29));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        slider3 = new QSlider(layoutWidget);
        slider3->setObjectName(QStringLiteral("slider3"));
        slider3->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(slider3);

        progressBar3 = new QProgressBar(layoutWidget);
        progressBar3->setObjectName(QStringLiteral("progressBar3"));
        progressBar3->setValue(24);

        horizontalLayout->addWidget(progressBar3);

        layoutWidget1 = new QWidget(gstvideo);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(460, 570, 187, 29));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        slider4 = new QSlider(layoutWidget1);
        slider4->setObjectName(QStringLiteral("slider4"));
        slider4->setMaximumSize(QSize(160, 16777215));
        slider4->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(slider4);

        progressBar4 = new QProgressBar(layoutWidget1);
        progressBar4->setObjectName(QStringLiteral("progressBar4"));
        progressBar4->setMaximumSize(QSize(118, 16777215));
        progressBar4->setValue(24);

        horizontalLayout_2->addWidget(progressBar4);

        layoutWidget2 = new QWidget(gstvideo);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 510, 187, 29));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        slider1 = new QSlider(layoutWidget2);
        slider1->setObjectName(QStringLiteral("slider1"));
        slider1->setMaximumSize(QSize(16777215, 27));
        slider1->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(slider1);

        progressBar1 = new QProgressBar(layoutWidget2);
        progressBar1->setObjectName(QStringLiteral("progressBar1"));
        progressBar1->setValue(24);

        horizontalLayout_3->addWidget(progressBar1);

        layoutWidget3 = new QWidget(gstvideo);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 560, 187, 29));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        slider2 = new QSlider(layoutWidget3);
        slider2->setObjectName(QStringLiteral("slider2"));
        slider2->setMaximumSize(QSize(160, 16777215));
        slider2->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(slider2);

        progressBar2 = new QProgressBar(layoutWidget3);
        progressBar2->setObjectName(QStringLiteral("progressBar2"));
        progressBar2->setMaximumSize(QSize(118, 16777215));
        progressBar2->setValue(24);

        horizontalLayout_4->addWidget(progressBar2);

        layoutWidget4 = new QWidget(gstvideo);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(10, 610, 182, 29));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        slider5 = new QSlider(layoutWidget4);
        slider5->setObjectName(QStringLiteral("slider5"));
        slider5->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(slider5);

        layoutWidget5 = new QWidget(gstvideo);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(300, 490, 79, 116));
        verticalLayout = new QVBoxLayout(layoutWidget5);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        bplay = new QToolButton(layoutWidget5);
        bplay->setObjectName(QStringLiteral("bplay"));

        verticalLayout->addWidget(bplay);

        bstop = new QToolButton(layoutWidget5);
        bstop->setObjectName(QStringLiteral("bstop"));
        bstop->setMaximumSize(QSize(81, 16777215));

        verticalLayout->addWidget(bstop);

        comboBox = new QComboBox(layoutWidget5);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout->addWidget(comboBox);

        label = new QLabel(gstvideo);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 490, 54, 15));
        label_2 = new QLabel(gstvideo);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 540, 61, 16));
        label_3 = new QLabel(gstvideo);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 590, 54, 15));
        label_4 = new QLabel(gstvideo);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(460, 490, 54, 15));
        label_5 = new QLabel(gstvideo);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(460, 550, 61, 16));
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        widget->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();

        retranslateUi(gstvideo);

        QMetaObject::connectSlotsByName(gstvideo);
    } // setupUi

    void retranslateUi(QWidget *gstvideo)
    {
        gstvideo->setWindowTitle(QApplication::translate("gstvideo", "gstvideo", 0));
#ifndef QT_NO_WHATSTHIS
        slider1->setWhatsThis(QApplication::translate("gstvideo", "<html><head/><body><p>Contraste</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        slider2->setWhatsThis(QApplication::translate("gstvideo", "<html><head/><body><p>Brillo</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        bplay->setWhatsThis(QApplication::translate("gstvideo", "<html><head/><body><p>Play</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        bplay->setText(QApplication::translate("gstvideo", "Play", 0));
        bstop->setText(QApplication::translate("gstvideo", "Pause", 0));
#ifndef QT_NO_WHATSTHIS
        comboBox->setWhatsThis(QApplication::translate("gstvideo", "<html><head/><body><p>efectos</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        label->setText(QApplication::translate("gstvideo", "Contrast", 0));
        label_2->setText(QApplication::translate("gstvideo", "Brightness", 0));
        label_3->setText(QApplication::translate("gstvideo", "Volume", 0));
        label_4->setText(QApplication::translate("gstvideo", "Hue", 0));
        label_5->setText(QApplication::translate("gstvideo", "Saturation", 0));
    } // retranslateUi

};

namespace Ui {
    class gstvideo: public Ui_gstvideo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSTVIDEO_H
