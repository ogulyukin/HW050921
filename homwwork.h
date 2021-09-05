#ifndef HOMWWORK_H
#define HOMWWORK_H

#include <QWidget>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtDebug>
#include <QFileDialog>
#include <QInputDialog>
#include <QTextCodec>
#include <QDir>
#include <QRandomGenerator>
#include "fivetaskdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class HomwWork; }
QT_END_NAMESPACE

class HomwWork : public QWidget
{
    Q_OBJECT

public:
    HomwWork(QWidget *parent = nullptr);
    ~HomwWork();

private slots:
    void on_filePushButton_clicked();

    void on_addsymbolButton_clicked();

    void on_FindWordsButton_clicked();

    void on_saveToANSIpushButton_clicked();

    void on_findWordInText_clicked();

    void on_chooseWordButton_clicked();

    void on_task5Button_clicked();

    void on_task6Button_clicked();

private:
    QStringList firstTask;
    QStringList secondTask;
    QStringList fourTask;
    QStringList fiveTask;
    QList<QString> symbols;
    Ui::HomwWork *ui;
    void calculateStrings(QStringList &strings);
    void setSymbolsLabel();
    int calculateSymbols(QStringList list);
};
#endif // HOMWWORK_H
