#ifndef CODEC_H
#define CODEC_H

#include "cadecCommands.h"
#include "instrument/keithley/keithleyK24xx.h"
#include "instrument/keithley/keithleyK2400.h"
#include "instrument/keithley/keithleyK2410.h"
#include "instrument/keithley/keithleyK2420.h"
#include "instrument/keithley/keithleyK2425.h"
#include "instrument/keithley/keithleyK2430.h"
#include "instrument/keithley/keithleyK2440.h"
#include "instrument/wentworth/wentworthS200.h"


#include "commandExecutionResult_Codes.h"

#include <QCoreApplication>
#include <QDebug>
#include <iostream>

#include "K24xxConfigurationParameters.h"

#include "math.h"

/**
  * CADEC (Computer Aided Device Electric Characterization)
  * @brief bla bla bla ....
  * @param none
  * @return none
  */

class Cadec: public QObject {
    Q_OBJECT


//Attributes
public:

protected:


private:

    QString promptString;
    QString cadecInfo;
    QString helpString;

    Instrument* actualInstrument;

    QStringList commandsList;

//Constructors and destructors
public:
    Cadec()
    {
        promptString = "";
        cadecInfo = "CADEC INFO:\n\n";
        helpString = "CADEC HELP: \n\n";
        actualInstrument = (KeithleyK2400*) new KeithleyK2400();
        actualInstrument->setReference(new QString("2400"));
        actualInstrument->setOperationMode(SWEEP_VOLTAGE);
        fillCommandsList();
    }
    ~Cadec(){}

//Methods
public:
    int executeCommand(QString _cmd);
    QString getInfo();
    QString getPromptString();
    QString getHelp();
    int changeOperationMode(QString _om);
    int changeActualInstrument(QString _ref);

    QStringList getSuggestedCommandsList(QString _cmd);
    int printSuggestedCommandsList(QTextStream &Rout,QString _cmd);

    void printLastCommand_ExecutionResult(int commandExecRes, QString commandLine);


protected:

private:

    void print();
    void fillCommandsList();

//Signals and slots

signals:

    //Signals to the logic controller

private slots:

    //********************************************************************//
    //*************************Logic Controller Slots**********************//
    //********************************************************************//


    //********************************************************************//
    //*************************Slots END**********************************//
    //********************************************************************//

    //********************************************************************//
    //**************************File System Slots*************************//
    //********************************************************************//


    //********************************************************************//
    //*************************Slots END**********************************//
    //********************************************************************//

};

#endif // CODEC_H
