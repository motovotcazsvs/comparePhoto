#include "mainwindow.h"
#include <QApplication>
#include <windows.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    /*for(int i = 0; i <= 10000; i++)
    {
        Sleep(1000);
        //ui->textEdit_2->insertPlainText(QString::number(i));
        qDebug() << i;
    }*/
}
