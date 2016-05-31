/********************************************************************************
** Form generated from reading UI file 'gstvideo.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gstvideo
{
public:
    QWidget *widget;
    QSpinBox *spinBox;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QSlider *slider2;
    QProgressBar *progressBar2;
    QHBoxLayout *horizontalLayout_2;
    QSlider *slider4;
    QProgressBar *progressBar4;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_5;
    QSlider *slider5;
    QHBoxLayout *horizontalLayout_3;
    QSlider *slider1;
    QProgressBar *progressBar1;
    QHBoxLayout *horizontalLayout;
    QSlider *slider3;
    QProgressBar *progressBar3;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QToolButton *bplay;
    QToolButton *bstop;
    QComboBox *comboBox;
    QLabel *label_4;
    QPushButton *pushButton;

    void setupUi(QWidget *gstvideo)
    {
        if (gstvideo->objectName().isEmpty())
            gstvideo->setObjectName(QStringLiteral("gstvideo"));
        gstvideo->resize(660, 694);
        gstvideo->setMinimumSize(QSize(660, 0));
        gstvideo->setMaximumSize(QSize(660, 16777215));
        widget = new QWidget(gstvideo);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 0, 723, 425));
        widget->setMinimumSize(QSize(723, 0));
        spinBox = new QSpinBox(gstvideo);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(350, 770, 44, 25));
        layoutWidget = new QWidget(gstvideo);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 480, 641, 204));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        slider2 = new QSlider(layoutWidget);
        slider2->setObjectName(QStringLiteral("slider2"));
        slider2->setMaximumSize(QSize(160, 16777215));
        slider2->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(slider2);

        progressBar2 = new QProgressBar(layoutWidget);
        progressBar2->setObjectName(QStringLiteral("progressBar2"));
        progressBar2->setMaximumSize(QSize(118, 16777215));
        progressBar2->setValue(24);

        horizontalLayout_4->addWidget(progressBar2);


        gridLayout->addLayout(horizontalLayout_4, 3, 0, 2, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        slider4 = new QSlider(layoutWidget);
        slider4->setObjectName(QStringLiteral("slider4"));
        slider4->setMaximumSize(QSize(160, 16777215));
        slider4->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(slider4);

        progressBar4 = new QProgressBar(layoutWidget);
        progressBar4->setObjectName(QStringLiteral("progressBar4"));
        progressBar4->setMaximumSize(QSize(118, 16777215));
        progressBar4->setValue(24);

        horizontalLayout_2->addWidget(progressBar4);


        gridLayout->addLayout(horizontalLayout_2, 4, 2, 2, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 5, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        slider5 = new QSlider(layoutWidget);
        slider5->setObjectName(QStringLiteral("slider5"));
        slider5->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(slider5);


        gridLayout->addLayout(horizontalLayout_5, 6, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        slider1 = new QSlider(layoutWidget);
        slider1->setObjectName(QStringLiteral("slider1"));
        slider1->setMaximumSize(QSize(16777215, 27));
        slider1->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(slider1);

        progressBar1 = new QProgressBar(layoutWidget);
        progressBar1->setObjectName(QStringLiteral("progressBar1"));
        progressBar1->setValue(24);

        horizontalLayout_3->addWidget(progressBar1);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        slider3 = new QSlider(layoutWidget);
        slider3->setObjectName(QStringLiteral("slider3"));
        slider3->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(slider3);

        progressBar3 = new QProgressBar(layoutWidget);
        progressBar3->setObjectName(QStringLiteral("progressBar3"));
        progressBar3->setValue(24);

        horizontalLayout->addWidget(progressBar3);


        gridLayout->addLayout(horizontalLayout, 1, 2, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 2, 2, 2, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        bplay = new QToolButton(layoutWidget);
        bplay->setObjectName(QStringLiteral("bplay"));

        verticalLayout->addWidget(bplay);

        bstop = new QToolButton(layoutWidget);
        bstop->setObjectName(QStringLiteral("bstop"));
        bstop->setMaximumSize(QSize(81, 16777215));

        verticalLayout->addWidget(bstop);

        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout->addWidget(comboBox);


        gridLayout->addLayout(verticalLayout, 0, 1, 6, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 0, 2, 1, 1);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 6, 1, 1, 1);

        spinBox->raise();
        layoutWidget->raise();
        widget->raise();

        retranslateUi(gstvideo);
        QObject::connect(bplay, SIGNAL(clicked()), bstop, SLOT(toggle()));
        QObject::connect(bstop, SIGNAL(clicked()), bplay, SLOT(toggle()));

        QMetaObject::connectSlotsByName(gstvideo);
    } // setupUi

    void retranslateUi(QWidget *gstvideo)
    {
        gstvideo->setWindowTitle(QApplication::translate("gstvideo", "gstvideo", 0));
#ifndef QT_NO_WHATSTHIS
        slider2->setWhatsThis(QApplication::translate("gstvideo", "<html><head/><body><p>Brillo</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        label_3->setText(QApplication::translate("gstvideo", "Volume", 0));
#ifndef QT_NO_WHATSTHIS
        slider1->setWhatsThis(QApplication::translate("gstvideo", "<html><head/><body><p>Contraste</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        label_2->setText(QApplication::translate("gstvideo", "Brightness", 0));
        label_5->setText(QApplication::translate("gstvideo", "Saturation", 0));
        label->setText(QApplication::translate("gstvideo", "Contrast", 0));
#ifndef QT_NO_WHATSTHIS
        bplay->setWhatsThis(QApplication::translate("gstvideo", "<html><head/><body><p>Play</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        bplay->setText(QApplication::translate("gstvideo", "Play", 0));
        bstop->setText(QApplication::translate("gstvideo", "Pause", 0));
#ifndef QT_NO_WHATSTHIS
        comboBox->setWhatsThis(QApplication::translate("gstvideo", "<html><head/><body><p>efectos</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        label_4->setText(QApplication::translate("gstvideo", "Hue", 0));
        pushButton->setText(QApplication::translate("gstvideo", "new Source", 0));
    } // retranslateUi

};

namespace Ui {
    class gstvideo: public Ui_gstvideo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSTVIDEO_H
/********************************************************************************
** Form generated from reading UI file 'gstvideo.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gstvideo
{
public:
    QWidget *widget;
    QSpinBox *spinBox;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QSlider *slider2;
    QProgressBar *progressBar2;
    QHBoxLayout *horizontalLayout_2;
    QSlider *slider4;
    QProgressBar *progressBar4;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_5;
    QSlider *slider5;
    QHBoxLayout *horizontalLayout_3;
    QSlider *slider1;
    QProgressBar *progressBar1;
    QHBoxLayout *horizontalLayout;
    QSlider *slider3;
    QProgressBar *progressBar3;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QToolButton *bplay;
    QToolButton *bstop;
    QComboBox *comboBox;
    QLabel *label_4;
    QPushButton *pushButton;

    void setupUi(QWidget *gstvideo)
    {
        if (gstvideo->objectName().isEmpty())
            gstvideo->setObjectName(QStringLiteral("gstvideo"));
        gstvideo->resize(660, 694);
        gstvideo->setMinimumSize(QSize(660, 0));
        gstvideo->setMaximumSize(QSize(660, 16777215));
        widget = new QWidget(gstvideo);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 0, 723, 425));
        widget->setMinimumSize(QSize(723, 0));
        spinBox = new QSpinBox(gstvideo);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(350, 770, 44, 25));
        layoutWidget = new QWidget(gstvideo);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 480, 641, 204));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        slider2 = new QSlider(layoutWidget);
        slider2->setObjectName(QStringLiteral("slider2"));
        slider2->setMaximumSize(QSize(160, 16777215));
        slider2->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(slider2);

        progressBar2 = new QProgressBar(layoutWidget);
        progressBar2->setObjectName(QStringLiteral("progressBar2"));
        progressBar2->setMaximumSize(QSize(118, 16777215));
        progressBar2->setValue(24);

        horizontalLayout_4->addWidget(progressBar2);


        gridLayout->addLayout(horizontalLayout_4, 3, 0, 2, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        slider4 = new QSlider(layoutWidget);
        slider4->setObjectName(QStringLiteral("slider4"));
        slider4->setMaximumSize(QSize(160, 16777215));
        slider4->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(slider4);

        progressBar4 = new QProgressBar(layoutWidget);
        progressBar4->setObjectName(QStringLiteral("progressBar4"));
        progressBar4->setMaximumSize(QSize(118, 16777215));
        progressBar4->setValue(24);

        horizontalLayout_2->addWidget(progressBar4);


        gridLayout->addLayout(horizontalLayout_2, 4, 2, 2, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 5, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        slider5 = new QSlider(layoutWidget);
        slider5->setObjectName(QStringLiteral("slider5"));
        slider5->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(slider5);


        gridLayout->addLayout(horizontalLayout_5, 6, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        slider1 = new QSlider(layoutWidget);
        slider1->setObjectName(QStringLiteral("slider1"));
        slider1->setMaximumSize(QSize(16777215, 27));
        slider1->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(slider1);

        progressBar1 = new QProgressBar(layoutWidget);
        progressBar1->setObjectName(QStringLiteral("progressBar1"));
        progressBar1->setValue(24);

        horizontalLayout_3->addWidget(progressBar1);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        slider3 = new QSlider(layoutWidget);
        slider3->setObjectName(QStringLiteral("slider3"));
        slider3->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(slider3);

        progressBar3 = new QProgressBar(layoutWidget);
        progressBar3->setObjectName(QStringLiteral("progressBar3"));
        progressBar3->setValue(24);

        horizontalLayout->addWidget(progressBar3);


        gridLayout->addLayout(horizontalLayout, 1, 2, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 2, 2, 2, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        bplay = new QToolButton(layoutWidget);
        bplay->setObjectName(QStringLiteral("bplay"));

        verticalLayout->addWidget(bplay);

        bstop = new QToolButton(layoutWidget);
        bstop->setObjectName(QStringLiteral("bstop"));
        bstop->setMaximumSize(QSize(81, 16777215));

        verticalLayout->addWidget(bstop);

        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout->addWidget(comboBox);


        gridLayout->addLayout(verticalLayout, 0, 1, 6, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 0, 2, 1, 1);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 6, 1, 1, 1);

        spinBox->raise();
        layoutWidget->raise();
        widget->raise();

        retranslateUi(gstvideo);
        QObject::connect(bplay, SIGNAL(clicked()), bstop, SLOT(toggle()));
        QObject::connect(bstop, SIGNAL(clicked()), bplay, SLOT(toggle()));

        QMetaObject::connectSlotsByName(gstvideo);
    } // setupUi

    void retranslateUi(QWidget *gstvideo)
    {
        gstvideo->setWindowTitle(QApplication::translate("gstvideo", "gstvideo", 0));
#ifndef QT_NO_WHATSTHIS
        slider2->setWhatsThis(QApplication::translate("gstvideo", "<html><head/><body><p>Brillo</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        label_3->setText(QApplication::translate("gstvideo", "Volume", 0));
#ifndef QT_NO_WHATSTHIS
        slider1->setWhatsThis(QApplication::translate("gstvideo", "<html><head/><body><p>Contraste</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        label_2->setText(QApplication::translate("gstvideo", "Brightness", 0));
        label_5->setText(QApplication::translate("gstvideo", "Saturation", 0));
        label->setText(QApplication::translate("gstvideo", "Contrast", 0));
#ifndef QT_NO_WHATSTHIS
        bplay->setWhatsThis(QApplication::translate("gstvideo", "<html><head/><body><p>Play</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        bplay->setText(QApplication::translate("gstvideo", "Play", 0));
        bstop->setText(QApplication::translate("gstvideo", "Pause", 0));
#ifndef QT_NO_WHATSTHIS
        comboBox->setWhatsThis(QApplication::translate("gstvideo", "<html><head/><body><p>efectos</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        label_4->setText(QApplication::translate("gstvideo", "Hue", 0));
        pushButton->setText(QApplication::translate("gstvideo", "new Source", 0));
    } // retranslateUi

};

namespace Ui {
    class gstvideo: public Ui_gstvideo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSTVIDEO_H
