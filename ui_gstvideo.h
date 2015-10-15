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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gstvideo
{
public:
    QLineEdit *lineEdit_2;
    QWidget *widget;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QSlider *slider3;
    QProgressBar *progressBar3;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_2;
    QSlider *slider4;
    QProgressBar *progressBar4;
    QWidget *widget3;
    QHBoxLayout *horizontalLayout_3;
    QSlider *slider1;
    QProgressBar *progressBar1;
    QWidget *widget4;
    QHBoxLayout *horizontalLayout_4;
    QSlider *slider2;
    QProgressBar *progressBar2;
    QWidget *widget5;
    QHBoxLayout *horizontalLayout_5;
    QSlider *slider5;
    QCheckBox *checkBox;
    QWidget *widget6;
    QVBoxLayout *verticalLayout;
    QToolButton *bplay;
    QToolButton *bstop;
    QComboBox *comboBox;
    QComboBox *Resolution;

    void setupUi(QWidget *gstvideo)
    {
        if (gstvideo->objectName().isEmpty())
            gstvideo->setObjectName(QStringLiteral("gstvideo"));
        gstvideo->resize(741, 661);
        gstvideo->setMinimumSize(QSize(741, 0));
        lineEdit_2 = new QLineEdit(gstvideo);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(400, 610, 261, 21));
        widget = new QWidget(gstvideo);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 0, 723, 425));
        widget->setMinimumSize(QSize(723, 0));
        widget1 = new QWidget(gstvideo);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(460, 490, 187, 29));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        slider3 = new QSlider(widget1);
        slider3->setObjectName(QStringLiteral("slider3"));
        slider3->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(slider3);

        progressBar3 = new QProgressBar(widget1);
        progressBar3->setObjectName(QStringLiteral("progressBar3"));
        progressBar3->setValue(24);

        horizontalLayout->addWidget(progressBar3);

        widget2 = new QWidget(gstvideo);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(460, 550, 187, 29));
        horizontalLayout_2 = new QHBoxLayout(widget2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        slider4 = new QSlider(widget2);
        slider4->setObjectName(QStringLiteral("slider4"));
        slider4->setMaximumSize(QSize(160, 16777215));
        slider4->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(slider4);

        progressBar4 = new QProgressBar(widget2);
        progressBar4->setObjectName(QStringLiteral("progressBar4"));
        progressBar4->setMaximumSize(QSize(118, 16777215));
        progressBar4->setValue(24);

        horizontalLayout_2->addWidget(progressBar4);

        widget3 = new QWidget(gstvideo);
        widget3->setObjectName(QStringLiteral("widget3"));
        widget3->setGeometry(QRect(10, 490, 187, 29));
        horizontalLayout_3 = new QHBoxLayout(widget3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        slider1 = new QSlider(widget3);
        slider1->setObjectName(QStringLiteral("slider1"));
        slider1->setMaximumSize(QSize(16777215, 27));
        slider1->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(slider1);

        progressBar1 = new QProgressBar(widget3);
        progressBar1->setObjectName(QStringLiteral("progressBar1"));
        progressBar1->setValue(24);

        horizontalLayout_3->addWidget(progressBar1);

        widget4 = new QWidget(gstvideo);
        widget4->setObjectName(QStringLiteral("widget4"));
        widget4->setGeometry(QRect(10, 550, 187, 29));
        horizontalLayout_4 = new QHBoxLayout(widget4);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        slider2 = new QSlider(widget4);
        slider2->setObjectName(QStringLiteral("slider2"));
        slider2->setMaximumSize(QSize(160, 16777215));
        slider2->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(slider2);

        progressBar2 = new QProgressBar(widget4);
        progressBar2->setObjectName(QStringLiteral("progressBar2"));
        progressBar2->setMaximumSize(QSize(118, 16777215));
        progressBar2->setValue(24);

        horizontalLayout_4->addWidget(progressBar2);

        widget5 = new QWidget(gstvideo);
        widget5->setObjectName(QStringLiteral("widget5"));
        widget5->setGeometry(QRect(10, 600, 182, 29));
        horizontalLayout_5 = new QHBoxLayout(widget5);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        slider5 = new QSlider(widget5);
        slider5->setObjectName(QStringLiteral("slider5"));
        slider5->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(slider5);

        checkBox = new QCheckBox(widget5);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        horizontalLayout_5->addWidget(checkBox);

        widget6 = new QWidget(gstvideo);
        widget6->setObjectName(QStringLiteral("widget6"));
        widget6->setGeometry(QRect(300, 490, 79, 116));
        verticalLayout = new QVBoxLayout(widget6);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        bplay = new QToolButton(widget6);
        bplay->setObjectName(QStringLiteral("bplay"));

        verticalLayout->addWidget(bplay);

        bstop = new QToolButton(widget6);
        bstop->setObjectName(QStringLiteral("bstop"));
        bstop->setMaximumSize(QSize(81, 16777215));

        verticalLayout->addWidget(bstop);

        comboBox = new QComboBox(widget6);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout->addWidget(comboBox);

        Resolution = new QComboBox(widget6);
        Resolution->setObjectName(QStringLiteral("Resolution"));

        verticalLayout->addWidget(Resolution);

        slider3->raise();
        progressBar3->raise();
        checkBox->raise();
        bplay->raise();
        comboBox->raise();
        progressBar1->raise();
        slider2->raise();
        slider4->raise();
        lineEdit_2->raise();
        widget->raise();
        progressBar4->raise();
        slider5->raise();
        slider1->raise();
        Resolution->raise();
        progressBar2->raise();
        bstop->raise();
        progressBar3->raise();
        progressBar4->raise();

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
        checkBox->setText(QApplication::translate("gstvideo", "CheckBox", 0));
#ifndef QT_NO_WHATSTHIS
        bplay->setWhatsThis(QApplication::translate("gstvideo", "<html><head/><body><p>Play</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        bplay->setText(QApplication::translate("gstvideo", "Play", 0));
        bstop->setText(QApplication::translate("gstvideo", "Pause", 0));
#ifndef QT_NO_WHATSTHIS
        comboBox->setWhatsThis(QApplication::translate("gstvideo", "<html><head/><body><p>efectos</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
    } // retranslateUi

};

namespace Ui {
    class gstvideo: public Ui_gstvideo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSTVIDEO_H
