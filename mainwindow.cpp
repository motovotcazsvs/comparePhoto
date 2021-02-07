#include "mainwindow.h"
#include "ui_mainwindow.h"

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

#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QLabel>
#include <QPixmap>
#include <QFile>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));

    thread = new QThread;
    my = new MyClass("B");
    my->moveToThread(thread);
    connect(my, SIGNAL(send(int)), this, SLOT(update(int)));
    connect(thread, SIGNAL(started()), my, SLOT(doWork()));
    connect(my, SIGNAL(finished()), thread, SLOT(terminate()));
    thread->start();

    //инициализация базы данных
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/QT_PROJECTS/untitled5/Compare.db3");
    db.open();
    QSqlQuery query;

    //взять с базы данных
    query.exec("SELECT photo, previous_photo, hesh, percent FROM Compare");
    QByteArray photo, previous_photo;
    while(query.next()){
        photo = query.value(0).toByteArray();
        previous_photo = query.value(1).toByteArray();
        QString percent = query.value(3).toString();
        qDebug() << percent << endl;
    }
    QPixmap out_pixmap1 = QPixmap();
    QPixmap out_pixmap2 = QPixmap();
    out_pixmap1.loadFromData(photo);
    out_pixmap2.loadFromData(previous_photo);
    //db.close();
    label_photo.setPixmap(out_pixmap1);
    label_previous_photo.setPixmap(out_pixmap2);
    label_photo.show();
    label_previous_photo.show();

    //поместить в базу данных
    QFile file1("C:/QT_PROJECTS/untitled5/img/13.jpg");
    QFile file2("C:/QT_PROJECTS/untitled5/img/14.jpg");
    if(!file1.open(QIODevice::ReadOnly)) return;
    if(!file2.open(QIODevice::ReadOnly)) return;
    QByteArray inByteArray1 = file1.readAll();
    QByteArray inByteArray2 = file2.readAll();
    file1.close();
    file1.close();
    query.prepare("INSERT INTO Compare(photo, previous_photo, opercent)"
                  "VALUES(:imageData1, :imageData2, :precent);");
    query.bindValue(":imageData1", inByteArray1);
    query.bindValue(":imageData2", inByteArray2);
    //query.bindValue(":hesh", "0");
    query.bindValue(":precent", "19");
    if(!query.exec()) qDebug() << "Error inserting filds into table" << query.lastError();
    db.close();



}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::on_pushButton_clicked()
{
    timer->start(200);
    qDebug() << "START";


}

void MainWindow::updateTime()
{
    QCameraImageCapture *imageCapture;
    imageCapture = new QCameraImageCapture(camera);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->start();
    camera->searchAndLock();
    imageCapture->capture();
    camera->unlock();
    qDebug() << "photo";

}

void MainWindow::on_pushButton_2_clicked()
{
    timer->stop();
    qDebug() << "STOP";

    //connect(my, SIGNAL(finished()), thread, SLOT(terminate()));
    //my->finished();
    //thread->terminate();
    //connect(my, SIGNAL(finished()), this, SLOT(pr()));
}

void MainWindow::update(int i)
{
    ui->textEdit->insertPlainText(QString::number(i));
}


