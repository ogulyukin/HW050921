#include "homwwork.h"
#include "ui_homwwork.h"

HomwWork::HomwWork(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HomwWork)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Домашнее задание");
    QTextCodec *codec = QTextCodec::codecForName("UTF-8"); //set codec for WIN coding
    QTextCodec::setCodecForLocale(codec);
    ui->tabWidget->setCurrentWidget(ui->tab);
}

HomwWork::~HomwWork()
{
    delete ui;
}


void HomwWork::on_filePushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open File",
                                                        "/home", tr("Text files (*.txt);;XML files (*.xml)All files (*.*)"));
    if(filename.isEmpty())
           return;
    qDebug() << "File choosen : " << filename;
    ui->fileLabel->setText(filename);
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    QString line = in.readLine();
    while(!line.isNull())
    {
        firstTask.append(line);
        line = in.readLine();
    }
    file.close();
    calculateStrings(firstTask);
}

void HomwWork::calculateStrings(QStringList &strings)
{
    int maxLength = 0;
    int minLength = strings.at(0).length();
    int totalLength = 0;
    for(auto i = strings.begin(); i != strings.end(); i++)
    {
        int length = i->length();
        if(length > maxLength)
            maxLength = length;
        if(length < minLength)
            minLength = length;
        totalLength += length;
        QStringList temp = i->split(' ');
        secondTask += temp;
    }
    int averageLength = totalLength / strings.count();
    ui->AverageStringLabel->setText(QString::number(averageLength));
    ui->MaxStringLabel->setText(QString::number(maxLength));
    ui->MinStringLabel->setText(QString::number(minLength));
}

void HomwWork::setSymbolsLabel()
{
    QString result = "";
    for (auto i = symbols.begin(); i != symbols.end(); i++)
    {
        result +=*i + " ";
    }
    ui->symbolsLabel->setText(result);
}

int HomwWork::calculateSymbols(QStringList list)
{
    int count = 0;
    for (auto it = list.begin(); it != list.end(); it++)
    {
        count += it->count();
    }
    return count;
}


void HomwWork::on_addsymbolButton_clicked()
{
    bool resultDialog = false;
    QString result = QInputDialog::getText(this, tr("Добавления символа"),
                                           tr("Введите новый первый символ для поиска:"), QLineEdit::Normal,"", &resultDialog);
    if(resultDialog && !result.isEmpty())
    {
        symbols.append(*result.begin());
        setSymbolsLabel();
    }
}


void HomwWork::on_FindWordsButton_clicked()
{
    int result = 0;
    for (auto i = secondTask.begin(); i != secondTask.end(); i++)
    {
        for (auto i2 = symbols.begin(); i2 != symbols.end(); i2++)
        {
            if(*i->begin() == *i2)
                result++;
        }
    }
    ui->resultCountLabel->setText(QString::number(result));
}


void HomwWork::on_saveToANSIpushButton_clicked()
{
    QString resultPath = QFileDialog::getExistingDirectory(this, "Open Directory", QDir::currentPath(),
                                                           QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(resultPath.isEmpty())
    {
        return;
    }
    resultPath += QDir::separator();
    resultPath += "task2file.txt";
    QFile ansiFile(resultPath);
    if (!ansiFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QMessageBox::information(this, "Ошибка", "Невозможно создать файл!");
        return;
    }
    QTextCodec *aCodec = QTextCodec::codecForName("cp1251");
    QTextStream ofstr(&ansiFile);
    ofstr.setCodec(aCodec); //Установка кодека для записи
    for(auto it = firstTask.begin(); it != firstTask.end(); it++)
    {
        ofstr << *it << Qt::endl;
    }
    ansiFile.close();
    QMessageBox::information(this, "Успех", resultPath +" записан");
}


void HomwWork::on_findWordInText_clicked()
{
    int count = 0;
    for(auto it = secondTask.begin(); it != secondTask.end(); it++)
    {
        for(auto it2 = fourTask.begin(); it2 != fourTask.end(); it2++)
        {
            if(*it == *it2)
                count++;
        }
    }

    ui->textBrowser->append("<font color = \"red\"><b>Найдено " + QString::number(count) + " совпадений</b></font>");
}


void HomwWork::on_chooseWordButton_clicked()
{
    bool resultDialog = false;
    QString result = QInputDialog::getText(this, tr("Добавления слов"),
                                           tr("Введите новое слова для поиска в тексте:"), QLineEdit::Normal,"", &resultDialog);
    if(resultDialog && !result.isEmpty())
    {
        fourTask.append(result);
        ui->textBrowser->append(result);
    }
}


void HomwWork::on_task5Button_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open File",
                                                        "/home", tr("Text files (*.txt);;XML files (*.xml)All files (*.*)"));
    if(filename.isEmpty())
           return;
    qDebug() << "File choosen : " << filename;
    ui->fileLabel->setText(filename);
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    QString line = in.readLine();
    while(!line.isNull())
    {
        fiveTask.append(line);
        line = in.readLine();
    }
    file.close();
    int totalStr = fiveTask.count();
    int numberOfForms = totalStr / 4;
    if(numberOfForms < 3)
    {
        QMessageBox::information(this, "ОШИБКА", "Выбран слишком маленький файл - невозможно выполнить условия задания!");
        return;
    }
    int count = 1;
    int symbolsCount = 0;
    auto it = fiveTask.begin();
    for(int i = 0; i < numberOfForms; i++)
    {
        QStringList temp;
        for(int i = 0; i < 4; i++)
        {
            if(it != fiveTask.end())
                temp << *it;
            it++;
        }
        symbolsCount += calculateSymbols(temp);
        QString titleDialog = "Просмотр Файла";
        if( i == numberOfForms - 1)
            titleDialog = "Среднее число символов на страницу " + QString::number(symbolsCount / numberOfForms);
        fiveTaskDialog* dialog = new fiveTaskDialog(count, temp, titleDialog, this);
        dialog->exec();
        count++;
    }
}


void HomwWork::on_task6Button_clicked()
{
    int Number = QRandomGenerator::global()->bounded(0,100);
    qDebug() << "Загадано число " << Number;
    int userNumber = -1;
    int count = 0;
    bool winFlag = false;
    while (Number != userNumber)
    {
        bool resultDialog = false;
        userNumber = QInputDialog::getInt(this, tr("Ваш ход"),
                                               tr("Введите число от 0 до 100"), -1, 0, 100, 1, &resultDialog);
        if(resultDialog)
        {
            if (Number == userNumber)
            {
                winFlag = true;
            }else if(Number > userNumber)
            {
                QMessageBox::information(this, "Ира", "Ваше число меньше чем загаданное!");
            }else if(Number < userNumber)
            {
                QMessageBox::information(this, "Ира", "Ваше число больше чем загаданное!");
            }

        }else
        {
            break;
        }
        count++;

    }
    if(winFlag == true)
    {
        QMessageBox::information(this,"ПОБЕДА", "Вы победили !\n Это заняло\n" + QString::number(count) + " попыток");
    }else
    {
        QMessageBox::information(this,"ПОРАЖЕНИЕ", "Вы не сумели отгадать число !\n Безплодно потрачено\n" + QString::number(count) + " попыток");
    }
}

