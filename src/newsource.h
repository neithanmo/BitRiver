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

    void on_videoDev_currentIndexChanged(int index);

    void on_audioDev_currentIndexChanged(int index);

    void on_lineEdit_2_editingFinished();

private:
    Ui::newSource *ui;
    int sourcetype;
    int sourcePort;
    QString sourceIP;
    QString sourcefilePath;
    QString device;
    QString sourceName;
};

#endif // NEWSOURCE_H
