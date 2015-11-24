#ifndef QTSHANOIRDATASET_H
#define QTSHANOIRDATASET_H

#include <QtCore>
#include "qtshanoirprocess.h"


class  QtShanoirDataset
{
private:
    int id;
    QString name;
    QDate creationDate;
    QString comment;
    float repetitionTime;
    float flipAngle;
    float echoTime;
    QList<QtShanoirProcess> processList;
    QString filter;

public:
    int getId();
    void setId(int);
    QString getName();

    /**
    As for now, possible field are name and filter...
    */
    QString getField(const QString & field);

    void setName(QString);
    QDate getCreationDate();
    void setCreationDate(QDate);
    QString getComment();
    void setComment(QString);
    float getRepetitionTime();
    void setRepetitionTime(float);
    float getFlipAngle();
    void setFlipAngle(float);
    float getEchoTime();
    void setEchoTime(float);
    QString getFilter();
    void setFilter(QString);
    QtShanoirProcess& getProcessById(int id);
    void insertProcess(QtShanoirProcess);
    void displayProcessList();
    QMap<int,QString> getProcessList();
};

#endif // QTSHANOIRDATASET_H
