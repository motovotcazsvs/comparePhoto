#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include <QString>

class MyClass:public QObject
{
    Q_OBJECT
public:
    MyClass(QString name);
public slots:
    void doWork();
    void comparePhotos();
signals:
    void send(int);
    void finished();
private:
    QString name;
};

#endif // MYCLASS_H
