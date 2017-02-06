#ifndef SETUP_H
#define SETUP_H

#include <QObject>
#include <QCoreApplication>
#include "iostream"
#include <QtXml>
#include "math.h"

class Setup : public QObject
{
    Q_OBJECT

public:
    Setup(QString* _name) {init(_name);}
    Setup() {init(new QString("setup default name") );}
    ~Setup(){}

    void init (QString* _name)
    {
        setName(_name);
        setSaved(false);
        setFilePath(new QString(""));
    }

    QString* getName(){return name;}
    void setName(QString* _name){name = _name;}

    bool isSaved(){return saved;}
    void setSaved(bool _saved){saved = _saved;}

    QString* getFilePath(){return filePath;}
    void setFilePath(QString* _fp){filePath = _fp;}


    virtual void print()
    {
        //std::cout<<"**********************************************"<<std::endl;
        //std::cout<<"******************SETUP DATA******************"<<std::endl;
        //std::cout<<"**********************************************"<<std::endl;

        std::cout<<"Name = "        <<getName()->toStdString()<<std::endl;
        std::cout<<"FilePath = "    <<getFilePath()->toStdString()<<std::endl;
        std::cout<<"Saved = "       <<isSaved()<<std::endl;
    }

protected:

private:
    QString*    name;
    QString*    filePath;
    bool        saved;
};

#endif // SETUP_H
