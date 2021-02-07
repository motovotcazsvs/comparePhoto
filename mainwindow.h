#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCameraViewfinder>
#include <QCameraInfo>
#include "myclass.h"
#include <QThread>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QLabel label_photo;
    QLabel label_previous_photo;


private slots:
    void on_pushButton_clicked();
    void updateTime();
    void update(int);
    void on_pushButton_2_clicked();


private:
    Ui::MainWindow *ui;
    QCamera *camera;
    QCameraViewfinder *viewfinder;
    QTimer *timer;
    QThread *thread;
    MyClass *my;

};

#endif // MAINWINDOW_H
