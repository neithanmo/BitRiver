#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <QDialog>

namespace Ui {
class inputBox;
}

class inputBox : public QDialog
{
    Q_OBJECT

public:
    explicit inputBox(QWidget *parent = 0);
    ~inputBox();

private:
    Ui::inputBox *ui;
};

#endif // INPUTBOX_H
