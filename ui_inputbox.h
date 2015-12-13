/********************************************************************************
** Form generated from reading UI file 'inputbox.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTBOX_H
#define UI_INPUTBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_inputBox
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *youtubeLine;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_2;
    QComboBox *Resolution;
    QHBoxLayout *horizontalLayout_10;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *Audiorate;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *Channels;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QComboBox *VideoBitRate;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QComboBox *AudioBitRate;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *Framerate;
    QLabel *label_11;
    QLabel *label_12;
    QCheckBox *Record;
    QLabel *label_9;
    QSplitter *splitter;
    QCheckBox *checkBox;
    QComboBox *LocalCamera;
    QComboBox *soundCards;
    QSplitter *splitter_2;
    QComboBox *VideoSRC;
    QLabel *label_8;
    QLineEdit *VideoPath;
    QLabel *label_10;
    QComboBox *AudioSRC;
    QLineEdit *AudioPath;

    void setupUi(QDialog *inputBox)
    {
        if (inputBox->objectName().isEmpty())
            inputBox->setObjectName(QStringLiteral("inputBox"));
        inputBox->resize(755, 325);
        buttonBox = new QDialogButtonBox(inputBox);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(660, 30, 85, 60));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(inputBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 50, 317, 237));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        youtubeLine = new QLineEdit(layoutWidget);
        youtubeLine->setObjectName(QStringLiteral("youtubeLine"));

        horizontalLayout->addWidget(youtubeLine);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_12->addWidget(label_2);

        Resolution = new QComboBox(layoutWidget);
        Resolution->setObjectName(QStringLiteral("Resolution"));

        horizontalLayout_12->addWidget(Resolution);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);


        horizontalLayout_10->addLayout(horizontalLayout_4);

        Audiorate = new QComboBox(layoutWidget);
        Audiorate->setObjectName(QStringLiteral("Audiorate"));

        horizontalLayout_10->addWidget(Audiorate);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);


        horizontalLayout_9->addLayout(horizontalLayout_5);

        Channels = new QComboBox(layoutWidget);
        Channels->setObjectName(QStringLiteral("Channels"));

        horizontalLayout_9->addWidget(Channels);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);


        horizontalLayout_8->addLayout(horizontalLayout_6);

        VideoBitRate = new QComboBox(layoutWidget);
        VideoBitRate->setObjectName(QStringLiteral("VideoBitRate"));

        horizontalLayout_8->addWidget(VideoBitRate);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);


        horizontalLayout_2->addLayout(horizontalLayout_7);

        AudioBitRate = new QComboBox(layoutWidget);
        AudioBitRate->setObjectName(QStringLiteral("AudioBitRate"));

        horizontalLayout_2->addWidget(AudioBitRate);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        Framerate = new QComboBox(layoutWidget);
        Framerate->setObjectName(QStringLiteral("Framerate"));

        horizontalLayout_3->addWidget(Framerate);


        verticalLayout_2->addLayout(horizontalLayout_3);

        label_11 = new QLabel(inputBox);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(140, 20, 97, 15));
        label_12 = new QLabel(inputBox);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(470, 20, 79, 15));
        Record = new QCheckBox(inputBox);
        Record->setObjectName(QStringLiteral("Record"));
        Record->setGeometry(QRect(430, 260, 119, 23));
        label_9 = new QLabel(inputBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(540, 40, 101, 23));
        splitter = new QSplitter(inputBox);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(360, 40, 106, 77));
        splitter->setOrientation(Qt::Vertical);
        checkBox = new QCheckBox(splitter);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        splitter->addWidget(checkBox);
        LocalCamera = new QComboBox(splitter);
        LocalCamera->setObjectName(QStringLiteral("LocalCamera"));
        splitter->addWidget(LocalCamera);
        soundCards = new QComboBox(splitter);
        soundCards->setObjectName(QStringLiteral("soundCards"));
        splitter->addWidget(soundCards);
        splitter_2 = new QSplitter(inputBox);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setGeometry(QRect(540, 65, 116, 151));
        splitter_2->setOrientation(Qt::Vertical);
        VideoSRC = new QComboBox(splitter_2);
        VideoSRC->setObjectName(QStringLiteral("VideoSRC"));
        splitter_2->addWidget(VideoSRC);
        label_8 = new QLabel(splitter_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        splitter_2->addWidget(label_8);
        VideoPath = new QLineEdit(splitter_2);
        VideoPath->setObjectName(QStringLiteral("VideoPath"));
        splitter_2->addWidget(VideoPath);
        label_10 = new QLabel(splitter_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        splitter_2->addWidget(label_10);
        AudioSRC = new QComboBox(splitter_2);
        AudioSRC->setObjectName(QStringLiteral("AudioSRC"));
        splitter_2->addWidget(AudioSRC);
        AudioPath = new QLineEdit(splitter_2);
        AudioPath->setObjectName(QStringLiteral("AudioPath"));
        splitter_2->addWidget(AudioPath);

        retranslateUi(inputBox);
        QObject::connect(buttonBox, SIGNAL(accepted()), inputBox, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), inputBox, SLOT(reject()));
        QObject::connect(checkBox, SIGNAL(clicked(bool)), VideoPath, SLOT(clear()));
        QObject::connect(checkBox, SIGNAL(clicked(bool)), AudioPath, SLOT(clear()));
        QObject::connect(checkBox, SIGNAL(clicked(bool)), VideoSRC, SLOT(clear()));
        QObject::connect(checkBox, SIGNAL(clicked(bool)), AudioSRC, SLOT(clear()));

        QMetaObject::connectSlotsByName(inputBox);
    } // setupUi

    void retranslateUi(QDialog *inputBox)
    {
        inputBox->setWindowTitle(QApplication::translate("inputBox", "Dialog", 0));
        label->setText(QApplication::translate("inputBox", "youtube-Key:", 0));
        label_2->setText(QApplication::translate("inputBox", "Resolution:", 0));
        label_4->setText(QApplication::translate("inputBox", "Audiorate:", 0));
        label_5->setText(QApplication::translate("inputBox", "Channels:", 0));
        label_6->setText(QApplication::translate("inputBox", "video birate:", 0));
        label_7->setText(QApplication::translate("inputBox", "Audio bitrate:", 0));
        label_3->setText(QApplication::translate("inputBox", "Framerate:", 0));
        label_11->setText(QApplication::translate("inputBox", "Encoding settings", 0));
        label_12->setText(QApplication::translate("inputBox", "Signal Sources", 0));
        Record->setText(QApplication::translate("inputBox", "Local Recording", 0));
        label_9->setText(QApplication::translate("inputBox", "External Sources", 0));
        checkBox->setText(QApplication::translate("inputBox", "Local Sources", 0));
        label_8->setText(QApplication::translate("inputBox", "Video", 0));
        VideoPath->setText(QString());
        label_10->setText(QApplication::translate("inputBox", "Audio", 0));
    } // retranslateUi

};

namespace Ui {
    class inputBox: public Ui_inputBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTBOX_H
