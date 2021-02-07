#include <QVideoWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QCameraImageCapture>

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QTimer>

#include "myclass.h"
#include <QThread>
#include "myclass.h"
#include <QDebug>
#include <windows.h>

MyClass::MyClass(QString s) : name(s)
{

}

void MyClass::doWork()
{
    for(int i = 0; i <= 10; i++)
    {
        emit send(i);
        Sleep(1000);
    }
    emit finished();
}

void MyClass::comparePhotos()
{
    int globalCount1 = 0;
    int globalCount2 = 0;
    int ecvivaletCount = 0;
    /*
    QImage img11("C:/img/13.jpg");
    QImage img22("C:/img/14.jpg");
    QImage img1 = img11.scaled(20, 11, Qt::IgnoreAspectRatio);
    QImage img2 = img22.scaled(20, 11, Qt::IgnoreAspectRatio);
    */
    QImage img1("C:/img/13.jpg");
    QImage img2("C:/img/14.jpg");
    QRgb color1, color2;
    globalCount1 = img1.width() * img1.height();
    globalCount2 = img2.width() * img2.height();
    if (globalCount1 != globalCount2)
        qDebug() << globalCount1 << " Ошибка!!!\nРазмер первого изибражения не соответствует второму!"
                                                      << globalCount2;
    for (int i=0;i<img1.width();i++)
        for (int j=0;j<img1.height();j++)
        {
            color1 = img1.pixel(i, j);
            color2 = img2.pixel(i, j);
            int gray1 = qGray(color1);
            int gray2 = qGray(color2);
            img1.setPixel(i, j, qRgb(gray1, gray1, gray1));
            img2.setPixel(i, j, qRgb(gray2, gray2, gray2));

            if (img1.pixel(i, j) == img2.pixel(i, j)){
                ecvivaletCount++;
            }
        }
    int procent = (100 * ecvivaletCount) / globalCount1;
    qDebug() << globalCount1 << endl << globalCount2 << endl << ecvivaletCount << endl << procent;
    emit finished();
}
