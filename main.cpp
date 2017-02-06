#include <QCoreApplication>
#include <QDebug>
#include "cadec.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    bool end = false;
    QTextStream in(stdin);
    QTextStream out(stdout);

    QString value = "";

    Cadec* cadec;
    cadec = new Cadec();

    out<< cadec->getHelp();
    out.flush();

    KeithleyK2400* k2400;
    k2400 = new KeithleyK2400();

    k2400->openConnection();
    k2400->reset();
    Sleep(1000);
    qDebug() <<" Presence Status: "<<k2400->checkPresence();
    k2400->clearTriggerCountBuffer();
    k2400->clearBufferOfReadings();
    k2400->setTriggerCount(2500);
    qDebug() <<" IDN: "<<k2400->getIDN();

/*
    int c =    261;    //261 Hz
    int d =    294;    //294 Hz
    int e =    329;    //329 Hz
    int f =    349;    //349 Hz
    int g =    392;    //392 Hz
    int A =    440;    //440 Hz
    int b =    493;    //493 Hz
    int C =    523;    //523 Hz
    int R =    0;      //0   Hz



    int melody[] = {  C,  b,  g,  C,  b,   e,  R,  C,  c,  g, A, C };
    int beats[]  = { 16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8 };
    int beatDuration = 10;
    int i = 0;
    int j = 0;

    int nBeats = 0;
    int vectorLenght = sizeof(melody)/sizeof(melody[0]);

    qDebug() <<" Number: "<<vectorLenght;

    while (i<vectorLenght){
        nBeats = beats[i];
        while (j<nBeats){

            k2400->beeperTone(melody[i],beatDuration);
            Sleep(beatDuration);
            j++;
        }
        i++;
        j=0;

    }
    */
    /*
    while (true){
        Sleep(200);
        k2400->beeperTone(5000,1000);
        Sleep(200);
        k2400->beeperTone(2000,100);
    }*/


    while (!end){

        out<<cadec->getPromptString();
        out.flush();

        value = in.readLine();

        while(value.endsWith( ' ' )) value.chop(1);
        while(value.startsWith( ' ' )) value.remove(0,1);

        if (value.compare("quit") == 0) end = true;
        //qDebug() << cadec->getInfo();
        if (!end) {
            int commandExecRes = cadec->executeCommand(value);
            cadec->printLastCommand_ExecutionResult(commandExecRes, value);
        }
    }

    qDebug() << "Good Bye !!!!!!";
    return a.exec();
}
