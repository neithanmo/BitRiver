#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <QDialog>
#include <QString>

namespace Ui {
class inputBox;
}

class inputBox : public QDialog
{
    Q_OBJECT

public:
    explicit inputBox(QWidget *parent = 0);
    ~inputBox();
    QString youtube;
    int resolutionX, resolutionY;
    int arate, channels,framerate;
    int vbrate,abrate;


private slots:
    void on_buttonBox_accepted();

    void on_Resolution_currentIndexChanged(int index);

    void on_Audiorate_currentIndexChanged(int index);

    void on_Channels_currentIndexChanged(int index);

    void on_VideoBitRate_currentIndexChanged(int index);

    void on_AudioBitRate_currentIndexChanged(int index);

    void on_Framerate_currentIndexChanged(int index);

private:
    Ui::inputBox *ui;
};

#endif // INPUTBOX_H
