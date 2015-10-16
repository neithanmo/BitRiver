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
    int resolution;


private slots:
    void on_buttonBox_accepted();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::inputBox *ui;
};

#endif // INPUTBOX_H
