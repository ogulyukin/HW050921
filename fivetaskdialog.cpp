#include "fivetaskdialog.h"
#include "ui_fivetaskdialog.h"

fiveTaskDialog::fiveTaskDialog(int partNum, QStringList &text, QString title, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fiveTaskDialog)
{
    ui->setupUi(this);
    QDialog::setWindowTitle(title);
    ui->label->setText("Часть " + QString::number(partNum));
    for (auto it = text.begin(); it != text.end(); it++)
    {
        ui->textBrowser->append(*it);
    }
}

fiveTaskDialog::~fiveTaskDialog()
{
    delete ui;
}

void fiveTaskDialog::on_task5Button2_clicked()
{
    this->close();
}

