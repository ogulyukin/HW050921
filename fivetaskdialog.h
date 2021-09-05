#ifndef FIVETASKDIALOG_H
#define FIVETASKDIALOG_H

#include <QDialog>

namespace Ui {
class fiveTaskDialog;
}

class fiveTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit fiveTaskDialog(int partNum, QStringList &test, QString title, QWidget *parent = nullptr);
    ~fiveTaskDialog();

private slots:
    void on_task5Button2_clicked();

private:
    Ui::fiveTaskDialog *ui;
};

#endif // FIVETASKDIALOG_H
