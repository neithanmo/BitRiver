#ifndef NEWSOURCE_H
#define NEWSOURCE_H

#include <QDialog>
#include<QListWidget>
#include <QString>
#include <QMessageBox>
#include <QDir>
#include<QTextStream>
#include<QFileDialog>
#include<QDebug>

namespace Ui {
class newSource;
}

class newSource : public QDialog
{
    Q_OBJECT

public:
    explicit newSource(QWidget *parent = 0);
    ~newSource();
    friend class gstvideo;

private slots:


    void on_listWidget_currentRowChanged(int currentRow);


    void on_Newmediasource_accepted();

private:
    Ui::newSource *ui;
    int sourcetype;
    int sourcePort;
    QString sourceIP;
    QString sourcefilePath;
    QString sourceName;
};

#endif // NEWSOURCE_H
