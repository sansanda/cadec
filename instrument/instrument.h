#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <QObject>
#include <QDebug>
#include <QTest>
#include <QThread>

#include "./gpib/SCPICommandFactory.h"
#include "./communications/parallelCommunications/gpib/gpibPort.h"
#include "./setup/setup.h"

#include "iostream"
#include "windows.h"

class Instrument: public QObject{
    Q_OBJECT

public:
    Instrument(         QString* _name,
                        QString* _idn,
                        QString* _reference,
                        QString* _manufacturer)
    {
        setName(_name);
        setIDN(_idn);
        setReference(_reference);
        setManufacturer(_manufacturer);
        setOperationMode(0);
        gpibPort = new GPIBPort();
        scpiCommandFactory = new SCPICommandFactory();
        actualSetup = new Setup();

    }
    Instrument()
    {
        setName(new QString("default Name"));
        setIDN(new QString("default IDN"));
        setReference(new QString("default reference"));
        setManufacturer(new QString("default manufacturer"));
        setOperationMode(0);
        gpibPort = new GPIBPort();
        scpiCommandFactory = new SCPICommandFactory();
        actualSetup = new Setup();
    }

    ~Instrument(){}

    QString* getName(){return name;}
    void setName(QString* _name){name = _name;}
    QString* getIDN(){return idn;}
    void setIDN(QString* _idn){idn = _idn;}
    QString* getReference(){return reference;}
    void setReference(QString* _reference){reference = _reference;}
    QString* getManufacturer(){return manufacturer;}
    void setManufacturer(QString* _manufacturer){manufacturer = _manufacturer;}
    int getOperationMode() const{return operationMode;}
    void setOperationMode(int value) {operationMode = value;}
    Setup *getActualSetup() const;
    void setActualSetup(Setup *value);


    void print()
    {


        std::cout<<"*******************************************"<<std::endl;
        std::cout<<"**************INSTRUMENT DATA**************"<<std::endl;
        std::cout<<"*******************************************"<<std::endl;

        std::cout<<"Name = "        <<getName()->toStdString()<<std::endl;
        std::cout<<"IDN = "         <<getIDN()->toStdString()<<std::endl;
        std::cout<<"Reference = "   <<getReference()->toStdString()<<std::endl;
        std::cout<<"Manufacturer = "<<getManufacturer()->toStdString()<<std::endl;
        std::cout<<"OperationMode = "<<getOperationMode()<<std::endl;

    }

public:

    //Communication Ports
    GPIBPort* gpibPort;
    SCPICommandFactory* scpiCommandFactory;
    Setup* actualSetup;

private:
    QString*    name;
    QString*    idn;
    QString*    reference;
    QString*    manufacturer;

protected:
    //Operation modes
    //0 --> Sweep Voltage
    //1 --> Sweep Current
    //
    int operationMode;
};


#endif // INSTRUMENT_H
